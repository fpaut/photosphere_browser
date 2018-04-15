/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package glModels;

import static com.jogamp.opengl.GL.*;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;

/**
 *
 * @author user
 */
public class glAxes {
    final float size = 1.0f;
    public void display(GLAutoDrawable gLDrawable) {
        final GL2 gl = gLDrawable.getGL().getGL2();
        
        gl.glColor3ub((byte) 255, (byte)0, (byte)0);
        gl.glBegin(GL_LINE_STRIP);
            gl.glVertex3f(0.0f, 0.0f, 0.0f);
            gl.glVertex3f(size, 0.0f, 0.0f);
            gl.glVertex3f(size * 0.75f, size * 0.25f, 0.0f);
            gl.glVertex3f(size * 0.75f, size * -0.25f, 0.0f);
            gl.glVertex3f(size, 0.0f, 0.0f);
            gl.glVertex3f(0.75f * size, 0.0f, 0.25f * size);
            gl.glVertex3f(0.75f * size, 0.0f, -0.25f * size);
            gl.glVertex3f( size, 0.0f, 0.0f);
        gl.glEnd();
        // Y
        gl.glColor3ub((byte) 0, (byte) 255, (byte) 0);
        gl.glBegin(GL_LINE_STRIP);
            gl.glVertex3f(0.0f, 0.0f, 0.0f);
            gl.glVertex3f(0.0f, size, 0.0f);
            gl.glVertex3f(0.0f, 0.75f * size,0.25f * size);
            gl.glVertex3f(0.0f, 0.75f * size,-0.25f * size);
            gl.glVertex3f(0.0f, size, 0.0f);
            gl.glVertex3f(0.25f * size, 0.75f * size,0.0f);
            gl.glVertex3f(-0.25f * size, 0.75f * size,0.0f);
            gl.glVertex3f(0.0f, size, 0.0f);
        gl.glEnd();
        // Z
        gl.glColor3ub((byte) 0, (byte) 0, (byte) 255);
            gl.glBegin(GL_LINE_STRIP);
            gl.glVertex3f(0.0f, 0.0f, 0.0f);
            gl.glVertex3f(0.0f, 0.0f, size);
            gl.glVertex3f(0.25f * size, 0.0f, 0.75f * size);
            gl.glVertex3f(-0.25f * size, 0.0f, 0.75f * size);
            gl.glVertex3f(0.0f, 0.0f, size);
            gl.glVertex3f(0.0f, 0.25f, 0.75f * size);
            gl.glVertex3f(0.0f, -0.25f, 0.75f * size);
            gl.glVertex3f(0.0f, 0.0f, size);
        gl.glEnd();
        
    }
    
}
