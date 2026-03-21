#include "ofApp.h"

void ofApp::consoleHelp() {
	std::cout << "\n-----------------------[ HELP ]-----------------------\n";
	std::cout << "- G : Set block data and generate draw object\n";
	std::cout << "- N : Generate new block data object\n";
	std::cout << "- D : Modify camera degree\n";
	std::cout << "- L : Modify light degree\n";
	std::cout << "- C : Modify block color\n";
	std::cout << "- S : Save image as a file\n";
	std::cout << "- ? : Print help\n\n";
	std::cout << "< HOW TO USE >\n";
	std::cout << "1. Generate block data object (press N)\n";
	std::cout << "2. Set block data and generate draw object (press G)\n";
	std::cout << "3. You can modify certain properties (press D, L, C)\n";
	std::cout << "4. Set new block to press G\n";
	std::cout << "------------------------------------------------------\n";
}

//--------------------------------------------------------------
void ofApp::setup(){
	consoleHelp();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (draw_object) {
		draw_object->render();
	}
	printStatus();
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (draw_object) {
		int size = std::min(ofGetWidth(), ofGetHeight()) - 2 * MARGIN;
		draw_object->drawFbo(MARGIN, MARGIN, size, size);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 'g' || key == 'G')
	{
		std::cout << "\n[ ofApp ] Set block data and generate draw object\n";

		if (!block_data) {
			std::cout << "[ ofApp ] Block data is not allocated. Generate block data (press N).\n";
			return;
		}

		int size = std::min(ofGetWidth(), ofGetHeight()) - 2 * MARGIN;

		if (draw_object)
			draw_object.reset();

		block_data->generateBlock();
		draw_object = std::make_unique<drawObject>(block_data.get(), size, size);
		printBlockDataInfo();
		printDrawObjectInfo();
	}

	else if (key == 'd' || key == 'D')
	{
		std::cout << "\n[ ofApp ] Modify cam degree\n";

		if (!draw_object) {
			std::cout << "[ ofApp ] Draw object is not allocated. Generate Draw object (press G).\n";
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
		std::cout << "\n[ ofApp ] Modify light degree\n";

		if (!draw_object) {
			std::cout << "[ ofApp ] Draw object is not allocated. Generate Draw object (press G).\n";
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
		std::cout << "\n[ ofApp ] Modify block color\n";

		int r, g, b;
		std::cout << "block color (R G B) : ";
		std::cin >> r >> g >> b;

		draw_object->blockColorUpdate(r, g, b);
	}

	else if (key == 'n' || key == 'N')
	{
		std::cout << "\n[ ofApp ] Generate block data\n";
		consoleInput();
	}

	else if (key == 's' || key == 'S')
	{
		std::cout << "\n[ ofApp ] Save image as a file\n";
		std::string filename = "image_" + draw_object->getIdentify() + ".jpg";
		draw_object->saveImage(filename);
		std::cout << "[ ofApp ] " << filename << " saved.\n";
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
	if (block_data) {
		draw_object.reset();
		block_data.reset();
	}

	int i1, i2, i3, i4, i5;
	float i6;
	bool i7;

	std::cout << "block count 1 : ";
	std::cin >> i1;
	std::cout << "block count 2 : ";
	std::cin >> i2;
	std::cout << "max row (1~13) : ";
	std::cin >> i3;
	std::cout << "max column (1~13) : ";
	std::cin >> i4;
	std::cout << "max height (1~13) : ";
	std::cin >> i5;
	std::cout << "density (0~100) : ";
	std::cin >> i6;
	std::cout << "allow duplicate (0 or 1) : ";
	std::cin >> i7;

	block_data = std::make_unique<blockData>(i1, i2, i3, i4, i5, i6, i7);
}

//--------------------------------------------------------------

void ofApp::printStatus() {
	std::string level[3] = { "[ Info ] ", "[ Warning ] ", "[ Error ] " };

	if (block_data && block_data->status.isUpdated()) {
		std::string msg = "";
		statusMessage s = block_data->status.getStatus();
		msg += level[(int)s.level] + s.msg + "\n";
		std::cout << msg;
	}
	if (draw_object && draw_object->status.isUpdated()) {
		std::string msg = "";
		statusMessage s = draw_object->status.getStatus();
		msg += level[(int)s.level] + s.msg + "\n";
		std::cout << msg;
	}
}

void ofApp::printBlockDataInfo() {
	if (!block_data)
		return;

	int max_r = block_data->getMaxRow();
	int max_c = block_data->getMaxCol();

	for (int i = 0; i < max_r; i++) {
		std::cout << "\t";
		for (int j = 0; j < max_c; j++) {
			if (block_data->getHeightData(i, j) == 0)
				std::cout << "." << " ";
			else
				std::cout << block_data->getHeightData(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\tblock_count : " << block_data->getBlockCount() << "\n";
	std::cout << "\tsize(r, c, h) : " << block_data->getSizeRow() << " / " << block_data->getSizeCol() << " / " << block_data->getSizeHeight() << "\n";
}

void ofApp::printDrawObjectInfo() {
	if (!draw_object)
		return;

	std::cout << "\tdegree_xz = " << draw_object->getCamDegreeXZ() << ", degree_h = " << draw_object->getCamDegreeH() << "\n";
	std::cout << "\tlight_degree_xz = " << draw_object->getLightDegreeXZ() << ", light_degree_h = " << draw_object->getLightDegreeH() << "\n";
	std::cout << "\tcam_dist = " << draw_object->getCamDist() << "\n";
}
