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
float x = 0.0f, z = 70.0f, thy = 10.0f;

float door_angle = 0.0f;

// angle for rotating
float angle = 0.0f;
float yangle = 0.0f;

void init(void) {
	// sky color
	glClearColor(0.0, 0.7, 1.0, 1.0);
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

void drawFloor() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(-20, 1, 10);
	glVertex3f(-20, 0, 10);
	glVertex3f(20, 0, 10);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(20, 1, -70);
	glVertex3f(20, 0, -70);
	glVertex3f(20, 0, 10);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, -70);
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 0, -70);
	glVertex3f(20, 0, -70);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 1, 10);
	glVertex3f(-20, 0, 10);
	glVertex3f(-20, 0, -70);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(20, 1, -70);
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 1, 10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(22, 0.5, 12);
	glVertex3f(-22, 0.5, 12);
	glVertex3f(-22, 0, 12);
	glVertex3f(22, 0, 12);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(22, 0.5, 12);
	glVertex3f(22, 0.5, -72);
	glVertex3f(22, 0, -72);
	glVertex3f(22, 0, 12);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(22, 0.5, -72);
	glVertex3f(-22, 0.5, -72);
	glVertex3f(-22, 0, -72);
	glVertex3f(22, 0, -72);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(-22, 0.5, -72);
	glVertex3f(-22, 0.5, 12);
	glVertex3f(-22, 0, 12);
	glVertex3f(-22, 0, -72);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(22, 0.5, 12);
	glVertex3f(22, 0.5, -72);
	glVertex3f(-22, 0.5, -72);
	glVertex3f(-22, 0.5, 12);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(10, 1.5, 0);
	glVertex3f(-10, 1.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(10, 1.5, 0);
	glVertex3f(10, 1.5, -60);
	glVertex3f(10, 0, -60);
	glVertex3f(10, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(10, 1.5, -60);
	glVertex3f(-10, 1.5, -60);
	glVertex3f(-10, 0, -60);
	glVertex3f(10, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(-10, 1.5, -60);
	glVertex3f(-10, 1.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(-10, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(10, 1.5, 0);
	glVertex3f(10, 1.5, -60);
	glVertex3f(-10, 1, -60);
	glVertex3f(-10, 1, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(16, 0.5, 0);
	glVertex3f(-10, 0.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(16, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(16, 0.5, 0);
	glVertex3f(16, 0.5, -60);
	glVertex3f(16, 0, -60);
	glVertex3f(16, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(16, 0.5, -60);
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0, -60);
	glVertex3f(16, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(-10, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(16, 0.5, 0);
	glVertex3f(16, 0.5, -60);
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0.5, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(17, 0.5, 0);
	glVertex3f(-10, 0.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(17, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(17, 0.5, 0);
	glVertex3f(17, 0.5, -60);
	glVertex3f(17, 0, -60);
	glVertex3f(17, 0, 0);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(17, 0.5, -60);
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0, -60);
	glVertex3f(17, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0.5, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(-10, 0, -60);
	glEnd();
	glBegin(GL_QUADS);  // Wall
	glVertex3f(17, 0.5, 0);
	glVertex3f(17, 0.5, -60);
	glVertex3f(-10, 0.5, -60);
	glVertex3f(-10, 0.5, 0);
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
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
void drawRoof() {
	glPushMatrix();
	glTranslatef(0.0f, 16.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);
	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(-20, 1, 10);
	glVertex3f(-20, 0, 10);
	glVertex3f(20, 0, 10);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(20, 1, -70);
	glVertex3f(20, 0, -70);
	glVertex3f(20, 0, 10);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, -70);
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 0, -70);
	glVertex3f(20, 0, -70);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 1, 10);
	glVertex3f(-20, 0, 10);
	glVertex3f(-20, 0, -70);
	glEnd();

	glBegin(GL_QUADS);  // Wall
	glVertex3f(20, 1, 10);
	glVertex3f(20, 1, -70);
	glVertex3f(-20, 1, -70);
	glVertex3f(-20, 1, 10);
	glEnd();

	glBegin(GL_TRIANGLES);  // Triangulo da frente do Telhado
	glVertex3f(-20, 1, 10);
	glVertex3f(0, 7, 10);
	glVertex3f(20, 1, 10);
	glEnd();

	glBegin(GL_POLYGON);  // Lateral esquerda do telhado
	glVertex3f(-20, 1, 10);
	glVertex3f(0, 7, 10);
	glVertex3f(-20, 1, -70);
	glVertex3f(0, 7, -70);
	glEnd();

	glBegin(GL_POLYGON);  // Lateral direita do telhado
	glVertex3f(20, 1, 10);
	glVertex3f(0, 7, 10);
	glVertex3f(0, 7, -70);
	glVertex3f(20, 1, -70);
	glEnd();

	glBegin(GL_TRIANGLES);  // Triangulo de tras do Telhado
	glVertex3f(-20, 1, -70);
	glVertex3f(0, 7, -70);
	glVertex3f(20, 1, -70);
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

	// Draw ground
	glColor3f(0.0, 0.65, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	//drawHouse();
	//drawDoor();
	drawFloor();
	drawDoor();
	drawRoof();
	for (int i = -18; i <= 18; i += 4) {
		draw_cylinder(1, 15, i, 1, 8);
	}
	for (int i = -18; i <= 18; i += 4) {
		draw_cylinder(1, 15, i, 1, -68);
	}
	for (int i = 8; i >= -68; i -= 4) {
		draw_cylinder(1, 15, -18, 1, i);
	}
	for (int i = 8; i >= -68; i -= 4) {
		draw_cylinder(1, 15, 18, 1, i);
	}
	for (int i = -8; i <= 8; i += 4) {
		draw_cylinder(1, 15, i, 1, -2);
	}
	for (int i = -8; i <= 8; i += 4) {
		draw_cylinder(1, 15, i, 1, -58);
	}
	for (int i = -15; i >= -35; i -= 4) {
		draw_cylinder(0.3, 15, -5, 1, i);
	}
	for (int i = -15; i >= -35; i -= 4) {
		draw_cylinder(0.3, 15, 5, 1, i);
	}
	for (int i = -5; i <= 5; i += 2) {
		draw_cylinder(0.3, 15, i, 1, -35);
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

	float fraction = 0.5f;

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
	glutCreateWindow("House 3D");

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
