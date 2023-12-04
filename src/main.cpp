#ifdef __APPLE__ // Check if the target OS is macOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#include "lib/variables.h"
#include "lib/player.h"
#include "lib/npc.h"

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y);
// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y);
//Update function
void update(int value);

// Initialize player
Player p;

// Initialize NPCs
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

// Initialize boundaries
const extern float boundaryLeft = -400.0f;
const extern float boundaryRight = 400.0f;
const extern float boundaryTop = 300.0f;
const extern float boundaryBottom = -300.0f;

//Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Draw boundaries (white)
    glColor3f(1.0f, 1.0f, 1.0f); // Set boundary color to red
    glBegin(GL_LINES);
        // Top boundary
        glVertex2f(boundaryLeft, boundaryTop);
        glVertex2f(boundaryRight, boundaryTop);
        // Bottom boundary
        glVertex2f(boundaryLeft, boundaryBottom);
        glVertex2f(boundaryRight, boundaryBottom);
        // Left boundary
        glVertex2f(boundaryLeft, boundaryBottom);
        glVertex2f(boundaryLeft, boundaryTop);
        // Right boundary
        glVertex2f(boundaryRight, boundaryBottom);
        glVertex2f(boundaryRight, boundaryTop);
    glEnd();

   //Draw player (red)
   glColor3f(1.0f, 0.0f, 0.0f);                       // Set color to red
   glPushMatrix();                                    // Push player matrix
   float playerSize = p.getSize();
   glTranslatef(p.getPosX(), p.getPosY(), 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, playerSize / 2);
   glVertex2f(-playerSize / 2, playerSize / 2);
   glEnd();
   glPopMatrix();                                     // Pop player matrix

   //Draw Enemy NPCs (yellow)
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

int main(int argc, char** argv) {
   //Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1200, 800);
   glutCreateWindow("Temporary name");    //CHANGE NAME

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