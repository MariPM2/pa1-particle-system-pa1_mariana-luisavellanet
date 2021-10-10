#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	//these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		;
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].update();
	}
	if(replay == true){
		if(keys.size() == 0){
			replay = false;
		}
		if(counter==0){
			reverse(keys.begin(), keys.end());
			replaykey = keys.back();
			keyPressed(replaykey);
			keys.pop_back();
			counter = 100;
			reverse(keys.begin(), keys.end());
		}
		else{
			counter--;
		}

	}

	//lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(0, 255, 255), ofColor(0, 0, 128));

	for (unsigned int i = 0; i < p.size(); i++)
	{

		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode. \nPress A to pause. \nPress I to increase size \nPress D to decrease size."
	"\nPress F to speed up. \nPress S to slow down. \nPress R to start and stop recording. \nPress P to replay. \nPress C to cancel replay. \nPress T to change figure to Triangle. \nPress Q to change figure to Circle.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if(replay == true){
		if(key =='C'|| key == 'c'){
			replay = false;
		}
		else if(key != replaykey){
			return;
		}
		key = replaykey;
	}
	if (key == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if (key == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if (key == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
	}
	if (key == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if (key == ' ')
	{
		resetParticles();
	}
	if (key == 'A' || key == 'a')
	{
		currentMode = PARTICLE_MODE_PAUSE;
		currentModeStr = "A - PARTICLE_MODE_PAUSE: Pause particle";
	}
	if (key == 'I' || key == 'i')
	{
		sizeUp();
	}
	if (key == 'D' || key == 'd')
	{
		sizeDown();
	}
	if (key == 'F' || key == 'f')
	{
		increaseVel();
	}
	if (key == 'S' || key == 's')
	{
		decreaseVel();
	}
	if (key == 'R' || key == 'r'){
		currentModeStr = "R - Record: Recording in session";
		record =! record;
	}
	if (record == true){
		keys.push_back(key);
	}
	if (key == 'P'|| key == 'p'){
		currentModeStr = "P-Replay: Recording is being played";
		replay = true;
	}
	if (key == 'Q' || key == 'q'){
		currentModeStr = "Q-Circle: Circle Figure";
		changeParticuleFigure(PARTICLE_FIGURE_CIRCLE);
	}
	if (key == 'T' || key == 't'){
		currentModeStr = "T-Triangle: Triangle Figure";
		changeParticuleFigure(PARTICLE_FIGURE_TRIANGLE);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
//--------------------------------------------------------------
void ofApp::sizeUp()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setScale(3*p[i].getScale());
		
		
	}
}

//--------------------------------------------------------------
void ofApp::sizeDown()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setScale(0.33*p[i].getScale());
	}
}

//--------------------------------------------------------------
void ofApp::increaseVel()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setVelx(4*p[i].getvelx());
		p[i].setVely(4*p[i].getvely());
		p[i].setVelz(4*p[i].getvelz());
	}
}

//--------------------------------------------------------------
void ofApp::decreaseVel()
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setVelx(0.25*p[i].getvelx());
		p[i].setVely(0.25*p[i].getvely());
		p[i].setVelz(0.25*p[i].getvelz());
	}
}
void ofApp::changeParticuleFigure(particleFigure FigureType)
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setFigure(FigureType);
	}
}