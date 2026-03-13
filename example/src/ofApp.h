#pragma once

#include "ofMain.h"
#include "ofxBlockGenerator.h"

#define MARGIN 20
#define WINDOW_SIZE 1200

class ofApp : public ofBaseApp{

	public:
		blockData* block_data = nullptr;
		drawObject* draw_object = nullptr;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void consoleInput();
		void consoleHelp();
};
