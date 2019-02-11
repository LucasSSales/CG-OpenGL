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
    
void drowHockeycourtLineEq(int x1, int y1, int x2, int y2, int width){
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
     drowPoit(x2, i, width);
     drowPoit(x1, i, width);
   }
   // Bordas do Campo
   drowCircunferenceSegmentLineEq(x2+radiossegment, y1-radiossegment, radiossegment, 2, width);
   drowCircunferenceSegmentLineEq(x1-radiossegment, y1-radiossegment, radiossegment, 1, width);
   drowCircunferenceSegmentLineEq(x2+radiossegment, y2+radiossegment, radiossegment, 3, width);
   drowCircunferenceSegmentLineEq(x1-radiossegment, y2+radiossegment, radiossegment, 4, width);
   drowLineEq(x2+radiossegment, y1, x1-radiossegment, y1, width);
   drowLineEq(x2+radiossegment, y2, x1-radiossegment, y2, width);
   // Linhas Do Campo
   drowLineEq(x2, y2+radiossegment, x1, y2+radiossegment, width);
   drowLineEq(x2, y1-radiossegment, x1, y1-radiossegment, width);
   drowLineEq(x2, middley, x1, middley, width);
   drowLineEq(x2, (int) (middley + (y1-middley)*(0.3)), x1, (int) (middley + (y1-middley)*(0.3)), width);
   drowLineEq(x2, (int) (middley - (y1-middley)*(0.3)), x1, (int) (middley - (y1-middley)*(0.3)),width);
   //CircunferenciasDoCampo
   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int)(radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   // CirculosCentrais
   drowFullCircunferenceLineEq(middlex, middley, (int) (radiossegment+radiossegment*0.5), width);
   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 1, width);
   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 2, width);
   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 3, width);
   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 4, width);

}
void drowHockeycourtmidPoint(int x1, int y1, int x2, int y2, int width){
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
     drowPoit(x2, i, width);
     drowPoit(x1, i, width);
   }
   // Bordas do Campo
   drowMidPointCircle(x2+radiossegment, y1-radiossegment, radiossegment, 2, width);
   drowMidPointCircle(x1-radiossegment, y1-radiossegment, radiossegment, 1, width);
   drowMidPointCircle(x2+radiossegment, y2+radiossegment, radiossegment, 3, width);
   drowMidPointCircle(x1-radiossegment, y2+radiossegment, radiossegment, 4, width);
   drowLineMidPoint(x2+radiossegment, y1, x1-radiossegment, y1, width);
   drowLineMidPoint(x2+radiossegment, y2, x1-radiossegment, y2, width);
   // Linhas Do Campo
   drowLineMidPoint(x2, y2+radiossegment, x1, y2+radiossegment, width);
   drowLineMidPoint(x2, y1-radiossegment, x1, y1-radiossegment, width);
   drowLineMidPoint(x2, middley, x1, middley, width);
   drowLineMidPoint(x2, (int) (middley + (y1-middley)*(0.3)), x1, (int) (middley + (y1-middley)*(0.3)),width);
   drowLineMidPoint(x2, (int) (middley - (y1-middley)*(0.3)), x1, (int) (middley - (y1-middley)*(0.3)), width);
   //CircunferenciasDoCampo
   drowFullCircunferenceMidPoint((int) (middlex + (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceMidPoint((int) (middlex - (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceMidPoint((int) (middlex - (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   drowFullCircunferenceMidPoint((int) (middlex + (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3), width);
   // CirculosCentrais
   drowFullCircunferenceMidPoint(middlex, middley, (int) (radiossegment+radiossegment*0.5),width);
   drowMidPointCircle(middlex, y2+radiossegment, radiossegment, 1, width);
   drowMidPointCircle(middlex, y2+radiossegment, radiossegment, 2, width);
   drowMidPointCircle(middlex, y1-radiossegment, radiossegment, 3, width);
   drowMidPointCircle(middlex, y1-radiossegment, radiossegment, 4, width);

}



    
}
