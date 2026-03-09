#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	consoleHelp();
	std::cout << "[ ofApp ] : generate new block data\n";
	consoleInput();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (img.isAllocated())
		img.draw(MARGIN, MARGIN);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g' || key == 'G') {
		std::cout << "[ ofApp ] : set block data and generate draw object\n";

		int size = std::min(ofGetWidth(), ofGetHeight());

		if (draw_object)
			delete draw_object;

		block_data->generateBlock();
		block_data->printHeightData();
		draw_object = new drawObject(block_data, size - 2 * MARGIN, size - 2 * MARGIN);
	}
	else if (key == 'd' || key == 'D') {
		std::cout << "[ ofApp ] : modify cam degree\n";

		float a, b;
		std::cout << "cam degree_xz : ";
		std::cin >> a;
		std::cout << "cam degree_h : ";
		std::cin >> b;
		draw_object->camDegreeUpdate(a, b);
	}
	else if (key == 'l' || key == 'L') {
		std::cout << "[ ofApp ] : modify cam degree\n";

		float a, b;
		std::cout << "light degree_xz : ";
		std::cin >> a;
		std::cout << "light degree_h : ";
		std::cin >> b;
		draw_object->lightDegreeUpdate(a, b);
	}
	else if (key == 'r' || key == 'R') {
		std::cout << "[ ofApp ] : render blocks\n";

		draw_object->render();
		draw_object->getPixels(pix);
		//std::cout << "[ ofApp ] : pixel created\n";
		std::cout << "[ ofApp ] : " << pix.getWidth() << "x" << pix.getHeight()
				  << " ch=" << pix.getNumChannels()
				  << " size=" << pix.size() << "\n";

		img.setFromPixels(pix);
		//std::cout << "[ ofApp ] : image created\n";
	}
	else if (key == 'n' || key == 'N') {
		cout << "[ ofApp ] : regenerate block data\n";
		consoleInput();
	}
	else if (key == 's' || key == 'S') {
		cout << "[ ofApp ] : save image as a file\n";
		std::string filename = "image_" + block_data->getIdentify() + ".jpg";
		draw_object->saveImage(filename);
		std::cout << "[ ofApp ] : " << filename << " saved\n";
	}
	else if (key == '/' || key == '?') {
		consoleHelp();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::consoleInput() {
	if (block_data)
		delete block_data;

	int i1, i2, i3, i4, i5, i6;
	std::cout << "block count 1 : ";
	std::cin >> i1;
	std::cout << "block count 2 : ";
	std::cin >> i2;
	std::cout << "max row : ";
	std::cin >> i3;
	std::cout << "max column : ";
	std::cin >> i4;
	std::cout << "max height : ";
	std::cin >> i5;
	std::cout << "density : ";
	std::cin >> i6;
	block_data = new blockData(i1, i2, i3, i4, i5, (double)i6);
}

//--------------------------------------------------------------
void ofApp::consoleHelp() {
	std::cout << "\n[ HELP ]\n";
	std::cout << "- G : set block data and generate draw object\n";
	std::cout << "- R : render blocks\n";
	std::cout << "- N : regenerate new block data object\n";
	std::cout << "- D : modify camera degree\n";
	std::cout << "- L : modify light degree\n";
	std::cout << "- S : save image as a file\n";
	std::cout << "- ? : print help\n\n";
}
