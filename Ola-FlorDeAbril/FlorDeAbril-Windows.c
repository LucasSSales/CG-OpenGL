//FLOR DE ABRIL
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//g++ FlorDeAbril.c -o FlorDeAbril -lGL -lGLU -lglut

static int ang = 0;

void init(void)
{
	/* selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW); //Projecao 2D
	gluOrtho2D(0.0, 600.0, 0.0, 400.0); //Definindo os limites da Porta de Visao (ViewPort)
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);

	//BASE
	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glRecti(295, 0, 305, 250);
	glPopMatrix();

	//PETALAS
	glPushMatrix();
	glTranslatef(300, 250, 0);
	glRotatef((GLfloat) ang, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1.0);
	for (int i = 0; i<4; i++) {
		glRotated(90, 0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(100, 30);
		glVertex2f(100, -30);
		glEnd();
	}
	glPopMatrix();

	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		ang = (ang + 5) % 360; //aletera o angulo para rotação
		glutPostRedisplay(); //redesenha a cena com novas coordenadas, executado no glutmainloop
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	//glutInitWindowPosition(100, 100);					
	glutCreateWindow("Flor de Abril");
	init();
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);					
	glutMainLoop();
	return 0;
}