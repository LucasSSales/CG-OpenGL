/*#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>*/

//#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glut.h>
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

void drawBox(float x, float y, float z, float height, float width, float length) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex3f(x + width / 2, y + height, z + length / 2);
	glVertex3f(x + width / 2, y, z + length / 2);
	glVertex3f((x - width / 2), y, z + length / 2);
	glVertex3f((x - width / 2), y + height, z + length / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x + width / 2, y + height, (z - length / 2));
	glVertex3f(x + width / 2, y, (z - length / 2));
	glVertex3f((x - width / 2), y, (z - length / 2));
	glVertex3f((x - width / 2), y + height, (z - length / 2));
	glEnd();

	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f((x - width / 2), y + height, (z + length / 2));
	glVertex3f((x - width / 2), y, (z + length / 2));
	glVertex3f((x - width / 2), y, (z - length / 2));
	glVertex3f((x - width / 2), y + height, (z - length / 2));
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x + width / 2, y + height, (z + length / 2));
	glVertex3f(x + width / 2, y, (z + length / 2));
	glVertex3f(x + width / 2, y, (z - length / 2));
	glVertex3f(x + width / 2, y + height, z - length / 2);
	glEnd();

	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f((x + width / 2), y + height, (z + length / 2));
	glVertex3f(x - width / 2, y + height, z + length / 2);
	glVertex3f(x - width / 2, y + height, z - length / 2);
	glVertex3f((x + width / 2), y + height, z - length / 2);
	glEnd();

	glPopMatrix();
}

void drawDoorBox() {

}


void drawDoor(float x, float y, float z, char angle) {
	glPushMatrix();
	glTranslatef(-x, y, z); 
	glRotatef(angle, 0, 1, 0);
	//	glTranslatef(5, 0, 5);

	if(x>0)
		drawBox(10, 0, 1.5, 150, 20, 3);
	else
		drawBox(-10, 0, 1.5, 150, 20, 3);
	
	//glColor3f(0.7f, 0.7f, 0.65f);
	//glScalef(0.6, 1.1, 0.1f);
	//glutSolidCube(100.0);
	
	glPopMatrix();

}

void drawFloor() {
	//DEGRAUS
	drawDegrau(150, 0, 4, 400);
	drawDegrau(145, 4, 8, 390);
	drawDegrau(140, 8, 12, 380);
	drawDegrau(95, 12, 16, 310);
	drawDegrau(90, 16, 20, 300);

	float h = 150;

	//PAREDES PRINCIPAIS
	drawBox(85, 20, 0, 20+h, 10, 540);
	drawBox(-85, 20, 0, 20+h, 10, 540);

	//DIVISORIA
	drawBox(0, 20, -95, 20+h, 180, 10); //H, W, L

	//BORDAS
	drawBox(50, 20, 245, 20 + h, 60, 10);
	drawBox(50, 20, -245, 20+h, 60, 10);
	drawBox(-50, 20, 245, 20 + h, 60, 10);
	drawBox(-50, 20, -245, 20+h, 60, 10);

	//PEDESTAL DA ESTATUA
	drawBox(0, 20, 0, 20, 40, 40);

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
	glTranslatef(0.0f, 130.0f, 0.0f);
	glColor3f(0.752941f, 0.752941f, 0.752941f);

	glBegin(GL_QUADS);
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
	drawDoor(20, 20, 240, door_angle);
	drawDoor(-20, 20, 240, -door_angle);

	drawDoor(20, 20, -240, -door_angle);
	drawDoor(-20, 20, -240, door_angle);
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



	//COLUNAS INTERNAS DAS VIRGENS
	draw_cylinder(8, h - 8, 40, 20, -150);
	draw_cylinder(8, h - 8, 40, 20, -209);

	draw_cylinder(8, h - 8, -40, 20, -150);
	draw_cylinder(8, h - 8, -40, 20, -209);

	//COLUNA ESTATUA ATENA
	int last = 0;
	for (int i = -58; i < 62; i += 22) {
	last = i;
	draw_cylinder(6, h, i, 12, -50);
	}

	for (int i = -25; i < 240; i += 25) {
	draw_cylinder(6, h, -58, 12, i);
	draw_cylinder(6, h, last, 12, i);
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
