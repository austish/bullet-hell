#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
 
void display() {
   glutSwapBuffers();
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(1200, 800);   // Set the window's initial width & height
   glutCreateWindow("OpenGL"); // Create a window with the given title
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   // glutReshapeFunc();
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

