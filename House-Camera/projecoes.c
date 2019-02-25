#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[30]={
  0.0, 0.0, 0.0, /*0*/
  0.0, 0.0, 30.0,/*1*/
  0.0, 30.0, 0.0,/*2*/
  30.0, 0.0, 0.0,/*3*/
  0.0, 30.0, 30.0,/*4*/
  30.0, 0.0, 30.0,/*5*/
  30.0, 30.0, 0.0,/*6*/
  30.0, 30.0, 30.0,/*7*/
  15.0, 15.0, 15.0 /*8*/
}; 

static GLubyte frenteIndices[]   = {4, 1, 5, 7};
static GLubyte trasIndices[]     = {2, 6, 3, 0};
static GLubyte esquerdaIndices[] = {4, 2, 0, 1};
static GLubyte fundoIndices[]    = {5, 1, 0, 3};
static GLubyte direitaIndices[]  = {7, 5, 3, 6};
static GLubyte topoIndices[]     = {4, 7, 6, 2};
static GLubyte roof01[]          = {0, 1, 8, 1, 5, 8, 5, 3, 8, 3, 0, 8};

static int camx = 15;
static int camy = 25;
static int camz = 90;

static int px = 15;
static int py = 25;
static int pz = 15;
    
static int eixoy, eixox;
int largura, altura;

int main(int argc, char** argv){
  int i;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (800, 800); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init();
  glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glOrtho (-50, 50, -50, 50, -50 , 50);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  largura=w; 
  altura=h;
}

void display(void){

  glPushMatrix();
  glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
  glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);



  glColor3f (AZUL); /* frente */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, frenteIndices);

  glColor3f (VERMELHO); /* tras */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trasIndices);

  glColor3f (CYAN);
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

  glColor3f (VERDE); /* direita */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, direitaIndices);

  glColor3f (AMARELO); /* topo */
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, topoIndices);


  glColor3f (LARANJA); /* fundo */
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

  glColor3f (AMARELO); /* telhado */
  glTranslatef(0.0f, 30.0f, 0.0f);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, roof01);






  glDisableClientState (GL_VERTEX_ARRAY);

  glPopMatrix();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  /*case 'a':
    printf("%d, %d\n",x,y);
    break;
  case 'y':
    eixoy = (eixoy + 5) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    eixoy = (eixoy - 5) % 360;
    glutPostRedisplay();
    break;
  case 'x':
    eixox = (eixox + 5) % 360;
    glutPostRedisplay();
    break;
  case 'X':
    eixox = (eixox - 5) % 360;
    glutPostRedisplay();
    break;*/
  case 'p':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(15, 25, 90, 15, 25, 15, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'o':
    glLoadIdentity();
    glOrtho (-50, 50, -50, 50, -50 , 50);
    glutPostRedisplay();
    break;
  case 'w':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, --camz, px, py, --pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 's':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, ++camz, px, py, ++pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'd':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(++camx, camy, camz, ++px, py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'a':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(--camx, camy, camz, --px, py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'D':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, camz, --px, py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'A':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, camz, ++px, py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'W':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, camz, px, ++py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'S':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, camz, px, --py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'r':
    camx = 15;
    camy = 25;
    camz = 90;
    px = 15;
    py = 25;
    pz = 15;
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
    gluLookAt(camx, camy, camz, px, py, pz, 0, 1, 0);
    glutPostRedisplay();
    break;
  
  
  
  }
}