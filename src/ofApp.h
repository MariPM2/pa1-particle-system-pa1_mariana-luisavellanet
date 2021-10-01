#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();
		void sizeUp();
		void sizeDown();
		void increaseVel();
		void decreaseVel();

		void keyPressed  (int key);
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
		
		particleMode currentMode;
		string currentModeStr; 
		int replaykey;
	
		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;

		vector <int> keys;
		bool record = false;
		bool replay = false;
		int counter = 100;
		
};
