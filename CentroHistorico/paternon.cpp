#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void init(void) {
	// sky color
	glClearColor(0.0, 0.7, 1.0, 1.0);
	//glOrtho(0,0,0,0,0,0);
}


void drawDoor() {
	glPushMatrix();
	glTranslatef(0, 2, -10);
	glRotatef(door_angle, 0, 1, 0);
	glTranslatef(0.3f, 0, 0);
	glColor3f(0.7f, 0.7f, 0.65f);
	glScalef(0.6, 1.1, 0.1f);
	glutSolidCube(10.0);
	glPopMatrix();

}

void drawDegrau(float x, float y1, float y2, float z) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);

	glBegin(GL_QUADS);  // Wall
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

	glColor3f(1.0, 0.753f, 0.753f);
	glBegin(GL_QUADS);  // Chao
	glVertex3f(x, y2, z);
	glVertex3f(x, y2, -z);
	glVertex3f(-x, y2, -z);
	glVertex3f(-x, y2, z);
	glEnd();

	glPopMatrix();
}

void drawWall(float x, float y1, float y2, float z) {

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.1f, 0.0f, 1.0f);

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x, y1, z);
	glVertex3f(x, y2, z);
	glVertex3f(x, y2, -z);
	glVertex3f(x, y1, -z);
	glEnd();

	glPopMatrix();
}

void drawWall2(float x, float y1, float y2, float z) {

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.1f, 1.0f, 0.0f);

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x, y2, z);
	glVertex3f(x, y1, z);
	glVertex3f(-x, y1, z);
	glVertex3f(-x, y2, z);
	glEnd();

	glPopMatrix();
}

void drawWall3(float x1, float x2, float y1, float y2, float z) {

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);  // Wall
	glVertex3f(x1, y2, z);
	glVertex3f(x1, y1, z);
	glVertex3f(x2, y1, z);
	glVertex3f(x2, y2, z);
	glEnd();

	glPopMatrix();
}

void draw_cylinder(GLfloat radius, GLfloat height, float px, float py, float pz) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glPushMatrix();
	glTranslatef(px, py, pz);
	glColor3f(0.0f, 0.0f, 0.65f);
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3f(0.0f, 0.0f, 0.65f);
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

void drawFloor() {
	drawDegrau(150, 0, 4, 400);
	drawDegrau(145, 4, 8, 390);
	drawDegrau(140, 8, 12, 380);
	drawDegrau(95, 12, 16, 310);
	drawDegrau(90, 16, 20, 300);

	float h = 150 +16;

	drawWall(90, 20, h, 270);
	drawWall(80, 20, h, 270);
	drawWall(-80, 20, h, -270);
	drawWall(-90, 20, h, -270);

	drawWall2(80, 20, h, -120);
	drawWall2(80, 20, h, -130);

	drawWall3(90, 80, 20, h, 270);
	drawWall3(90, 80, 20, h, -270);

	drawWall3(-90, -80, 20, h, 270);
	drawWall3(-90, -80, 20, h, -270);
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


	//drawDegrau(140, 8, 12, 380);


	glPushMatrix();
	glTranslatef(0.0f, 160.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);
	glBegin(GL_QUADS);  // Wall
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
	glEnd();

	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);  // Triangulo da frente do Telhado
	glVertex3f(-x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(x, y2, z);
	glEnd();

	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);  // Lateral esquerda do telhado
	glVertex3f(-x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(0, y3, -z);
	glVertex3f(-x, y2, -z);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);  // Lateral direita do telhado
	glVertex3f(x, y2, z);
	glVertex3f(0, y3, z);
	glVertex3f(0, y3, -z);
	glVertex3f(x, y2, -z);
	glEnd();

	glColor3f(1.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);  // Triangulo de tras do Telhado
	glVertex3f(-x, y2, -z);
	glVertex3f(0, y3, -z);
	glVertex3f(x, y2, -z);
	glEnd();

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
	//gluLookAt(0, 350, 5, 0, 0, 0, 0, 1, 0);

	// Draw ground
	glColor3f(0.0, 0.65, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-1000.0f, 0.0f, -1000.0f);
	glVertex3f(-1000.0f, 0.0f, 1000.0f);
	glVertex3f(1000.0f, 0.0f, 1000.0f);
	glVertex3f(1000.0f, 0.0f, -1000.0f);
	glEnd();

	//drawHouse();
	//drawDoor();
	drawFloor();
	//drawDoor();
	drawRoof(140, 0, 30, 80, 380);

	int h = 150;
	//COLUNAS FACHADA
	for (int i = -127; i < 0; i += 35) {
		draw_cylinder(8, h, i, 12, 367);
	}
	for (int i = 127; i > 0; i -= 35) {
		draw_cylinder(8, h, i, 12, 367);
	}
	//COLUNAS FUNDOS
	for (int i = -127; i < 0; i += 35) {
		draw_cylinder(8, h, i, 12, -367);
	}
	for (int i = 127; i > 0; i -= 35) {
		draw_cylinder(8, h, i, 12, -367);
	}
	//COLUNAS LATERIAS
	for (int i = -367; i <= 367; i += 35) {
		draw_cylinder(8, h, 127, 12, i);
	}
	for (int i = -367; i <= 367; i += 35) {
		draw_cylinder(8, h, -127, 12, i);
	}

	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		draw_cylinder(7, h-8, i, 20, 290);
	}
	for (int i = 75; i > 0; i -= 30) {
		draw_cylinder(7, h-8, i, 20, 290);
	}
	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		draw_cylinder(7, h - 8, i, 20, -290);
	}
	for (int i = 75; i > 0; i -= 30) {
		draw_cylinder(7, h - 8, i, 20, -290);
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
