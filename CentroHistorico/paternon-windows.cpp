#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include "texture.h"
#define PI 3.141592


/*
* Adaptado de:
*   https://github.com/mdrkb/3D-House-using-OpenGL-and-C-/blob/master/main.cpp
*/

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
float x = 0.0f, z = 600.0f, thy = 30.0f;

float door_angle = 0.0f;

// angle for rotating
float angle = 0.0f;
float yangle = 0.0f;

//colors
float brown[3] = { 0.4, 0, 0 };
float brownLight[3] = { 0.6, 0, 0 };
float gold[3] = { 1, 1, 0 };

GLfloat luz_especular[] = { 0, 30, 0, 1 };
GLfloat objeto_especular[] = { 0, 30, 0, 1 };

//TEXTURAS
GLuint texture[10];


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
	if ((err = fopen_s(&file, filename, "rb")) != 0) {
		printf("File Not Found : %s\n", filename);
		return 0;
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
		exit(1);
	}
	return image1;
}



void init(void) {
	// sky color
	glClearColor(0.0, 0.7, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	Image *image1 = loadTexture("wood.bmp");
	Image *image2 = loadTexture("marmore.bmp");
	Image *image3 = loadTexture("wall2.bmp");
	Image *image4 = loadTexture("wall.bmp");
	Image *image5 = loadTexture("gold.bmp");

	if (image1 == NULL || image3 == NULL || image4 == NULL || image5 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}

	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Create Texture
	glGenTextures(10, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->data);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);

}

void drawDegrau(float x, float y1, float y2, float z) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);


	glBegin(GL_QUADS);  // Wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y2, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-x, y2, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-x, y1, z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y1, z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y2, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y2, -z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y1, -z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y1, z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y2, -z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-x, y2, -z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-x, y1, -z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y1, -z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-x, y2, -z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-x, y2, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-x, y1, z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-x, y1, -z);
	glEnd();

	//glColor3f(1.0, 0.753f, 0.753f);
	glBegin(GL_QUADS);  // Chao
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y2, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y2, -z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-x, y2, -z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-x, y2, z);
	glEnd();

	glPopMatrix();
}

void draw_cylinder(GLfloat radius, GLfloat height, float px, float py, float pz, int tex) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;
	glBindTexture(GL_TEXTURE_2D, texture[tex]);

	/** Draw the tube */
	glPushMatrix();
	glTranslatef(px, py, pz);
	//glColor3f(color[0], color[1], color[2]);
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		double u = angle / (double) PI;
		//glNormal3f(x, y, pz);
		glTexCoord2f(1.0, u);
		glVertex3f(x, y, height);
		glTexCoord2f(0.0, u);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();
	/** Draw the circle on top of cylinder */


	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);

		float radian = angle * (PI / 180.0f);
		float xcos = (float)cos(radian);
		float ysin = (float)sin(radian);
		float tx = xcos * 0.5 + 0.5;
		float ty = ysin * 0.5 + 0.5;
		glTexCoord2f(tx, ty);

		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
	glPopMatrix();
}

void drawBox(float x, float y, float z, float height, float width, float length, int tex) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture[tex]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + width / 2, y + height, z + length / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + width / 2, y, z + length / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f((x - width / 2), y, z + length / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f((x - width / 2), y + height, z + length / 2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + width / 2, y + height, (z - length / 2));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + width / 2, y, (z - length / 2));
	glTexCoord2f(1.0, 1.0);
	glVertex3f((x - width / 2), y, (z - length / 2));
	glTexCoord2f(0.0, 1.0);
	glVertex3f((x - width / 2), y + height, (z - length / 2));
	glEnd();

	//glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f((x - width / 2), y + height, (z + length / 2));
	glTexCoord2f(1.0, 0.0);
	glVertex3f((x - width / 2), y, (z + length / 2));
	glTexCoord2f(1.0, 1.0);
	glVertex3f((x - width / 2), y, (z - length / 2));
	glTexCoord2f(0.0, 1.0);
	glVertex3f((x - width / 2), y + height, (z - length / 2));
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + width / 2, y + height, (z + length / 2));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + width / 2, y, (z + length / 2));
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x + width / 2, y, (z - length / 2));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + width / 2, y + height, z - length / 2);
	glEnd();

	//glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f((x + width / 2), y + height, (z + length / 2));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x - width / 2, y + height, z + length / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x - width / 2, y + height, z - length / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f((x + width / 2), y + height, z - length / 2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f((x + width / 2), y, (z + length / 2));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x - width / 2, y, z + length / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x - width / 2, y, z - length / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f((x + width / 2), y, z - length / 2);
	glEnd();

	glPopMatrix();
}


