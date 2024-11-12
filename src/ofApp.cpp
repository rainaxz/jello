#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	gridSize = 10;
	spacing = 10.0f;
	k = 9.5f;
	damping = 0.99f;

	camera.setPosition(gridSize * spacing / 2, gridSize * spacing / 2, gridSize * spacing * 8);
	camera.lookAt(ofVec3f(gridSize * spacing / 2, gridSize * spacing / 2, gridSize / 2));


	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			for (int z = 0; z < gridSize; z++) {
				Particle p;
				p.position.set(x, y, z);
				p.position *= spacing;
				p.velocity.set(0, 0, 0);
				p.force.set(0, 0, 0);
				particles.push_back(p);

				std::cout << "Particle at: " << p.position << std::endl;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::update(){

	//reset forces
	for (auto& p : particles) {
		p.force.set(0, 0, 0);
	}

	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			for (int z = 0; z < gridSize; z++) {
				int i = index(x, y, z);
				Particle& p = particles[i];

				for (int dx = -1; dx <= 1; dx++) {
					for (int dy = -1; dy <= 1; dy++) {
						for (int dz = -1; dz <= 1; dz++) {

							if (dx == 0 && dy == 0 && dz == 0) {
								continue;
							}

							int nx = x + dx;
							int ny = y + dy;
							int nz = z + dz;

							if (nx < 0 || ny < 0 || nz < 0 || nx >= gridSize || ny >= gridSize || nz >= gridSize) {
								continue;
							}

							int neighbourIndex = index(nx, ny, nz);
							Particle& neighbour = particles[neighbourIndex];

							ofVec3f delta = p.position - neighbour.position;
							float distance = delta.length();
							float restLength = spacing * sqrt(dx * dx + dy * dy + dz * dz);

							ofVec3f force = -k * (distance - restLength) * delta.normalize();
							p.force += force;
							neighbour.force -= force;
						}
					}
				}
			}
		}
	}

	for (auto& p : particles) {
		ofVec3f acceleration = p.force;
		p.velocity += acceleration;
		p.velocity *= damping;
		p.position += p.velocity;
	}



}

int ofApp::index(int x, int y, int z) {
	return x + (y * gridSize) + (z * gridSize * gridSize);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50);
	ofEnableLighting();
	ofLight light;
	light.setPosition(gridSize* spacing / 2, gridSize* spacing, gridSize* spacing);
	light.enable();

	camera.begin();

	for (auto& p : particles) {
		ofDrawSphere(p.position, spacing * 0.5); 
	}

	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == ' ') {
		for (auto& p : particles) {
			p.position += ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)) * 2;
		}
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
