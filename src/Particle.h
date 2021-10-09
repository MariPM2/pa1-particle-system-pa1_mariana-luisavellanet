#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_PAUSE
	// PARTICLE_MODE_INCREASE_SIZE
	// PARTICLE_MODE_DECREASE_SIZE
};
enum particleFigure{
	PARTICLE_FIGURE_TRIANGULE,
	PARTICLE_FIGURE_CIRCULE
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setFigure(particleFigure newFigure);
		void setAttractPoints( vector <glm::vec3> * attract );
		void setScale(float newScale);
		void setVelx(float XnewVel);
		void setVely(float YnewVel);
		void setVelz(float ZnewVel);
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();
		float getScale();
		float getvelx();
		float getvely();
		float getvelz();
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;
		particleFigure Figure;
		
		vector <glm::vec3> * attractPoints; 
};
