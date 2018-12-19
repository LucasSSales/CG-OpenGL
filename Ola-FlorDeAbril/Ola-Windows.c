#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//#include <GL/gl.h>
//#include <GL/glut.h>
//#include <stdlib.h>
//g++ Ola.c -o Ola -lGL -lGLU -lglut

static const int squares = 20;
static int hy[squares], wy[squares];
static bool active[squares], dir[squares];
static int height = 800 / squares;

void init(void)
{
	/* selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW); //Projecao 2D

	gluOrtho2D(0.0, 800.0, 0.0, 400.0); //Definindo os limites da Porta de Visao (ViewPort)

}

void ola() {

	for (int i = 0; i < squares; i++) {
		if (active[i] == 1) {
			if (dir[i] == 1) {
				wy[i] += 10;
				hy[i] += 10;
			}
			else {
				wy[i] -= 10;
				hy[i] -= 10;
			}
		}

		if (i > 0 && hy[i - 1] == 30) {
			active[i] = 1;
		}

		if (hy[i] == 100) {
			dir[i] = 0;
		}

		if (hy[i] == 0) {
			dir[i] = 1;
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		ola();
		glutPostRedisplay(); //redesenha a cena com novas coordenadas, executado no glutmainloop
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}

}

//desenha as transformacoes
void displayRet(void) {

	//limpa o display
	glClear(GL_COLOR_BUFFER_BIT);

	int x = 0;
	double z = 0;
	for (int i = 0; i < squares; i++) {
		glColor3f(0.0, (GLfloat) z, 1.0);
		glRecti(x, wy[i], x + height, hy[i]);
		x += height;
		z = (z + 0.05);
	}

	//executa os comandos
	glFlush();

}

int main(int argc, char *argv[]) {

	for (int i = 0; i < squares; i++) {
		hy[i] = 0;
		wy[i] = height;
		active[i] = 0;
		dir[i] = 0;
	}

	active[0] = 1;
	dir[0] = 1;

	/* inicializa o sitema GLUT */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Ola");



	//chama a funcao init e inicia as propriedades View Port
	init();
	/* Callback para mostrar objetos na tela */
	glutDisplayFunc(displayRet);
	/* Callback para para interagir com teclado */
	glutKeyboardFunc(keyboard);
	/* inicia o processamento dos eventos... */
	glutMainLoop();

}
