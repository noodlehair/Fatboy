#include "LocalGraphicsLib.h"
#include "ImageIO.h"


int LoadGLTextures(ImageIO* the_image,GLuint* texture )									
{
        int Status=FALSE;								
        
			Status=TRUE;								
			glGenTextures(1, texture);				

			glBindTexture(GL_TEXTURE_2D, *texture);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,the_image->getWidth(), the_image->getHeight(), 0, GL_RGB, GL_FLOAT, the_image->getImageDisplayArray());
        

        
        return Status;									
}
