#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	consoleHelp();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (draw_object) {
		draw_object->render();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (draw_object) {
		draw_object->draw(MARGIN, MARGIN);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 'g' || key == 'G')
	{
		std::cout << "[ ofApp ] : Set block data and generate draw object\n";

		if (!block_data) {
			std::cout << "[ ofApp ] : Block data is not allocated. Generate block data (press N).\n";
			return;
		}

		int size = std::min(ofGetWidth(), ofGetHeight()) - 2 * MARGIN;

		if (draw_object)
			delete draw_object;

		block_data->generateBlock();
		block_data->printHeightData();
		block_data->printStatus();
		draw_object = new drawObject(block_data, size, size);
	}

	else if (key == 'd' || key == 'D')
	{
		std::cout << "[ ofApp ] : Modify cam degree\n";

		if (!draw_object) {
			std::cout << "[ ofApp ] : Draw object is not allocated. Generate Draw object (press G).\n";
			return;
		}

		float a, b;
		std::cout << "camera degree_xz : ";
		std::cin >> a;
		std::cout << "camera degree_h : ";
		std::cin >> b;

		draw_object->camDegreeUpdate(a, b);
	}

	else if (key == 'l' || key == 'L')
	{
		std::cout << "[ ofApp ] : Modify light degree\n";

		if (!draw_object) {
			std::cout << "[ ofApp ] : Draw object is not allocated. Generate Draw object (press G).\n";
			return;
		}

		float a, b;
		std::cout << "light degree_xz : ";
		std::cin >> a;
		std::cout << "light degree_h : ";
		std::cin >> b;

		draw_object->lightDegreeUpdate(a, b);
	}

	else if (key == 'c' || key == 'C')
	{
		//change color
		std::cout << "[ ofApp ] : Modify block color\n";

		int r, g, b;
		std::cout << "block color (R G B) : ";
		std::cin >> r >> g >> b;

		draw_object->blockColorUpdate(r, g, b);
	}

	else if (key == 'n' || key == 'N')
	{
		std::cout << "[ ofApp ] : Regenerate block data\n";
		consoleInput();
	}

	else if (key == 's' || key == 'S')
	{
		std::cout << "[ ofApp ] : Save image as a file\n";
		std::string filename = "image_" + draw_object->getIdentify() + ".jpg";
		draw_object->saveImage(filename);
		std::cout << "[ ofApp ] : " << filename << " saved.\n";
	}

	else if (key == '/' || key == '?')
	{
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
	std::cout << "\n-----------------------[ HELP ]-----------------------\n";
	std::cout << "- G : Set block data and generate draw object\n";
	std::cout << "- N : Regenerate new block data object\n";
	std::cout << "- D : Modify camera degree\n";
	std::cout << "- L : Modify light degree\n";
	std::cout << "- C : Modify block color\n";
	std::cout << "- S : Save image as a file\n";
	std::cout << "- ? : Print help\n\n";
	std::cout << "HOW TO USE\n";
	std::cout << "1. Generate block data object (press N)\n";
	std::cout << "2. Set block data and generate draw object (press G)\n";
	std::cout << "3. You can modify certain properties (press D, L, C)\n";
	std::cout << "4. Generate new block to press G\n";
	std::cout << "------------------------------------------------------\n\n";
}
