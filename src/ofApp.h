#pragma once

#include "ofMain.h"

struct Particle {

	ofVec3f position;
	ofVec3f velocity;
	ofVec3f force;

};

class ofApp : public ofBaseApp{

	public:
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

		int gridSize;
		float spacing;
		float k;
		float damping;

		std::vector<Particle> particles;
		
		int index(int x, int y, int z);
		ofCamera camera;
		
};
