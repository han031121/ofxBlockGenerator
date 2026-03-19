#include "drawObject.h"

void drawObject::setup() {
	setFbo();

	light.setup();
	light.setDirectional();
	light.setDiffuseColor(ofFloatColor(1.0));
	light.setSpecularColor(ofFloatColor(0.3));

	cam.setFov(cam_fov);

	float size_r = data->getSizeRow() * block_size;
	float size_c = data->getSizeCol() * block_size;
	float size_h = data->getSizeHeight() * block_size;
	float block_radius = 0.5f * sqrt(size_r * size_r + size_c * size_c + size_h * size_h);
	float margin = 1.2;

	cam_dist = margin * block_radius / std::tan(std::numbers::pi * cam.getFov() / 180 / 2);
	cam_dist = std::max(cam_min_dist, cam_dist);

	std::tuple<float, float, float> block_center = data->getCenter();
	cam_center = {
		get<0>(block_center) * block_size,
		get<2>(block_center) * block_size,
		-get<1>(block_center) * block_size
	};
}

void drawObject::drawBlocks() {
	int max_r = data->getMaxRow();
	int max_c = data->getMaxCol();

	for (int r = 0; r < max_r; r++) {
		for (int c = 0; c < max_c; c++) {
			int height = data->getHeightData(r, c);

			for (int h = 0; h < height; h++)
				ofDrawBox(r * block_size, h * block_size, -c * block_size, block_size);
		}
	}
}

void drawObject::drawOutline() {
	int max_r = data->getMaxRow();
	int max_c = data->getMaxCol();

	ofSetColor(0, 0, 0, 255);

	for (int r = 0; r < max_r; r++) {
		for (int c = 0; c < max_c; c++) {
			int height = data->getHeightData(r, c);

			for (int h = 0; h < height; h++)
				drawSingleOutline(r, c, h);
		}
	}
}

void drawObject::drawSingleOutline(int r, int c, int h) {
	int mul_a[4] = { 1, 1, -1, -1 };
	int mul_b[4] = { 1, -1, 1, -1 };
	glm::vec3 block_center = { r * block_size, h * block_size, -c * block_size };

	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { mul_a[i], mul_b[i], 0 }; //z fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, thickness, thickness, block_size);
	}
	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { 0, mul_b[i], mul_a[i] }; //x fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, block_size, thickness, thickness);
	}
	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { mul_a[i], 0, mul_b[i] }; //y fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, thickness, block_size, thickness);
	}
}

void drawObject::setFbo() {
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	s.useStencil = true;
	s.depthStencilAsTexture = false;
	s.numSamples = 4;
	fbo.allocate(s);
}

void drawObject::setCamera() {
	cam.orbitDeg(90 + degree_xz, -degree_h, cam_dist, cam_center);
	cam.lookAt(cam_center, {0, 1, 0});

	light.setOrientation(glm::vec3(light_degree_h, 270 + light_degree_xz, 0));
}

void drawObject::render() {
	if (!data || !need_to_refresh)
		return;

	fbo.begin();
	ofClear(255, 255, 255, 255);
	setCamera();
	ofEnableDepthTest();

	ofEnableLighting();
	light.enable();

	cam.begin();
	ofSetColor(draw_color, 255);
	drawBlocks();
	cam.end();

	light.disable();
	ofDisableLighting();

	cam.begin();
	ofSetColor(0, 0, 0, 255);
	drawOutline();
	cam.end();

	ofDisableDepthTest();
	fbo.end();

	need_to_refresh = false;
}

void drawObject::saveImage(std::string filename) {
	if (need_to_refresh) {
		status.setStatus(statusLevel::Error, "[ drawObject ] Need to refresh the image.");
		return;
	}
	ofPixels pixels;
	fbo.readToPixels(pixels);
	ofSaveImage(pixels, filename);
};

void drawObject::getPixels(ofPixels & pixels) {
	if (need_to_refresh) {
		status.setStatus(statusLevel::Error, "[ drawObject ] Need to refresh the image.");
		return;
	}
	fbo.readToPixels(pixels);
}

void drawObject::getImage(ofImage & image) {
	if (need_to_refresh) {
		status.setStatus(statusLevel::Error, "[ drawObject ] Need to refresh the image.");
		return;
	}
	ofPixels pix;
	getPixels(pix);
	image.setFromPixels(pix);
}

std::string drawObject::getIdentify() {
	std::string s = "";
	s += data->getIdentify();
	s += '_' + std::to_string((int)degree_xz) + std::to_string((int)degree_h);
	s += '_' + std::to_string((int)light_degree_xz) + std::to_string((int)light_degree_h);
	return s;
}

void drawObject::printImageProperty() {
	std::cout << "[ drawObject ] degree_xz = " << degree_xz << ", degree_h = " << degree_h;
	std::cout << ", light_degree_xz = " << light_degree_xz << ", light_degree_h = " << light_degree_h << "\n";
	std::cout << "[ drawObject ] cam_dist = " << cam_dist << "\n";
	std::cout << "[ drawObject ] cam_center = " << cam_center.x << " " << cam_center.y << " " << cam_center.z << "\n";
}

//---------------------------- Update -------------------------------
void drawObject::camDegreeUpdate(float deg_xz, float deg_h, bool isRelative) {
	if (isRelative) {
		degree_xz += deg_xz;
		degree_h += deg_h;
	}
	else {
		degree_xz = deg_xz;
		degree_h = deg_h;
	}
	need_to_refresh = true;
}

void drawObject::lightDegreeUpdate(float deg_xz, float deg_h, bool isRelative) {
	if (isRelative) {
		light_degree_xz += deg_xz;
		light_degree_h += deg_h;
	}
	else {
		light_degree_xz = deg_xz;
		light_degree_h = deg_h;
	}
	need_to_refresh = true;
}

void drawObject::blockColorUpdate(int r, int g, int b, bool isRelative) {
	if (isRelative) {
		glm::vec3 new_color(draw_color.r, draw_color.g, draw_color.b);
		new_color += glm::vec3(r, g, b);
		draw_color = ofColor(new_color.x, new_color.y, new_color.z);
	}
	else {
		draw_color = ofColor(r, g, b);
	}
	need_to_refresh = true;
}

void drawObject::camDistUpdate(int d, bool isRelative) {
	if (isRelative) {
		cam_dist += d;
	}
	else {
		cam_dist = d;
	}
	need_to_refresh = true;
}