void drawDoor(float x, float y, float z, char angle) {
	glPushMatrix();
	glTranslatef(-x, y, z);
	glRotatef(angle, 0, 1, 0);
	//	glTranslatef(5, 0, 5);

	float color[3] = { 0.7, 0.7, 0.7 };

	if (x>0)
		drawBox(10, 0, 1.5, 150, 20, 3, 4);
	else
		drawBox(-10, 0, 1.5, 150, 20, 3, 4);

	//glColor3f(0.7f, 0.7f, 0.65f);
	//glScalef(0.6, 1.1, 0.1f);
	//glutSolidCube(100.0);

	glPopMatrix();

}

void drawFloor() {
	//DEGRAUS
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	drawDegrau(150, 0, 4, 400);
	drawDegrau(145, 4, 8, 390);
	drawDegrau(140, 8, 12, 380);
	drawDegrau(95, 12, 16, 310);
	drawDegrau(90, 16, 20, 300);

	float h = 150;

	float wall[3] = { 0.6, 0.6, 0.6 };
	float pedestal[3] = { 0.7, 0.7, 0.7 };
	float ouro[3] = { 1, 1, 0 };

	//PAREDES PRINCIPAIS
	drawBox(85, 20, 0, h, 10, 540, 1);
	drawBox(-85, 20, 0, h, 10, 540, 1);

	//DIVISORIA
	drawBox(0, 20, -95, h, 180, 10, 1); //H, W, L

										   //BORDAS
	drawBox(50, 20, 245, h, 60, 10, 1);
	drawBox(50, 20, -245, h, 60, 10, 1);
	drawBox(-50, 20, 245, h, 60, 10, 1);
	drawBox(-50, 20, -245, h, 60, 10, 1);

	//PEDESTAL DA ESTATUA
	drawBox(0, 20, 0, 3, 85, 55, 1);
	drawBox(0, 23, 0, 2, 80, 50, 4);
	drawBox(0, 25, 0, 12, 77, 48, 1);
	drawBox(0, 37, 0, 2, 80, 50, 4);

}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 2000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawRoof(float x, float y1, float y2, float y3, float z) {

	glPushMatrix();
	glTranslatef(0.0f, 166.7, 0.0f);
	//glColor3f(0.752941f, 0.752941f, 0.752941f);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	drawBox(0,0,0, 20, 280, 750, 3);
	/*glBegin(GL_QUADS);
	glVertex3f(x, y2, z);
	glVertex3f(-x, y2, z);
	glVertex3f(-x, y1, z);
	glVertex3f(x, y1, z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x, y2, z);
	glVertex3f(x, y2, -z);
	glVertex3f(x, y1, -z);
	glVertex3f(x, y1, z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x, y2, -z);
	glVertex3f(-x, y2, -z);
	glVertex3f(-x, y1, -z);
	glVertex3f(x, y1, -z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(-x, y2, -z);
	glVertex3f(-x, y2, z);
	glVertex3f(-x, y1, z);
	glVertex3f(-x, y1, -z);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x, y2, z);
	glVertex3f(x, y2, -z);
	glVertex3f(-x, y2, -z);
	glVertex3f(-x, y2, z);
	glEnd();*/

	glColor3f(0.6, 0.6, 0.6);
	//glColor3f(0.0f, 1.0f, 1.0f);

	x = 140;
	z = 375;
	y2 = 20;
	y3 = 70;

	glBegin(GL_TRIANGLES);  // Triangulo da frente do Telhado
	glVertex3f(-x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(x, y2, z);
	glEnd();

	//glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);  // Lateral esquerda do telhado
	glVertex3f(-x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(0, y3, -z);
	glVertex3f(-x, y2, -z);
	glEnd();

	//glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);  // Lateral direita do telhado
	glVertex3f(x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(0, y3, -z);
	glVertex3f(x, y2, -z);
	glEnd();

	//glColor3f(1.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);  // Triangulo de tras do Telhado
	glVertex3f(-x, y2, -z);
	glVertex3f(0, y3, -z);
	glVertex3f(x, y2, -z);
	glEnd();

	glPopMatrix();

}

void drawChair(float x, float y, float z) {

	drawBox(x, y + 5, z, 0.5, 5, 5, 0);

	drawBox(x - 2, y, z - 2, 5, 1, 1, 0);
	drawBox(x - 2, y, z + 2, 5, 1, 1, 0);
	drawBox(x + 2, y, z - 2, 5, 1, 1, 0);
	drawBox(x + 2, y, z + 2, 5, 1, 1, 0);

	drawBox(x - 2, y + 5.5, z - 2, 5, 1, 1, 0);
	drawBox(x + 2, y + 5.5, z - 2, 5, 1, 1, 0);

	drawBox(x, y + 8, z - 2, 3.5, 5, 1, 0);

}


void table(float x, float y, float z) {
	
	glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, texture[4]);
	draw_cylinder(12, 0.5, x, y + 8.5, z, 2);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	draw_cylinder(1.5, 8.9, x, y, z, 0);

	glTranslatef(x, y, z);
	glRotatef(55, 0, 1, 0);
	drawChair(-3, 0, -12);

	glRotatef(-160, 0, 1, 0);
	drawChair(-3, 0, -12);

	glPopMatrix();

}

void tocha(float x, float y, float z) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//glColor3f(1.0f, 1.0f, 0.0f);//Brown
								//draw_cylinder(2, 0.5, x, y, z, gold);
								//draw_cylinder(1, 12, x, y + 0.5, z, gold);
	glTranslatef(x, y, z);
	glRotatef(-90, 1, 0, 0);
	glutSolidCylinder(2, 0.5, 10, 10);
	glutSolidCylinder(1, 12, 10, 10);
	//glTranslatef(-x, -y, -z);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y + 14, z);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(3.5, 4, 10, 10);
	glPopMatrix();
}

void drawbed(float position_x, float position_y, float position_z, float size) {
	float c[3] = { 0.7,0,0 };

	glPushMatrix();
	glTranslatef(position_x, position_y, position_z);

	drawBox(0, size / 20, 0, size / 10, size / 5, size / 3, 0);
	c[2] = 0.7;
	draw_cylinder((GLfloat) size / 80, (GLfloat)(size / 20) + 1, size / 10 - size / 80, 0, size / 6 - size / 80, 0);
	draw_cylinder((GLfloat)size / 80, (GLfloat)(size / 20) + 1, -size / 10 + size / 80, 0, size / 6 - size / 80, 0);
	draw_cylinder((GLfloat)size / 80, (GLfloat)(size / 20) + 1, -size / 10 + size / 80, 0, -size / 6 + size / 80, 0);
	draw_cylinder((GLfloat)size / 80, (GLfloat)(size / 20) + 1, size / 10 - size / 80, 0, -size / 6 + size / 80, 0);
	c[2] = 0.7;
	c[0] = 0.7;
	drawBox(0, size / 10, (size / 9) - 1, size / 10, size / 7, size / 9, 0);

	glPopMatrix();

}

void renderScene(void) {
	
	// Para ver os objetos em modo polígono (somente os traços)	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();


	// Set the camera    
	gluLookAt(x, thy, z, x + lx, thy + ly, z + lz, 0.0f, 1.0f, 0.0f);


	//Ambient Light
	GLfloat amb[] = { 0.3, 0.3, 0.3, 1.0f }; //intensidade/cor
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

	//spot light
	GLfloat pos0[] = { 100.0f, 300.0f, 600.0f, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	GLfloat direction[] = { -400.0f, 0.0f, 0.0f, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0); //angulo
	GLfloat dif0[] = { 0.4, 0.4, 0.4, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);//concentração

	//positioned light
	GLfloat col1[] = { 0.6f, 0.6f, 0.5f, 1.0f }; //cor
	GLfloat pos1[] = { 150.0f, 90.0f, 80.0f, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, col1);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	//glLightf(GL_LIGHT1, GL_EXPONENT, 5);//concentração

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, objeto_ambiente);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objeto_difusa);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objeto_especular);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, n);

	//glShadeModel(GL_SMOOTH);

	//directed light
	//GLfloat col1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //cor
	//GLfloat pos1[] = { -1.0f, 300.0f, 0.5f, 0.0f }; //coordenadas, directed
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, col1);
	//glLightfv(GL_LIGHT1, GL_POSITION, pos1);



	drawbed(15, 20, -120, 70);
	drawbed(-15, 20, -120, 70);


	// Draw ground
	glColor3f(0.0, 0.65, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-1000.0f, 0.0f, -1000.0f);
	glVertex3f(-1000.0f, 0.0f, 1000.0f);
	glVertex3f(1000.0f, 0.0f, 1000.0f);
	glVertex3f(1000.0f, 0.0f, -1000.0f);
	glEnd();

	//draw_cylinder(5, 25, 0, 200, 500, gold);

	//drawHouse();
	//drawDoor();
	drawFloor();
	drawDoor(20, 20, 240, door_angle);
	drawDoor(-20, 20, 240, -door_angle);

	drawDoor(20, 20, -240, -door_angle);
	drawDoor(-20, 20, -240, door_angle);
	drawRoof(140, 0, 30, 80, 380);

	table(0, 20, -176);

	
	int h = 150;
	float boxh = 5;
	//float coluna[3] = { 0.5, 0.5, 0.5 };

	//COLUNAS FACHADA
	for (int i = -127; i < 0; i += 35) {
		drawBox(i, 12+h, 367, boxh, 18, 18, 2);
		draw_cylinder(8, h, i, 12, 367, 2);
	}
	for (int i = 127; i > 0; i -= 35) {
		drawBox(i, 12 + h, 367, boxh, 18, 18, 2);
		draw_cylinder(8, h, i, 12, 367, 2);
	}
	//COLUNAS FUNDOS
	for (int i = -127; i < 0; i += 35) {
		drawBox(i, 12 + h, -367, boxh, 18, 18, 2);
		draw_cylinder(8, h, i, 12, -367, 2);
	}
	for (int i = 127; i > 0; i -= 35) {
		drawBox(i, 12 + h, -367, boxh, 18, 18, 2);
		draw_cylinder(8, h, i, 12, -367, 2);
	}
	//COLUNAS LATERIAS
	for (int i = -367; i <= 367; i += 35) {
		drawBox(127, 12 + h, i, boxh, 18, 18, 2);
		draw_cylinder(8, h, 127, 12, i, 2);
	}
	for (int i = -367; i <= 367; i += 35) {
		drawBox(-127, 12 + h, i, boxh, 18, 18, 2);
		draw_cylinder(8, h, -127, 12, i, 2);
	}

	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		drawBox(i, 20+h-8, 290, boxh, 18, 18, 2);
		draw_cylinder(7, h-8, i, 20, 290, 2);
	}
	for (int i = 75; i > 0; i -= 30) {
		drawBox(i, 20+h-8, 290, boxh, 18, 18, 2);
		draw_cylinder(7, h-8, i, 20, 290, 2);
	}
	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		drawBox(i, 20+ h-8, -290, boxh, 18, 18, 2);
		draw_cylinder(7, h-8, i, 20, -290, 2);
	}
	for (int i = 75; i > 0; i -= 30) {
		drawBox(i, 20 + h-8, -290, boxh, 18, 18, 2);
		draw_cylinder(7, h-8, i, 20, -290, 2);
	}

	//COLUNAS INTERNAS DAS VIRGENS
	drawBox(40, 20+ h - 8, -150, boxh, 18, 18, 2);
	draw_cylinder(8, h - 8, 40, 20, -150, 2);

	drawBox(40, 20+ h - 8, -209, boxh, 18, 18, 2);
	draw_cylinder(8, h - 8, 40, 20, -209, 2);

	drawBox(-40, 20+ h - 8, -150, boxh, 18, 18, 2);
	draw_cylinder(8, h - 8, -40, 20, -150, 2);

	drawBox(-40, 20+ h - 8, -209, boxh, 18, 18, 2);
	draw_cylinder(8, h - 8, -40, 20, -209, 2);

	//COLUNA ESTATUA ATENA
	float hlim = ((20 + h - 8)/2) - 11;
	int last = 0;
	for (int i = -58; i < 62; i += 22) {
		last = i;
		//baixo
		drawBox(i, 20 + hlim, -50, boxh, 18, 18, 2);
		draw_cylinder(6, hlim, i, 20, -50, 2);

		//cima
		drawBox(i, 20 + h - 8, -50, boxh, 18, 18, 2);
		draw_cylinder(6, h-hlim-11, i, hlim+25, -50, 2);
	}
	drawBox(2, 20 + hlim + 5, -50, 6, 130, 20, 4);


	for (int i = -25; i < 240; i += 25) {
		//em baixo
		drawBox(-58, 20 + hlim, i, boxh, 18, 18, 2);
		draw_cylinder(6, hlim, -58, 20, i, 2);

		drawBox(last, 20 + hlim, i, boxh, 18, 18, 2);
		draw_cylinder(6, hlim, last, 20, i, 2);


		//em cima
		drawBox(-58, 20 + h - 8, i, boxh, 18, 18, 2);
		draw_cylinder(6, h - (hlim + 11), -58, hlim+25, i, 2);

		drawBox(last, 20 + h- 8, i, boxh, 18, 18, 2);
		draw_cylinder(6, h - (hlim + 11), last, hlim+25, i, 2);
	}

	drawBox(-58, 20 + hlim + 5, 90, 6, 20, 300, 4);
	drawBox(last, 20 + hlim + 5, 90, 6, 20, 300, 4);

	for (int i = 70; i < 200; i += 30) {
		tocha(-38, 20, i);
		tocha(last - 20, 20, i);
	}



	glFlush();
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {
	float fraction = 0.5f;
	switch (key) {
	case 'o':
		printf("%.2f %.2f %.2f ", x, z, y);
		if (door_angle <= 118.0f) door_angle += 2.0f;
		glutPostRedisplay();
		break;

	case 'c':
		if (door_angle >= 2.0f) door_angle -= 2.0f;
		glutPostRedisplay();
		break;

	case'w':
		if (thy > 0) thy--;
		break;

	case 's':
		thy++;
		break;

	case 27:
		exit(0);
		break;
	}
}


void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 3.0f;//botar de volta para 1.0f

	switch (key) {

	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Paternon");

	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
