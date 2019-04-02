#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#define _CRT_SECURE_NO_DEPRECATE
//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// #include <stdlib.h>
#include <string.h>
#//include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <stdio.h>
//#include <math.h>

GLuint texture[3];


struct Image {

	unsigned long sizeX;

	unsigned long sizeY;

	char *data;

};

typedef struct Image Image;


#define checkImageWidth 64

#define checkImageHeight 64


GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void) {

	int i, j, c;

	for (i = 0; i < checkImageWidth; i++) {

		for (j = 0; j < checkImageHeight; j++) {

			c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;

			checkImage[i][j][0] = (GLubyte)c;

			checkImage[i][j][1] = (GLubyte)c;

			checkImage[i][j][2] = (GLubyte)c;

		}

	}

}



int ImageLoad(char *filename, Image *image) {

	FILE *file;

	unsigned long size; // size of the image in bytes.

	unsigned long i; // standard counter.

	unsigned short int planes; // number of planes in image (must be 1)

	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

			   // make sure the file is there.

	errno_t err;
	if ((err = fopen_s(&file, filename, "rb")) !=0) {

		printf("File Not Found : %s\n", filename);

		return 0;

		//_CRT_SECURE_NO_WARNINGS

	}

	// seek through the bmp header, up to the width/height:

	fseek(file, 18, SEEK_CUR);

	// read the width

	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {

		printf("Error reading width from %s.\n", filename);

		return 0;

	}

	//printf("Width of %s: %lu\n", filename, image->sizeX);

	// read the height

	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {

		printf("Error reading height from %s.\n", filename);

		return 0;

	}

	//printf("Height of %s: %lu\n", filename, image->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).

	size = image->sizeX * image->sizeY * 3;

	// read the planes

	if ((fread(&planes, 2, 1, file)) != 1) {

		printf("Error reading planes from %s.\n", filename);

		return 0;

	}

	if (planes != 1) {

		printf("Planes from %s is not 1: %u\n", filename, planes);

		return 0;

	}

	// read the bitsperpixel

	if ((i = fread(&bpp, 2, 1, file)) != 1) {

		printf("Error reading bpp from %s.\n", filename);

		return 0;

	}

	if (bpp != 24) {

		printf("Bpp from %s is not 24: %u\n", filename, bpp);

		return 0;

	}

	// seek past the rest of the bitmap header.

	fseek(file, 24, SEEK_CUR);

	// read the data.

	image->data = (char *)malloc(size);

	if (image->data == NULL) {

		printf("Error allocating memory for color-corrected image data");

		return 0;

	}

	if ((i = fread(image->data, size, 1, file)) != 1) {

		printf("Error reading image data from %s.\n", filename);

		return 0;

	}

	for (i = 0; i<size; i += 3) { // reverse all of the colors. (bgr -> rgb)

		temp = image->data[i];

		image->data[i] = image->data[i + 2];

		image->data[i + 2] = temp;

	}

	// we're done.

	return 1;

}


Image * loadTexture(char *filename) {

	Image *image1;

	// allocate space for texture

	image1 = (Image *)malloc(sizeof(Image));

	if (image1 == NULL) {

		printf("Error allocating space for image");

		exit(0);

	}

	if (!ImageLoad(filename, image1)) {
		printf("kkkkkk");
		exit(1);
	}

	return image1;

}



void myinit(void)

{

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	Image *image1 = loadTexture("GioGio.bmp");
	Image *image2 = loadTexture("yang.bmp");

	if (image1 == NULL || image2 == NULL) {

		printf("Image was not returned from loadTexture\n");

		exit(0);

	}

	makeCheckImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Create Texture

	glGenTextures(3, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture

	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,

		GL_RGB, GL_UNSIGNED_BYTE, image1->data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture

	glTexImage2D(GL_TEXTURE_2D, 0, 4, image2->sizeX, image2->sizeY, 0,

		GL_RGB, GL_UNSIGNED_BYTE, image2->data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);



	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,

		checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &checkImage[0][0][0]);


	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);

}

void draw_cylinder(GLfloat radius, GLfloat height, float px, float py, float pz) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glPushMatrix();
	glTranslatef(px, py, pz);
	//glColor3f(color[0], color[1], color[2]);
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	//glTexCoord2f(0.0, 0.0);
	//glTexCoord2f(1.0, 0.0);
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		double u = angle / (double)2*PI;


		glTexCoord2f(u, 1.0);
		glVertex3f(x, y, height);
		glTexCoord2f(u, 0.0);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	//glTexCoord3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, height);
	glTexCoord3f(radius, 0.0, 0.0);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();
	/** Draw the circle on top of cylinder */

	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
	glPopMatrix();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture[2]);

	//glutSolidTeapot(1.0);
	glPushMatrix();
		//glBindTexture(GL_TEXTURE_2D, texture[2]);
		glRotatef(90, 1.0, 0.0, 0.0);
		//glutSolidCylinder(1, 4, 15, 15);
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	draw_cylinder(1, 1, 0,-1,0);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);

	glVertex3f(1.0, -1.0, 0.0);

	glTexCoord2f(1.0, 0.0);

	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);

	glVertex3f(2.41421, 1.0, -1.41421);

	glTexCoord2f(0.0, 1.0);

	glVertex3f(2.41421, -1.0, -1.41421);

	glEnd();

	glutSwapBuffers();

}


void myReshape(int w, int h) {

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0, 1.0*(GLfloat)w / (GLfloat)h, 1.0, 30.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glTranslatef(0.0, 0.0, -3.6);

}


void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 27: // “esc” on keyboard

		exit(0);

		break;

	default: // “a” on keyboard

		break;

	}

}


int main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Texture Mapping - Programming Techniques");

	myinit();

	glutReshapeFunc(myReshape);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutMainLoop();

	system("pause");
	return 0;

}
