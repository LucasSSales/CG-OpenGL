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
    int width = 2;
    HockeyCourtDraw ihc;
    Functions f;
    public String algorithm = "Eq. da Reta";
    private ArrayList<Integer> xr = new ArrayList<Integer>();
    private ArrayList<Integer> yr = new ArrayList<Integer>();
    private ArrayList<Integer> xl = new ArrayList<Integer>();
    private ArrayList<Integer> yl = new ArrayList<Integer>();
        
    
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
        if(x < 106){
            if(this.xl.size()==2)
                return;
            this.xl.add(x);
            this.yl.add(y);
        }else if(x > 353){
            if(this.xr.size()==2)
                return;
            this.xr.add(x);
            this.yr.add(y);
        }
    }
    
    public void clear(){
        this.xl = new ArrayList<Integer>();
        this.yl = new ArrayList<Integer>();
        this.xr = new ArrayList<Integer>();
        this.yr = new ArrayList<Integer>();
    }
    
    public void drawBres(int width){
        if(this.xl.size()==2){
            this.ihc.drowLineMidPoint(this.xl.get(0), this.yl.get(0), this.xl.get(1), this.yl.get(0), width);
            this.ihc.drowLineMidPoint(this.xl.get(0), this.yl.get(1), this.xl.get(1), this.yl.get(1), width);
            for(int i = this.yl.get(0); i > this.yl.get(1); i--){
                this.ihc.drowPoit(this.xl.get(1), i, width);
                this.ihc.drowPoit(this.xl.get(0), i, width);
            }
        }
        
        if(this.xr.size()==2){
            this.ihc.drowLineMidPoint(this.xr.get(0), this.yr.get(0), this.xr.get(1), this.yr.get(0), width);
            this.ihc.drowLineMidPoint(this.xr.get(0), this.yr.get(1), this.xr.get(1), this.yr.get(1), width);
            for(int i = this.yr.get(0); i > this.yr.get(1); i--){
                this.ihc.drowPoit(this.xr.get(1), i, width);
                this.ihc.drowPoit(this.xr.get(0), i, width);
            }
        }  
    }
    
    public void drawEq(int width){
        if(this.xl.size()==2){
            this.ihc.drowLineEq(this.xl.get(0), this.yl.get(0), this.xl.get(1), this.yl.get(0), width);
            this.ihc.drowLineEq(this.xl.get(0), this.yl.get(1), this.xl.get(1), this.yl.get(1), width);
            for(int i = this.yl.get(0); i > this.yl.get(1); i--){
                this.ihc.drowPoit(this.xl.get(1), i, width);
                this.ihc.drowPoit(this.xl.get(0), i, width);
            }
        }
        
        if(this.xr.size()==2){
            this.ihc.drowLineEq(this.xr.get(0), this.yr.get(0), this.xr.get(1), this.yr.get(0), width);
            this.ihc.drowLineEq(this.xr.get(0), this.yr.get(1), this.xr.get(1), this.yr.get(1), width);
            for(int i = this.yr.get(0); i > this.yr.get(1); i--){
                this.ihc.drowPoit(this.xr.get(1), i, width);
                this.ihc.drowPoit(this.xr.get(0), i, width);
            }
        }  
    }

    public void init(GLAutoDrawable drawable) {
        gl = drawable.getGL();
        gl.glEnable(gl.GL_BLEND);
        gl.glBlendFunc(gl.GL_SOURCE0_ALPHA, gl.GL_ONE_MINUS_SRC_ALPHA);
        //parametros de projecao
        gl.glMatrixMode(gl.GL_PROJECTION);
        glu.gluOrtho2D(0, 460, 540, 0);
    }

        public void display(GLAutoDrawable drawable) {
            gl = drawable.getGL();
            gl.glClear(gl.GL_COLOR_BUFFER_BIT);
            gl.glClearColor(255,255,255,0);
            //espessura
            gl.glLineWidth((float)this.width);
            //cor
            gl.glColor3f(rgb[0], rgb[1], rgb[2]);
            this.ihc = new HockeyCourtDraw(gl);
            //algoritmos
            if(this.algorithm.equals("Eq. da Reta")){
                this.ihc.drowHockeycourtLineEq(100, 500, 360, 40, width);
                drawEq(this.width);
            }else if(this.algorithm.equals("Bresenham")){
                this.ihc.drowHockeycourtmidPoint(100, 500, 360, 40, width);
                drawBres(this.width);
            }   
            gl.glFlush();
        }

        public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
            
        }
}
