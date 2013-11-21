#include "LocalGraphicsLib.h"
#include "ImageIO.h"
#include <glut.h>
using namespace std;
class DebrisEmitter{
public :

	 DebrisEmitter(const char* file_name_1, const char* file_name_2);
	~DebrisEmitter(void);
	 void debrisEmitterInit();
	 void debrisEmitterDisplay();
	 ImageIO* image1;
	 ImageIO* image2;
	 float	slowdown;									
	 float	zoom;				
	 GLuint	loop;						
	 GLuint	col;						
	 GLuint	delay;						
	 GLuint	texture[2];	
	 bool initFlag;
};
