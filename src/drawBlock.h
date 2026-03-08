#pragma once

#include "blockGenerator.h"
#include "ofMain.h"

class drawObject {

	private:
		int block_size = 100;
		int width;
		int height;

		float degree_xz;
		float degree_h;
		float light_degree_xz;
		float light_degree_h;
		float thickness;

		int cam_fov = 30;
		float cam_min_dist = 1700;
		glm::vec3 cam_center;

		blockData * data = nullptr;

		ofColor draw_color = ofColor(220, 185, 154);
		ofFbo fbo;
		ofEasyCam cam;
		ofLight light;

		void setup();

		void drawBlocks(); //draw blocks on fbo
		void drawOutline();
		void drawSingleOutline(int r, int c, int h);

		void setCamera();

	public:
		drawObject(blockData* _d, int _w, int _h, int _dxz = 25, int _dh = 20, int _ldxz = 25, int _ldh = 38, int _t = 2)
			: data(_d), width(_w), height(_h),
			degree_xz(_dxz), degree_h(_dh), light_degree_xz(_ldxz), light_degree_h(_ldh), thickness(_t) {
				setup();
			}

		void render(); //draw and render blocks on fbo
		void saveImage(std::string filename); //save PNG

		void getPixels(ofPixels & pixels) {
			fbo.readToPixels(pixels);
		}
		void camDegreeUpdate(float deg_xz, float deg_h) {
			degree_xz = deg_xz;
			degree_h = deg_h;
		}
		void lightDegreeUpdate(float deg_xz, float deg_h) {
			degree_xz = deg_xz;
			degree_h = deg_h;
		}
};
