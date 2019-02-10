/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package opengl;

import com.sun.org.apache.xpath.internal.functions.Function;
import static java.lang.Math.floor;
import java.util.ArrayList;
import java.util.Vector;
import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.glu.GLU;

/**
 *
 * @author Lucas
 */
public class GraphicListener implements GLEventListener{
    
    static GL gl;
    static GLU glu;
    float[] rgb = new float[3];
    int width = 1;
    HockeyCourtDraw ihc;
    Functions f;
    public String algorithm = "Eq. da Reta";
    private ArrayList<Integer> x = new ArrayList<Integer>();
    private ArrayList<Integer> y = new ArrayList<Integer>();
    
    
    public GraphicListener(){
        this.glu = new GLU();
    }
    
    public void setColor(float[] rgb){
        this.rgb = rgb;
    }
    
    public void setWidth(int width){
        this.width = width;
    }
    
    public void setXY(int x, int y){
        this.x.add(x);
        this.y.add(y);
        System.out.println("popo");
    }
    
    public void draw(){
        for(int i =0; i < this.x.size()-1; i++){
            System.out.println(this.x.get(i)+"   "+this.y.get(i)+"  "+this.x.get(i+1)+"  "+this.y.get(i+1));
            //this.ihc.drowLineEq(this.x.get(i), this.y.get(i), this.x.get(i+1), this.y.get(i+1));
        }
  
    }
    
    public void teste(){
            gl.glBegin(gl.GL_LINES);
                gl.glVertex2f(0, 0);
                gl.glVertex2f(40, 0);
                gl.glVertex2f(40, 0);
                gl.glVertex2f(40, 70);
                gl.glVertex2f(40, 70);
                gl.glVertex2f(100, 100);
            gl.glEnd();
    }


        public void init(GLAutoDrawable drawable) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
            
            gl = drawable.getGL();
            
            gl.glEnable(gl.GL_BLEND);
            gl.glBlendFunc(gl.GL_SOURCE0_ALPHA, gl.GL_ONE_MINUS_SRC_ALPHA);
            
            //parametros de projecao
            gl.glMatrixMode(gl.GL_PROJECTION);
            glu.gluOrtho2D(0, 600, 0, 800);//(left, right, bottom, top);
            //gl.gluOrtho2D(0, width, 0, height);
            
        
        }

        public void display(GLAutoDrawable drawable) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
            //gl.glClear(gl.GL_COLOR_BUFFER_BIT);
            gl = drawable.getGL();
            gl.glClear(gl.GL_COLOR_BUFFER_BIT);
            gl.glClearColor(255,255,255,0);
                 
            //linha
            gl.glLineWidth((float)this.width);
            //cor
            gl.glColor3f(rgb[0], rgb[1], rgb[2]);
            
            this.ihc = new HockeyCourtDraw(gl);
            //this.ihc.teste(this.width);
            
            //this.ihc.drowHockeycourtmidPoint(200, 500, 500, 100);
            
            //if(this.algorithm , Bresenham)
            if(this.algorithm.equals("Eq. da Reta")){
                this.ihc.drowHockeycourtLineEq(150, 700, 450, 100);
            }else if(this.algorithm.equals("Bresenham")){
                this.ihc.drowHockeycourtmidPoint(150, 700, 450, 100);
            }
            
            draw();
            
            
            gl.glFlush();
            
            
        }

        public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
        }
        
    



//
//void drowHockeycourtLineEq(int x1, int y1, int x2, int y2){
//  if(x1 < x2){
//      int aux;
//      aux = x1; 
//      x1 = x2; 
//      x2 = aux;
//  }
//  if(y1 < y2){
//    int aux = y2;
//    y2 = y1; 
//    y1 = aux;
//  }
//  int radiossegment = (x1-x2)/10;
//  int middley = (y1+y2)/2, middlex = (x1+x2)/2;
//
//   for(int i = y1-radiossegment; i > y2+radiossegment; i--)
//   {
//     drowPoit(x2, i, 2);
//     drowPoit(x1, i, 2);
//   }
//   // Bordas do Campo
//   drowCircunferenceSegmentLineEq(x2+radiossegment, y1-radiossegment, radiossegment, 2);
//   drowCircunferenceSegmentLineEq(x1-radiossegment, y1-radiossegment, radiossegment, 1);
//   drowCircunferenceSegmentLineEq(x2+radiossegment, y2+radiossegment, radiossegment, 3);
//   drowCircunferenceSegmentLineEq(x1-radiossegment, y2+radiossegment, radiossegment, 4);
//   drowLineEq(x2+radiossegment, y1, x1-radiossegment, y1);
//   drowLineEq(x2+radiossegment, y2, x1-radiossegment, y2);
//   // Linhas Do Campo
//   drowLineEq(x2, y2+radiossegment, x1, y2+radiossegment);
//   drowLineEq(x2, y1-radiossegment, x1, y1-radiossegment);
//   drowLineEq(x2, middley, x1, middley);
//   drowLineEq(x2, (int) (middley + (y1-middley)*(0.3)), x1, (int) (middley + (y1-middley)*(0.3)));
//   drowLineEq(x2, (int) (middley - (y1-middley)*(0.3)), x1, (int) (middley - (y1-middley)*(0.3)));
//   //CircunferenciasDoCampo
//   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
//   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley - (y1-middley)*(0.6)), (int)(radiossegment+radiossegment*0.3));
//   drowFullCircunferenceLineEq((int) (middlex - (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
//   drowFullCircunferenceLineEq((int) (middlex + (x1-middlex)*0.6), (int) (middley + (y1-middley)*(0.6)), (int) (radiossegment+radiossegment*0.3));
//   // CirculosCentrais
//   drowFullCircunferenceLineEq(middlex, middley, (int) (radiossegment+radiossegment*0.5));
//   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 1);
//   drowCircunferenceSegmentLineEq(middlex, y2+radiossegment, radiossegment, 2);
//   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 3);
//   drowCircunferenceSegmentLineEq(middlex, y1-radiossegment, radiossegment, 4);
//
//}













}
