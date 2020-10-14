#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	auto depth = 10;
	for (int x = -300; x <= 300; x += 60) {

		for (int y = -300; y <= 300; y += 60) {

			this->setBoxToMesh(this->face, this->frame, glm::vec3(x, y, 0), 60, 60, depth);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth) {

	auto noise_value = glm::vec2(ofNoise(location.x * 0.002 + 300, ofGetFrameNum() * 0.004), ofNoise(location.y * 0.002 + 300, ofGetFrameNum() * 0.004));

	float angle_x = 0;
	if (noise_value.x > 0.3 && noise_value.x < 0.5) { angle_x = ofMap(noise_value.x, 0.3, 0.5, PI, 0); }
	if (noise_value.x > 0.5 && noise_value.x < 0.7) { angle_x = ofMap(noise_value.x, 0.5, 0.7, 0, PI); }
	
	float angle_y = 0;
	if (noise_value.y > 0.3 && noise_value.y < 0.5) { angle_y = ofMap(noise_value.y, 0.3, 0.5, PI, 0); }
	if (noise_value.y > 0.5 && noise_value.y < 0.7) { angle_y = ofMap(noise_value.y, 0.5, 0.7, 0, PI); }

	auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
	auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation_y * rotation_x);

	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation_y * rotation_x);
	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation_y * rotation_x);

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	frame_target.addVertex(location + glm::vec4(width * -0.5, height * 0.5, depth * -0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * 0.5, depth * -0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * 0.5, depth * 0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * -0.5, height * 0.5, depth * 0.5, 0) * rotation_y * rotation_x);

	frame_target.addVertex(location + glm::vec4(width * -0.5, height * -0.5, depth * -0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * -0.5, depth * -0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * -0.5, depth * 0.5, 0) * rotation_y * rotation_x);
	frame_target.addVertex(location + glm::vec4(width * -0.5, height * -0.5, depth * 0.5, 0) * rotation_y * rotation_x);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 1);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 0);

	frame_target.addIndex(index + 4); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 5); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 7);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}