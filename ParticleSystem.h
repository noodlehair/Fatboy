#include "FlameEmitter.h"
#include "FlashEmitter.h"
#include "ShockwaveEmitter.h"
#include "DebrisEmitter.h"
class ParticleSystem{
public :

	 ParticleSystem();
	~ParticleSystem(void);
	// FlameEmitter *flameEmitter;
	///* FlashEmitter *flashEmitter;
	// ShockwaveEmitter *shockwaveEmitter;
	 DebrisEmitter *debrisEmitter;
	 void display();
};