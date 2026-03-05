#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	int i1, i2, i3, i4, i5, i6;
	std::cin >> i1 >> i2 >> i3 >> i4 >> i5 >> i6;
	block_data = new blockData(i1, i2, i3, i4, i5, (double)i6);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (img.isAllocated())
		img.draw(30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') {
		std::cout << "[ ofApp ] : generate new block data and draw object\n";
		if (draw_object)
			delete draw_object;

		block_data->generateBlock();
		block_data->printHeightData();
		draw_object = new drawObject(block_data, 600, 600);
	}
	else if (key == 'f') {
		std::cout << "[ ofApp ] : modify degree\n";

		float a, b;
		std::cout << "degree_xz : ";
		std::cin >> a;
		std::cout << "degree_h : ";
		std::cin >> b;
		draw_object->degreeUpdate(a, b);
	}
	else if (key == 'r') {
		std::cout << "[ ofApp ] : render blocks\n";

		draw_object->render();
		draw_object->getPixels(pix);
		std::cout << "[ ofApp ] : pixel created\n";
		std::cout << pix.getWidth() << "x" << pix.getHeight()
				  << " ch=" << pix.getNumChannels()
				  << " size=" << pix.size() << "\n";

		img.setFromPixels(pix);
		std::cout << "[ ofApp ] : image created\n";
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
