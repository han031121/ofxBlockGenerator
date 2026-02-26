#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableDepthTest();

	int i1, i2, i3, i4, i5, i6;
	std::cin >> i1 >> i2 >> i3 >> i4 >> i5 >> i6;

	data = std::make_unique<blockData>(i1, i2, i3, i4, i5, static_cast<double>(i6));
	data->generateBlock();

	blockDrawer.setCellSize(40.0f);
	blockDrawer.setBlockHeight(40.0f);
	blockDrawer.setOrigin(glm::vec3(-data->getMaxCol() * 20.0f, 0.0f, -data->getMaxRow() * 20.0f));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(20);

	if (!data) {
		return;
	}

	cam.begin();
	cam.setDistance(500.0f);
	cam.lookAt(glm::vec3(0.0f, -80.0f, 0.0f));

	blockDrawer.draw(*data);

	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
