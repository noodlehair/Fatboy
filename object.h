#include <stdio.h>
#include <stdlib.h>



class object{
public:
	object(float r, float px, float py, float pz, 
		float cr, float cg, float cb);

	void draw(
		float ambient, float diffuse, float specular, float emission, float shininess,
		float bullit_x, float bullit_y, float bullit_z, bool* ifDraw, float angle, float lookAt_z, bool shoot);

private:
    float radius;
 
    float position_x;
    float position_y;
    float position_z;
 
    float color_r;
    float color_g;
    float color_b;

	bool drawIt;

};
