/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "glmodels.h"

//----------------------------------------------------------------------------

void quad(void)
{
	    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	      // Top face (y = 1.0f)
	      // Define vertices in counter-clockwise (CCW) order with normal pointing out
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f,  1.0f);
	      glVertex3f( 1.0f, 1.0f,  1.0f);

	      // Bottom face (y = -1.0f)
	      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	      glVertex3f( 1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f( 1.0f, -1.0f, -1.0f);

	      // Front face  (z = 1.0f)
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f( 1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f, -1.0f, 1.0f);
	      glVertex3f( 1.0f, -1.0f, 1.0f);

	      // Back face (z = -1.0f)
	      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	      glVertex3f( 1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f( 1.0f,  1.0f, -1.0f);

	      // Left face (x = -1.0f)
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(-1.0f,  1.0f,  1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);

	      // Right face (x = 1.0f)
	      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	      glVertex3f(1.0f,  1.0f, -1.0f);
	      glVertex3f(1.0f,  1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f, -1.0f);
	   glEnd();  // End of drawing color-cube
}

void pyramid(void)
{

//	static float r = 0.0;
//
//	    glRotated(r,0,0,1);
//	    glRotated(r,0,1,0);
//	    glRotated(r,1,0,0);
//	    r = r + 1.0;
//        printf("\n\r=%f\n\n", r);

	   // Render a pyramid consists of 4 triangles
	   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	      // Front
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f( 0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(-1.0f, -1.0f, 1.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(1.0f, -1.0f, 1.0f);

	      // Right
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f(0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(1.0f, -1.0f, 1.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(1.0f, -1.0f, -1.0f);

	      // Back
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f(0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(1.0f, -1.0f, -1.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(-1.0f, -1.0f, -1.0f);

	      // Left
	      glColor3f(1.0f,0.0f,0.0f);       // Red
	      glVertex3f( 0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f,0.0f,1.0f);       // Blue
	      glVertex3f(-1.0f,-1.0f,-1.0f);
	      glColor3f(0.0f,1.0f,0.0f);       // Green
	      glVertex3f(-1.0f,-1.0f, 1.0f);
	   glEnd();   // Done drawing the pyramid
}

void drawaxes(void)
{
    // X
    glColor3ub(255, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, -0.25, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.75, 0.0, 0.25);
    glVertex3f(0.75, 0.0, -0.25);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    // Y
    glColor3ub(0, 255, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.75, 0.25);
    glVertex3f(0.0, 0.75, -0.25);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glVertex3f(-0.25, 0.75, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    // Z
    glColor3ub(0, 0, 255);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.25, 0.0, 0.75);
    glVertex3f(-0.25, 0.0, 0.75);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.25, 0.75);
    glVertex3f(0.0, -0.25, 0.75);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

//    glColor3ub(255, 255, 0);
//    glRasterPos3f(1.1, 0.0, 0.0);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
//    glRasterPos3f(0.0, 1.1, 0.0);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
//    glRasterPos3f(0.0, 0.0, 1.1);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
}
 

