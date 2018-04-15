/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package glModels;

import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;

/**
 *
 * @author user
 */
public class glQuad {
        static float rotateT = 0.0f;
   public void display(GLAutoDrawable gLDrawable) {
        final GL2 gl = gLDrawable.getGL().getGL2();
        gl.glClear(GL.GL_COLOR_BUFFER_BIT);
        gl.glClear(GL.GL_DEPTH_BUFFER_BIT);
        gl.glLoadIdentity();
        gl.glTranslatef(0.0f, 0.0f, -5.0f);

        // rotate about the three axes
        gl.glRotatef(rotateT, 1.0f, 0.0f, 0.0f);
        gl.glRotatef(rotateT, 0.0f, 1.0f, 0.0f);
        gl.glRotatef(rotateT, 0.0f, 0.0f, 1.0f);

        // Draw A Quad
        gl.glBegin(GL2.GL_QUADS);       
        gl.glColor3f(0.0f, 1.0f, 1.0f);   // set the color of the quad
        gl.glVertex3f(-1.0f, 1.0f, 0.0f);   // Top Left
        gl.glVertex3f( 1.0f, 1.0f, 0.0f);   // Top Right
        gl.glVertex3f( 1.0f,-1.0f, 0.0f);   // Bottom Right
        gl.glVertex3f(-1.0f,-1.0f, 0.0f);   // Bottom Left
        // Done Drawing The Quad
        gl.glEnd();                                                     

        // increasing rotation for the next iteration
        rotateT += 0.2f;
    }
    
}
