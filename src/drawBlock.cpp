#include "drawBlock.h"

void drawObject::setup() {
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	s.useStencil = true;
	s.depthStencilAsTexture = false;
	s.numSamples = 4;
	fbo.allocate(s);

	light.setup();
	light.setDirectional();
	light.setDiffuseColor(ofFloatColor(1.0));
	light.setSpecularColor(ofFloatColor(0.3));

	cam.setFov(cam_fov);
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

void drawObject::setCamera() {
	float size_r = data->getSizeRow() * block_size;
	float size_c = data->getSizeCol() * block_size;
	float size_h = data->getSizeHeight() * block_size;
	float block_radius = 0.5f * sqrt(size_r * size_r + size_c * size_c + size_h * size_h);
	float margin = 1.2;

	float dist = margin * block_radius / std::tan(std::numbers::pi * cam.getFov() / 180 / 2);
	dist = std::max(cam_min_dist, dist);

	cam_center = {
		(data->getSizeRow() - 1) * block_size * 0.5f,
		(data->getSizeHeight() - 1) * block_size * 0.5f,
		-(data->getSizeCol() - 1) * block_size * 0.5f
	};

	cam.orbitDeg(90 + degree_xz, -degree_h, dist, cam_center);
	cam.lookAt(cam_center, {0, 1, 0});

	light.setOrientation(glm::vec3(light_degree_h, 270 + light_degree_xz, 0));

	std::cout << "[ drawBlock ] : degree_xz = " << degree_xz << ", degree_h = " << degree_h;
	std::cout << ", light_degree_xz = " << light_degree_xz << ", light_degree_h = " << light_degree_h << "\n";
	std::cout << "[ drawBlock ] : dist = " << dist << "\n";
	//std::cout << "[ setCamere ] : cam_center = {" << cam_center.x << "," << cam_center.y << "," << cam_center.z << "}\n";
}

void drawObject::render() {
	if (!data)
		return;

	fbo.begin();
	ofClear(255, 255, 255, 255);

	setCamera();

	ofEnableLighting();
	light.enable();

	ofEnableDepthTest();

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
}

void drawObject::saveImage(std::string filename) {
	ofPixels pixels;
	fbo.readToPixels(pixels);
	ofSaveImage(pixels, filename);
};
