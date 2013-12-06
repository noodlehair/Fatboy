#include <stdio.h>
#include <stdlib.h>
#include "ImageIO.h"
 

class player{
public:
	player(float a);
	void draw(float x, float y, float z,GLuint texture1, GLuint texture2);
private:
	float size;

};
