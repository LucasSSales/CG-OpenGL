#ifndef texture_h
#define texture_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Image Image;

struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};


void makeCheckImage();
int ImageLoad(char *filename, Image *image);
Image * loadTexture(char *filename);
 
#endif