#include "ParticleSystem.h"

ParticleSystem :: ParticleSystem(){
	/*flameEmitter = new FlameEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/falme.ppm");
	flashEmitter = new FlashEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/flash.ppm");
	shockwaveEmitter = new ShockwaveEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/shock.ppm");*/
	debrisEmitter = new DebrisEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris1.ppm",
		                                "C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris2.ppm");

}

ParticleSystem :: ~ParticleSystem(){

	/*delete flameEmitter;
	delete flashEmitter;
	delete shockwaveEmitter;*/
	delete debrisEmitter;

}

void ParticleSystem :: display(){
	///*flashEmitter->flashEmitterDisplay();
	//shockwaveEmitter->shockwaveEmitterDisplay();*/	
	//flameEmitter->flameEmitterDisplay();
    debrisEmitter->debrisEmitterDisplay();
									

}