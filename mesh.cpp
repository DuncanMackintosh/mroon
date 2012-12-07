#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "renderables/QuadMesh.h"

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=50.0f, z=50.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void changeSize(int w, int h) {

        // Prevent a divide by zero, when window is too short
        // (you cant make a window of zero width).
        if (h == 0)
                h = 1;

        float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);

        // Reset Matrix
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set the correct perspective.
        gluPerspective(45.0f, ratio, 0.1f, 100.0f);

        // Get Back to the Modelview
        glMatrixMode(GL_MODELVIEW);
}



void computePos(float deltaMove) {

        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
}

float gridHeights[100][100];

void init(void) {
  for(int x=0; x<100; x++) {
      for(int y=0; y<100; y++) {
          gridHeights[x][y] = (float)rand()/(float)RAND_MAX * 3.0f;
      }
  }
}

void renderScene(void) {

        if (deltaMove)
                computePos(deltaMove);

        // Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();
        // Set the camera
        gluLookAt(      x, 5.0f, z,
                        x+lx, 5.0f,  z+lz,
                        0.0f, 1.0f,  0.0f);
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
          for(int x=1; x<100; x++) {
              for(int y=1; y<100; y++) {
                  glColor3f(0.9f, gridHeights[x-1][y-1], 0.9f);
                  glVertex3f(x-1, gridHeights[x-1][y-1], y-1);
                  glColor3f(0.9f, gridHeights[x][y-1], 0.9f);
                  glVertex3f(x, gridHeights[x][y-1], y-1);
                  glColor3f(0.9f, gridHeights[x][y], 0.9f);
                  glVertex3f(x, gridHeights[x][y], y);
                  glColor3f(0.9f, gridHeights[x-1][y], 0.9f);
                  glVertex3f(x-1, gridHeights[x-1][y], y);
              }
          }
        glEnd();


        glBegin(GL_LINES);
          for(int x=1; x<100; x++) {
              for(int y=1; y<100; y++) {

//                  glColor3f(0.0f, 0.2f, 0.9f);
//                  glVertex3f(x-1, 2.0f, y-1);
//                  glVertex3f(x, 2.0f, y-1);
//                  glVertex3f(x-1, 2.0f, y-1);
//                  glVertex3f(x-1, 2.0f, y);
//
                  glColor3f(0.0f, 0.9f, 0.2f);
                  glVertex3f(x-1, gridHeights[x-1][y-1], y-1);
                  glVertex3f(x, gridHeights[x][y-1], y-1);
                  glVertex3f(x-1, gridHeights[x-1][y-1], y-1);
                  glVertex3f(x-1, gridHeights[x-1][y], y);
              }
          }
        glEnd();




        glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

        if (key == 27)
              exit(0);
}

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
}

void mouseMove(int x, int y) {

         // this will only be true when the left button is down
         if (xOrigin >= 0) {

                // update deltaAngle
                deltaAngle = (x - xOrigin) * 0.01f;

                // update camera's direction
                lx = sin(angle + deltaAngle);
                lz = -cos(angle + deltaAngle);
        }
}

void mouseButton(int button, int state, int x, int y) {

        // only start motion if the left button is pressed
        if (button == GLUT_LEFT_BUTTON) {

                // when the button is released
                if (state == GLUT_UP) {
                        angle += deltaAngle;
                        xOrigin = -1;
                }
                else  {// state = GLUT_DOWN
                        xOrigin = x;
                }
        }
}

int main(int argc, char **argv) {

  init();
        // init GLUT and create window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(320,320);
        glutCreateWindow("Lighthouse3D - GLUT Tutorial");

        // register callbacks
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);

        glutIgnoreKeyRepeat(1);
        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(pressKey);
        glutSpecialUpFunc(releaseKey);

        // here are the two new functions
        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

        // OpenGL init
        glEnable(GL_DEPTH_TEST);

        // enter GLUT event processing cycle
        glutMainLoop();

        return 1;
}
