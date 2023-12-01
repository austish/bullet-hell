#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "lib/player.h"
#include "lib/npc.h"

// Initialize player
Player p;

// Initialize NPCs
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

// }

// Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Draw player (red)
   glColor3f(1.0f, 0.0f, 0.0f);
   float playerSize = p.getSize();
   glPushMatrix();
   glTranslatef(p.getPosX(), p.getPosY(), 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, playerSize / 2);
   glVertex2f(-playerSize / 2, playerSize / 2);
   glEnd();
   glPopMatrix();

   // Draw Enemy NPCs (yellow)
   glColor3f(1.0f, 1.0f, 0.0f);
   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
      float enemiesSize = enemies[i].getSize();
      glPushMatrix();
      glTranslatef(enemies[i].getPosX(), enemies[i].getPosY(), 0.0f);
      glBegin(GL_QUADS);
      glVertex2f(-enemiesSize / 2, -enemiesSize / 2);
      glVertex2f(enemiesSize / 2, -enemiesSize / 2);
      glVertex2f(enemiesSize / 2, enemiesSize / 2);
      glVertex2f(-enemiesSize / 2, enemiesSize / 2);
      glEnd();
      glPopMatrix();
    }

   glutSwapBuffers();
}

// Update function
void update(int value) {
   p.updatePlayer();

   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
        enemies[i].updateNPC();
   }

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

