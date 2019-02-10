/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package opengl;

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
    int x = -1, y = -1;
    float[] rgb = new float[3];
    int width = 1;
    
    
    public GraphicListener(){
        this.glu = new GLU();
    }
    
    public void setColor(float[] rgb){
        this.rgb = rgb;
        //System.out.println(this.rgb[0]+" "+this.rgb[1]+" "+this.rgb[2]);
    }
    
    public void setWidth(int width){
        this.width = width;
        //System.out.println(this.width);
    }
    
    public void draw(int x, int y){

        this.x = x;
        this.y = y;
  
    }


        public void init(GLAutoDrawable drawable) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
            
            gl = drawable.getGL();
            
            gl.glEnable(gl.GL_BLEND);
            gl.glBlendFunc(gl.GL_SOURCE0_ALPHA, gl.GL_ONE_MINUS_SRC_ALPHA);
            
            //parametros de projecao
            gl.glMatrixMode(gl.GL_PROJECTION);
            glu.gluOrtho2D(0, 200, 0, 150);//(left, right, bottom, top);
            
        
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
            
            gl.glBegin(gl.GL_LINES);
                gl.glVertex2f(0, 0);
                gl.glVertex2f(40, 0);
                gl.glVertex2f(40, 0);
                gl.glVertex2f(40, 70);
                gl.glVertex2f(40, 70);
                gl.glVertex2f(100, 100);
            gl.glEnd();
            
            //arquibancada
//            gl.glBegin(gl.GL_LINES);
//            if(this.x!=-1)
//                gl.glVertex2f(this.x, this.y);
//                gl.glVertex2f(x, y);
//            gl.glEnd();
//            draw(this.x, this.y);
            
            gl.glFlush();
            
            
        }

        public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
        }
        
    }
