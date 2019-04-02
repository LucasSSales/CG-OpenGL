//#include <iostream>
//#include <GLUT/glut.h>
#include <GL/gl.h>
#include <GL/glut.h>
//g++ Rotacao.c -o Rotacao -lGL -lGLU -lglut

static int year = 0, day = 0, year2 = 0, day2 = 0;
GLfloat position[4] = {1.0, 1.0, 0.0, 1.0};
void init (void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, position);
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);
  	glEnable(GL_LIGHT1);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	  //glTranslatef(0.0,0.0,0.0);
	  glMaterialfv(GL_FRONT, GL_EMISSION, position);
	  glutSolidSphere(1.0, 20, 16); //desenha o sol
  	glPopMatrix();
	
	glPushMatrix();
		glutSolidSphere(1.0, 20, 16); //desenha o sol
		//glColor3f(1.0, 1.0, 0.0);
		glRotatef((GLfloat) year, 0.0, 1.0, 0.0); //(angulo, x, y, z)
		glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
		glutSolidSphere(0.2, 50, 8); //(diametro, linhas h e v)
	glPopMatrix();

	
	// glPushMatrix();
	// 	glColor3f(1.0, 0.0, 1.0);
	// 	glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
	// 	glTranslatef(2.0, 0.0, 0.0);
	// 	glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
	// 	glutSolidSphere(0.2, 50, 8); //(diametro, linhas h e v)
	// glPopMatrix();//i, 

	//glColor3f(1.0, 0.0, 1.0);

/*	glPushMatrix();
		glRotatef((GLfloat) year2, 0.0, 1.0, 0.0);
		glTranslatef(-2.0, 0.0, 0.0);
		glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
		glutSolidSphere(0.2, 10, 8); //(diametro, linhas h e v)

		glColor3f(1.0, 0.0, 0.0);
		glRotatef((GLfloat) year2, 0.0, 1.0, 0.0);
		//glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat) day2, 0.0, 0.0, 1.0);
		glutSolidSphere(0.05, 10, 8); //(diametro, linhas h e v)

	glPopMatrix();//i, */


	glPushMatrix();

	glPopMatrix();//i, 

	glutSwapBuffers();

}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //posicao da camera

}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'd':
			day = (day + 10) % 360;
			day2 = (day2 + 1) % 360;
			glutPostRedisplay(); //redesenha a cena com novas coordenadas, executado no glutmainloop
			break;
		case 'D':
			day = (day - 10) % 360;
			glutPostRedisplay();
			break;
		case 'y':
			year = (year + 5) % 360;
			year2 = (year2-5) %360;
			glutPostRedisplay();
			break;
		case 'Y':
			year = (year - 5) % 360;
			year2 = (year2+5) %360;
			glutPostRedisplay();
			break;
		case 'z':
			day = (day + 100) % 360;
			year = (year + 50) % 360;
			glutPostRedisplay();
			break;
		case 'Z':
			day = (day - 100) % 360;
			year = (year - 50) % 360;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;	
	}

}



int main(int argc, char *argv[]) {

	glutInit(&argc, argv);									

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);	
	glutInitWindowPosition(100, 100);					
	glutCreateWindow("Rotacao de Planetas");	

	init(); 
	glutDisplayFunc(display);					
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);						
	glutMainLoop();	

	return 0;									

}