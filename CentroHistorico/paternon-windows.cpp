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

//colors
float brown[3] = { 0.4, 0, 0 };
float brownLight[3] = { 0.6, 0, 0 };
float gold[3] = { 1, 1, 0 };

void init(void) {
	// sky color
	glClearColor(0.0, 0.7, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);
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

void draw_cylinder(GLfloat radius, GLfloat height, float px, float py, float pz, float color[]) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glPushMatrix();
	glTranslatef(px, py, pz);
	glColor3f(color[0], color[1], color[2]);
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

void drawBox(float x, float y, float z, float height, float width, float length, float color[]) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(color[0], color[1], color[2]);

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

	//glColor3f(0.5f, 1.0f, 1.0f);
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

	//glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f((x + width / 2), y + height, (z + length / 2));
	glVertex3f(x - width / 2, y + height, z + length / 2);
	glVertex3f(x - width / 2, y + height, z - length / 2);
	glVertex3f((x + width / 2), y + height, z - length / 2);
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
		drawBox(10, 0, 1.5, 150, 20, 3, color);
	else
		drawBox(-10, 0, 1.5, 150, 20, 3, color);

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

	float wall[3] = { 0.6, 0.6, 0.6 };
	float pedestal[3] = { 0.7, 0.7, 0.7 };
	float ouro[3] = { 1, 1, 0 };

	//PAREDES PRINCIPAIS
	drawBox(85, 20, 0, h, 10, 540, wall);
	drawBox(-85, 20, 0, h, 10, 540, wall);

	//DIVISORIA
	drawBox(0, 20, -95, h, 180, 10, wall); //H, W, L

										   //BORDAS
	drawBox(50, 20, 245, h, 60, 10, wall);
	drawBox(50, 20, -245, h, 60, 10, wall);
	drawBox(-50, 20, 245, h, 60, 10, wall);
	drawBox(-50, 20, -245, h, 60, 10, wall);

	//PEDESTAL DA ESTATUA
	drawBox(0, 20, 0, 3, 85, 55, pedestal);
	drawBox(0, 23, 0, 2, 80, 50, ouro);
	drawBox(0, 25, 0, 12, 77, 48, pedestal);
	drawBox(0, 37, 0, 2, 80, 50, ouro);

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
	glTranslatef(0.0f, 138.0f, 0.0f);
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

	glColor3f(0.6, 0.6, 0.6);
	//glColor3f(0.0f, 1.0f, 1.0f);
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

	float c[3] = { 1,0,0 };
	drawBox(x, y + 5, z, 0.5, 5, 5, c);

	c[0] = 0;
	c[2] = 1;

	drawBox(x - 2, y, z - 2, 5, 1, 1, c);
	drawBox(x - 2, y, z + 2, 5, 1, 1, c);
	drawBox(x + 2, y, z - 2, 5, 1, 1, c);
	drawBox(x + 2, y, z + 2, 5, 1, 1, c);

	drawBox(x - 2, y + 5.5, z - 2, 5, 1, 1, c);
	drawBox(x + 2, y + 5.5, z - 2, 5, 1, 1, c);

	drawBox(x, y + 8, z - 2, 3.5, 5, 1, c);

}


void table(float x, float y, float z) {

	float c[3] = { 0, 1, 0 };

	glPushMatrix();
	draw_cylinder(12, 0.5, x, y + 8.5, z, brownLight);
	draw_cylinder(1.5, 8.9, x, y, z, brown);

	glTranslatef(x, y, z);
	glRotatef(55, 0, 1, 0);
	drawChair(-3, 0, -12);

	glRotatef(-160, 0, 1, 0);
	drawChair(-3, 0, -12);


	glPopMatrix();

}

void tocha(float x, float y, float z) {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);//Brown
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
	GLfloat amb[] = {0.3, 0.3, 0.3, 1.0f }; //intensidade/cor
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//spot light
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
	GLfloat pos0[] = { 00.0f, 5.0f, 400.0f, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	GLfloat direction[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //coordenadas
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0); //angulo
												//GLfloat dif0[] = { 0.5f, 0.5f, 0.5f, 0.0f }; //coordenadas
												//glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);//concentração

	//positioned light
	//GLfloat col0[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //cor
	//GLfloat pos0[] = { 0.0f, 30.0f, 0.0f, 0.0f }; //coordenadas
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, col0);
	//glLightfv(GL_LIGHT0, GL_POSITION, pos0);

	//glShadeModel(GL_SMOOTH);

	//directed light
	//GLfloat col1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //cor
	//GLfloat pos1[] = { -1.0f, 300.0f, 0.5f, 0.0f }; //coordenadas, directed
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, col1);
	//glLightfv(GL_LIGHT1, GL_POSITION, pos1);




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
	float coluna[3] = { 0.5, 0.5, 0.5 };

	//COLUNAS FACHADA
	for (int i = -127; i < 0; i += 35) {
		draw_cylinder(8, h, i, 12, 367, coluna);
	}
	for (int i = 127; i > 0; i -= 35) {
		draw_cylinder(8, h, i, 12, 367, coluna);
	}
	//COLUNAS FUNDOS
	for (int i = -127; i < 0; i += 35) {
		draw_cylinder(8, h, i, 12, -367, coluna);
	}
	for (int i = 127; i > 0; i -= 35) {
		draw_cylinder(8, h, i, 12, -367, coluna);
	}
	//COLUNAS LATERIAS
	for (int i = -367; i <= 367; i += 35) {
		draw_cylinder(8, h, 127, 12, i, coluna);
	}
	for (int i = -367; i <= 367; i += 35) {
		draw_cylinder(8, h, -127, 12, i, coluna);
	}

	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		draw_cylinder(7, h - 8, i, 20, 290, coluna);
	}
	for (int i = 75; i > 0; i -= 30) {
		draw_cylinder(7, h - 8, i, 20, 290, coluna);
	}
	//COLUNAS INTERNAS ENTRADA
	for (int i = -75; i < 0; i += 30) {
		draw_cylinder(7, h - 8, i, 20, -290, coluna);
	}
	for (int i = 75; i > 0; i -= 30) {
		draw_cylinder(7, h - 8, i, 20, -290, coluna);
	}

	//COLUNAS INTERNAS DAS VIRGENS
	draw_cylinder(8, h - 8, 40, 20, -150, coluna);
	draw_cylinder(8, h - 8, 40, 20, -209, coluna);

	draw_cylinder(8, h - 8, -40, 20, -150, coluna);
	draw_cylinder(8, h - 8, -40, 20, -209, coluna);

	//COLUNA ESTATUA ATENA
	int last = 0;
	for (int i = -58; i < 62; i += 22) {
		last = i;
		draw_cylinder(6, h, i, 20, -50, coluna);
	}

	for (int i = -25; i < 240; i += 25) {
		draw_cylinder(6, h, -58, 20, i, coluna);
		draw_cylinder(6, h, last, 20, i, coluna);
	}

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
