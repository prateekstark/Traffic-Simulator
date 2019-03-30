#include<iostream>
#include<GL/glut.h>
#include<string>
#include<vector>
using namespace std;

// GLfloat angle = 0.0f;  // rotational angle of the shapes

int refreshMills = 30; // refresh interval in milliseconds

GLfloat ySpeed = 0.000f;
GLfloat xSpeed = 0.03f;

GLfloat yCoordinate = 0.000f;
GLfloat xCoordinate = -0.5f;
void initGL(){
  glClearColor(0.0f,0.0f,0.0f,1.0f);
}
int arr[5] = {1,2,3,4,5};



void createVehicle(int length, int width, string color, int arr[]){
    glTranslatef(xCoordinate, 0.4f, 0.0f);
  // createVehicle(2,1,"BLUE");
    
    GLfloat resizeLength = length*(0.1);
    
    GLfloat resizeWidth = length*(0.05);
    
    GLfloat xColor, yColor, zColor;
    
    if(color.compare("GREEN") == 0){
        xColor = 0.0;
        yColor = 1.0;
        zColor = 0.0;
    }
    
    if(color.compare("BLUE") == 0){
        xColor = 0.0;
        yColor = 0.0;
        zColor = 1.0;
    }
    glBegin(GL_QUADS);
        glColor3f(xColor, yColor, zColor);  // Blue
        // glColor3f(1.0f, 1.0f, 0.0f);  // Red
        glVertex2f(-resizeLength/3, -resizeWidth/3);     // Define vertices in counter-clockwise (CCW) order
        glVertex2f( resizeLength/3, -resizeWidth/3);     //  so that the normal (front-face) is facing you
        glVertex2f( resizeLength/3,  resizeWidth/3);
        glVertex2f(-resizeLength/3,  resizeWidth/3);
    glEnd();
    glEnd();
    xCoordinate = arr[2]*0.02;
}









void road(){
    glBegin(GL_QUADS);              
        glColor3f(0.0f, 0.0f, 0.0f); 
        glVertex2f(-1.0f, -0.7f);    
        glVertex2f(-1.0f,  0.7f);
        glVertex2f( 1.0f, 0.7f);
        glVertex2f( 1.0f,  -0.7f);     
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-1.0f,0.55f);
        glVertex2f(-1.0f,0.6f);
        glVertex2f(1.0f,0.6f);
        glVertex2f(1.0f,0.55f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-1.0f,-0.55f);
        glVertex2f(-1.0f,-0.6f);
        glVertex2f(1.0f,-0.6f);
        glVertex2f(1.0f,-0.55f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-1.0f,-0.05f);
        glVertex2f(-1.0f,0.05f);
        glVertex2f(-0.8f,0.05f);
        glVertex2f(-0.8f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.7f,-0.05f);
        glVertex2f(-0.7f,0.05f);
        glVertex2f(-0.5f,0.05f);
        glVertex2f(-0.5f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.4f,-0.05f);
        glVertex2f(-0.4f,0.05f);
        glVertex2f(-0.2f,0.05f);
        glVertex2f(-0.2f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.1f,-0.05f);
        glVertex2f(-0.1f,0.05f);
        glVertex2f(0.1f,0.05f);
        glVertex2f(0.1f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(0.2f,-0.05f);
        glVertex2f(0.2f,0.05f);
        glVertex2f(0.4f,0.05f);
        glVertex2f(0.4f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(0.5f,-0.05f);
        glVertex2f(0.5f,0.05f);
        glVertex2f(0.7f,0.05f);
        glVertex2f(0.7f,-0.05f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(0.8f,-0.05f);
        glVertex2f(0.8f,0.05f);
        glVertex2f(1.0f,0.05f);
        glVertex2f(1.0f,-0.05f);
    glEnd();
}

void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  road();
  createVehicle(1,2,"GREEN",arr);
  glPopMatrix();
  glutSwapBuffers();
   // angle = angle + 2.0f;
   
}


int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Animation via Idle Function");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   // glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutTimerFunc(0, Timer, 0);     // First timer call immediately
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
