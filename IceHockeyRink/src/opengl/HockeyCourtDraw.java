/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package opengl;

import static java.lang.Math.floor;
import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.glu.GLU;
import static opengl.GraphicListener.gl;

/**
 *
 * @author Lucas
 */
public class HockeyCourtDraw extends Functions {
    
    final int width = 800, height = 600;
    private GL gl;

    public HockeyCourtDraw(GL gl) {
        super(gl);
        this.gl = gl;
    }
    
    public void teste(int width){
        
        drowPoit(400, 400, width);
    }
    
    
    
void drowHockeycourtLineEq(int x1, int y1, int x2, int y2){
  if(x1 < x2){
      int aux;
      aux = x1; 
      x1 = x2; 
      x2 = aux;
  }
  if(y1 < y2){
    int aux = y2;
    y2 = y1; 
    y1 = aux;
  }
  int radiossegment = (x1-x2)/10;
  int middley = (y1+y2)/2, middlex = (x1+x2)/2;

   for(int i = y1-radiossegment; i > y2+radiossegment; i--)
   {
     drowPoit(x2, i, 2);
     drowPoit(x1, i, 2);
   }
   // Bordas do Campo
   drowCircunferenceSegmentLineEq(x2+radiossegment, y1-radiossegment, radiossegment, 2);
   drowCircunferenceSegmentLineEq(x1-radiossegment, y1-radiossegment, radiossegment, 1);
   drowCircunferenceSegmentLineEq(x2+radiossegment, y2+radiossegment, radiossegment, 3);
   drowCircunferenceSegmentLineEq(x1-radiossegment, y2+radiossegment, radiossegment, 4);
   drowLineEq(x2+radiossegment, y1, x1-radiossegment, y1);
   drowLineEq(x2+radiossegment, y2, x1-radiossegment, y2);
   // Linhas Do Campo
   drowLineEq(x2, y2+radiossegment, x1, y2+radiossegment);
   drowLineEq(x2, y1-radiossegment, x1, y1-radiossegment);
   drowLineEq(x2, middley, x1, middley);
   drowLineEq(x2, (int) (middley + (y1-middley)*(0.3)), x1, (int) (middley + (y1-middley)*(0.3)));
   drowLineEq(x2, (int) (middley - (y1-middley)*(0.3)), x1, (int) (middley - (y1-middley)*(0.3)));
   //CircunferenciasDoCampo
   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int)(radiossegment+radiossegment*0.3));
   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   // CirculosCentrais
   drowFullCircunferenceLineEq(middlex, middley, (int) (radiossegment+radiossegment*0.5));
   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 1);
   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 2);
   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 3);
   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 4);

}
void drowHockeycourtmidPoint(int x1, int y1, int x2, int y2){
  if(x1 < x2){
      int aux;
      aux = x1; 
      x1 = x2; 
      x2 = aux;
  }
  if(y1 < y2){
    int aux = y2;
    y2 = y1;
    y1 = aux;
  }
  int radiossegment = (x1-x2)/10;
  int middley = (y1+y2)/2, middlex = (x1+x2)/2;
  

   for(int i = y1-radiossegment; i > y2+radiossegment; i--)
   {
     drowPoit(x2, i, 2);
     drowPoit(x1, i, 2);
   }
   // Bordas do Campo
   drowMidPointCircle(x2+radiossegment, y1-radiossegment, radiossegment, 2);
   drowMidPointCircle(x1-radiossegment, y1-radiossegment, radiossegment, 1);
   drowMidPointCircle(x2+radiossegment, y2+radiossegment, radiossegment, 3);
   drowMidPointCircle(x1-radiossegment, y2+radiossegment, radiossegment, 4);
   drowLineMidPoint(x2+radiossegment, y1, x1-radiossegment, y1);
   drowLineMidPoint(x2+radiossegment, y2, x1-radiossegment, y2);
   // Linhas Do Campo
   drowLineMidPoint(x2, y2+radiossegment, x1, y2+radiossegment);
   drowLineMidPoint(x2, y1-radiossegment, x1, y1-radiossegment);
   drowLineMidPoint(x2, middley, x1, middley);
   drowLineMidPoint(x2, (int) (middley + (y1-middley)*(0.3)), x1, (int) (middley + (y1-middley)*(0.3)));
   drowLineMidPoint(x2, (int) (middley - (y1-middley)*(0.3)), x1, (int) (middley - (y1-middley)*(0.3)));
   //CircunferenciasDoCampo
   drowFullCircunferenceMidPoint((int) (middlex + (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   drowFullCircunferenceMidPoint((int) (middlex - (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   drowFullCircunferenceMidPoint((int) (middlex - (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   drowFullCircunferenceMidPoint((int) (middlex + (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
   // CirculosCentrais
   drowFullCircunferenceMidPoint(middlex, middley, (int) (radiossegment+radiossegment*0.5));
   drowMidPointCircle(middlex, y2+radiossegment, radiossegment, 1);
   drowMidPointCircle(middlex, y2+radiossegment, radiossegment, 2);
   drowMidPointCircle(middlex, y1-radiossegment, radiossegment, 3);
   drowMidPointCircle(middlex, y1-radiossegment, radiossegment, 4);

}

void display()
{
// gl.glClear(gl.GL_COLOR_BUFFER_BIT);
// gl.glColor3f(0.0f, 1.0f, 0.0f);
// drowHockeycourtLineEq(300, 500, 500, 100);
// drowHockeycourtmidPoint(300, 500, 500, 100);
// gl.glFlush();
}

//void init()
//{
//  gl.gluOrtho2D(0, width, 0, height);
//}
//int main(int argc, char **argv)
//{
//  glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(width, height);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("Input");
//    init();
//  glutDisplayFunc(display);
//  // glutKeyboardFunc(keyboardHandler);
//  // glutPassiveMotionFunc(passiveMotionHandler);
//  // glutTimerFunc(10, scheduleUpdate, 1);
//glutMainLoop();
//
// return 0;
//}
    
}
