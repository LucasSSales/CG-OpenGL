/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package opengl;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.media.opengl.GLEventListener;

/**
 *
 * @author Lucas
 */
public class MouseInput implements MouseListener {
    
    public int x, y;
    GraphicListener gl;
    
    public MouseInput(GraphicListener g){
        this.gl = g;
    }

    public void mouseClicked(MouseEvent e) {
//        this.x = e.getX();
//        this.y = e.getY();
//        System.out.println("--");
    }

    public void mousePressed(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        this.x = e.getX();
        this.y = e.getY();
    }

    public void mouseReleased(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public void mouseEntered(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public void mouseExited(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
