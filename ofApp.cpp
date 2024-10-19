#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 7);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		glm::vec3 vertex = this->draw_mesh.getVertex(i);
		auto noise_value = ofNoise(glm::vec4(vertex * 0.0085, ofGetFrameNum() * 0.01));

		if (noise_value > 0.46 && noise_value < 0.5) {

			vertex = glm::normalize(vertex) * ofMap(noise_value, 0.46, 0.5, 300, 350);
		}
		else if (noise_value > 0.5 && noise_value < 0.56) {

			vertex = glm::normalize(vertex) * 350;
		}
		else if (noise_value > 0.56 && noise_value < 0.6) {

			vertex = glm::normalize(vertex) * ofMap(noise_value, 0.54, 0.58, 350, 300);
		}

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
		this->draw_mesh.addColor(ofColor(0));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.72);

	this->draw_mesh.draw();

	ofSetColor(139, 200);
	this->line_mesh.drawWireframe();

	this->cam.end();

	/*
	int start = 500;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}