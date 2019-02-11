/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package opengl;

import java.util.ArrayList;
import javax.media.opengl.GL;
import static opengl.GraphicListener.gl;

/**
 *
 * @author Lucas
 */
public class Functions {
    
    private GL gl;
    
    public Functions(GL gl){
        this.gl = gl;
    }
    
    void drowPoit(int x, int y, int depth){
      gl.glPushMatrix();
       gl.glBegin(gl.GL_POLYGON);      
         gl.glVertex2i(x,y);
         gl.glVertex2i(x+depth,y);
         gl.glVertex2i(x+depth,y+depth);
         gl.glVertex2i(x,y+depth);
       gl.glEnd();
      gl.glPopMatrix();
    }
    
    void drowLineEq(int x1, int y1, int x2, int y2, int width)
    {
      if(x1 > x2)
      {
        int aux = x1; x1 = x2; x2 = aux;
        aux=y1; y1=y2; y2=aux;
      }
      double a = (double)(y2-y1)/(double)(x2-x1);
      for(int i = x1; i < x2; i++)
      {
        int ypoint = (int)(y1 + a*(double)(i-x1));
        drowPoit(i, ypoint, width);
      }
    }
    void drowCircunferenceSegmentLineEq(int x, int y, int r, int quadrant, int width){
      gl.glPushMatrix();
      gl.glTranslated(x, y, 0);
      if(quadrant == 1) {
        for(int i = 0; i < r; i++){
          int ypoint = (int) Math.floor(Math.sqrt(r*r - i*i));
          drowPoit(i, ypoint, width);
        }
      }
      if(quadrant == 2) {
        for(int i = 0; i < r; i++){
          int ypoint = (int) Math.floor(Math.sqrt(r*r - i*i));
          drowPoit(-i, ypoint, width);
        }
      }
      if(quadrant == 3) {
        for(int i = 0; i < r; i++){
          int ypoint = (int) Math.floor(-Math.sqrt(r*r - i*i));
          drowPoit(-i, ypoint, width);
        }
      }
      if(quadrant == 4) {
        for(int i = 0; i < r; i++){
          int ypoint = (int) Math.floor(-Math.sqrt(r*r - i*i));
          drowPoit(i, ypoint, width);
        }
      }
      gl.glPopMatrix();
    }
    void drowFullCircunferenceLineEq(int x, int y, int r, int width){
        for(int i = 1; i  <= 4; i++) drowCircunferenceSegmentLineEq(x, y, r, i, width);
    }

    void drowLineMidPoint(int x1, int y1, int x2, int y2, int width){
      if(x1 > x2)
      {
        int aux = x1; x1 = x2; x2 = aux;
        aux=y1; y1=y2; y2=aux;
      }
      int dx, dy, incE, incNE, d, x, y;
      dx = x2-x1;
      dy = y2-y1;
      d = 2*dy - dx;
      incE = 2*dy;
      incNE = 2*(dy-dx);
      x = x1;
      y = y1;
     gl.glPushMatrix();
      drowPoit(x, y, width);
      while(x < x2){
        if(d <= 0){
          d += incE;
          x++;
        }else{
          d += incNE;
          x+=1;
          y+=1;
        }
        drowPoit(x, y, width);
      }
      gl.glPopMatrix();
    }
    void drowMidPointCircle(int x1, int y1, int r, int quadrant, int width){
      gl.glPushMatrix();
      gl.glTranslated(x1, y1, 0);
      if(quadrant == 1){
        int x, y;
        float d;

        x = 0;
        y = r;
        d = 5/4 - r;

        drowPoit(x, y, width);
        drowPoit(y, x, width);
        while(y > x){
          if(d < 0){
            d += 2*x+3;
            x++;
          }else{
            d += 2*(x-y)+5;
            x++;
            y--;
          }
          drowPoit(x, y, width);
          drowPoit(y, x, width);
        }
      }
      if(quadrant == 2){
        int x, y;
        float d;

        x = 0;
        y = r;
        d = 5/4 - r;

        drowPoit(-x, y, width);
        drowPoit(-y, x, width);
        while(y > x){
          if(d < 0){
            d += 2*x+3;
            x++;
          }else{
            d += 2*(x-y)+5;
            x++;
            y--;
          }
          drowPoit(-x, y, width);
          drowPoit(-y, x, width);
        }
      }
      if(quadrant == 4){
        int x, y;
        float d;

        x = 0;
        y = r;
        d = 5/4 - r;

        drowPoit(x, -y, width);
        drowPoit(y, -x, width);

        while(y > x){
          if(d < 0){
            d += 2*x+3;
            x++;
          }else{
            d += 2*(x-y)+5;
            x++;
            y--;
          }
          drowPoit(x, -y, width);
          drowPoit(y, -x, width);
        }
      }
      if(quadrant == 3){
        int x, y;
        float d;

        x = 0;
        y = r;
        d = 5/4 - r;

        drowPoit(-y, -x, width);
        drowPoit(-x, -y, width);
        while(y > x){
          if(d < 0){
            d += 2*x+3;
            x++;
          }else{
            d += 2*(x-y)+5;
            x++;
            y--;
          }
          drowPoit(-y, -x, width);
          drowPoit(-x, -y, width);
        }
      }
      gl.glPopMatrix();
    }
    void drowFullCircunferenceMidPoint(int x, int y, int r, int width)
    {
      for(int i = 1; i <= 4; i++) drowMidPointCircle(x, y, r, i, width);
    }
    
}
