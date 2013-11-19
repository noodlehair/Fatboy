#include "LocalGraphicsLib.h"
#include "ImageIO.h"
#include <glut.h>
using namespace std;
class FlashEmitter{
public :

	 FlashEmitter(const char* file_name);
	~FlashEmitter(void);
	 void flashEmitterInit();
	 void flashEmitterDisplay();
	 ImageIO* image;
	 float	slowdown;									
	 float	zoom;				
	 GLuint	loop;						
	 GLuint	col;						
	 GLuint	delay;						
	 GLuint	texture[1];
	
};
