#ifdef __APPLE__ // Check OS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#include "lib/variables.h"
#include "lib/player.h"
#include "lib/npc.h"
#include "lib/borders.h"

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y);
// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y);
//Update function
void update(int value);

// Initialize player and NPCs
Player p;
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

//Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Draw functions
   drawBorders();
   p.drawPlayer();
   glColor3f(1.0f, 1.0f, 0.0f);     //Draw Enemy NPCs (yellow)
   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
      enemies[i].drawNPC();
    }

   glutSwapBuffers();
}

int main(int argc, char** argv) {
   //Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1200, 800);
   glutCreateWindow("Bullet Hell");

   //Handle display and keyboard updates
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboardDown);
   glutKeyboardUpFunc(keyboardUp);
   glutTimerFunc(16, update, 0);

   //Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-400, 400, -300, 300, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop();
   return 0;
}

//Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
   p.updateKey(key, true);
}

//Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
   p.updateKey(key, false);
}

//Update function
void update(int value) {
   p.updatePlayer();

   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
        enemies[i].updateNPC();
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}