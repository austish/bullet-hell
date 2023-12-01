#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "lib/player.h"

// Initialize player
Player p;

// Initialize game
// void init() {
//    // Initialize npcs, etc. here
// }

// Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Draw player
   float playerSize = p.getSize();
   glTranslatef(p.getPosX(), p.getPosY(), 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, playerSize / 2);
   glVertex2f(-playerSize / 2, playerSize / 2);
   glEnd();

   glutSwapBuffers();
}

// Update function
void update(int value) {
   p.updatePlayer();
   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
   p.updateKey(key, true);
}

// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
   p.updateKey(key, false);
}

int main(int argc, char** argv) {
   // Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1100, 800);
   glutCreateWindow("Temporary name");
   // init();

   // Handle display and keyboard updates
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboardDown);
   glutKeyboardUpFunc(keyboardUp);
   glutTimerFunc(16, update, 0);    // ~60 fps

   // Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-400, 400, -300, 300, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop();
   return 0;
}

