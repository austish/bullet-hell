#ifdef __APPLE__ // Check OS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#include "lib/player.h"
#include "lib/npc.h"
#include "lib/borders.h"
#include <cstdlib>
#include <ctime>
#include <string>

void drawText(const std::string &text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y);
// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y);
//Update function
void update(int value);

// Initialize player and NPCs
Player p;
std::vector<NPC> enemies;
float spawnTimer = 0.0f; // timer for spawning NPCs

//Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Draw functions
   drawBorders();
   p.drawPlayer();
   glColor3f(1.0f, 1.0f, 0.0f);     //Draw Enemy NPCs (yellow)
   for (auto &enemy: enemies) {
        enemy.drawNPC();
   }

   // Draw UI background
   glColor3f(0.5f, 0.5f, 0.5f); // Grey background
   glBegin(GL_QUADS);
   glVertex2f(borderLeft, borderTop + UIheight);
   glVertex2f(borderRight, borderTop + UIheight); // Account for UI height
   glVertex2f(borderRight, borderTop);
   glVertex2f(borderLeft, borderTop);
   glEnd();

   // Set color for text
   glColor3f(1.0f, 1.0f, 1.0f); // White text

   // Draw text at the top left corner
   drawText("Left: 123", borderLeft + 10, borderTop + UIheight - 30);

   // Draw text at the top right corner
   drawText("Right: 456", borderRight - 100, borderTop + UIheight - 30);

   glutSwapBuffers();
}

int main(int argc, char** argv) {
   //Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1200, 800);
   glutCreateWindow("Bullet Hell");
   srand(static_cast<unsigned int>(time(nullptr)));   // Random seed

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

   for (auto &enemy: enemies) {
        enemy.updateNPC();
   }

   // Spawn NPCs
   spawnTimer += 16.0f; // Increment by 16 milliseconds (time per frame)
   if (spawnTimer >= 1000.0f) {  // Spawn every second
      // Random position within borders
      float x = borderLeft + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderRight + abs(borderLeft)))); // Random X
      float y = borderBottom+ static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderTop + abs(borderBottom)))); // Random Y

      // Spawn new NPC
      enemies.push_back(NPC(x, y, 30.0f, 1.0f));

      // Reset timer
      spawnTimer = 0.0f;
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}