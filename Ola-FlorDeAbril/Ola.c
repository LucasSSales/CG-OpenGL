//#include <Windows.h>
//#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
//g++ Ola.c -o Ola -lGL -lGLU -lglut

static int hy[6] = {100, 100, 100, 100, 100, 100}, wy[6] = {0, 0, 0, 0, 0, 0};
static bool active[6] = {1, 0, 0, 0, 0, 0}, dir[6] = {1, 0, 0, 0, 0, 0};

void init (void)
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glMatrixMode (GL_MODELVIEW); //Projecao 2D

  gluOrtho2D (0.0, 600.0, 0.0, 400.0); //Definindo os limites da Porta de Visao (ViewPort)

}

void ola(){
	for (int i = 0; i < 6; i++){
		if(active[i] == 1){
			if(dir[i] == 1){
				wy[i] += 10;
				hy[i] += 10;
			}else{
				wy[i] -= 10;
				hy[i] -= 10;
			}
		}

		if(i > 0 && wy[i-1] == 30){
			active[i] = 1;
		}

		if(wy[i] == 100){
			dir[i] = 0;
		}

		if(wy[i] == 0){
			dir[i] = 1;
		}
	}
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
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
void displayRet(void){
	
	//limpa o display
	glClear(GL_COLOR_BUFFER_BIT); 

	//Retangulo 01
	glColor3f(0.0, 0.0, 1.0);		 
	glRecti(0, wy[0], 100, hy[0]);

	//Retangulo 02
	glColor3f(1.0, 0.0, 0.0);
	glRecti(100, wy[1], 200, hy[1]);

	//Retangulo 03
	glColor3f(0.0, 1.0, 0.0);
	glRecti(200, wy[2], 300, hy[2]);

	//Retangulo 04
	glColor3f(1.0, 0.0, 1.0);
	glRecti(300, wy[3], 400, hy[3]);

	//Retangulo 05
	glColor3f(1.0, 1.0, 0.0);
	glRecti(400, wy[4], 500, hy[4]);

	//Retangulo 06
	glColor3f(0.0, 1.0, 1.0);
	glRecti(500, wy[5], 600, hy[5]);

    //executa os comandos
	glFlush();

}

int main(int argc, char *argv[]) {
	
	/* inicializa o sitema GLUT */
	glutInit(&argc, argv);									

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600,400);						
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
