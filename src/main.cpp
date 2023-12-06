#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
<<<<<<< Updated upstream
#include "lib/player.h"
#include "lib/npc.h"

//Initialize player
=======
#endif

#include "lib/player.h"
#include "lib/npc.h"
#include "lib/borders.h"
#include "lib/ui.h"
#include "lib/menu.h"
#include "lib/bullet.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y);
// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y);
// Update function
void update(int value);
// Display callback function
void display();
// Mouse movement and clicking
void mouseMotion(int x, int y);
void mouseClick(int button, int state, int x, int y);
// draws circle to represent user crosshair
void drawCircle(float centerX, float centerY, float radius, int numSegments);

// Initialize game
>>>>>>> Stashed changes
Player p;

//Initialize NPCs
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

//Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   //Draw player (red)
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

//Update function
void update(int value) {
   p.updatePlayer();

   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
        enemies[i].updateNPC();
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

//Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
   p.updateKey(key, true);
}

//Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
   p.updateKey(key, false);
}

// Global variables for mouse position
float mouseX = 0.0f, mouseY = 0.0f;

int main(int argc, char** argv) {
   //Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1100, 800);
   glutCreateWindow("Temporary name");

   //Handle display and keyboard updates
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboardDown);
   glutKeyboardUpFunc(keyboardUp);
   glutTimerFunc(16, update, 0);

   //Register mouse callbacks
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);

   //Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-400, 400, -300, 300, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop();
   return 0;
}

<<<<<<< Updated upstream
=======
//Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
   if (currentState == MENU && key == ' ') {
      currentState = GAME;
   }
   p.updateKey(key, true);
}

//Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
   p.updateKey(key, false);
}

//Update function
void update(int value) {
   p.updatePlayer();

   // Check if in game state
   if (currentState == GAME) {
      // TEMPORARY update calls. should be called whenever health or score changes
      ui.updateHealth(1);
      ui.updateScore(1);

      for (auto &enemy: enemies) {
         enemy.updateNPC();
      }

      // Spawn NPCs
      spawnTimer += 16.0f; // Increment by 16 milliseconds (time per frame)
      if (spawnTimer >= 1000.0f) {  // Spawn every second
         // Random position within borders
         float x = borderLeft + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderRight + abs(borderLeft)))); // Random X
         float y = borderBottom + 40 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderTop + abs(borderBottom) - 50))); // Random Y

         // Spawn new NPC
         enemies.push_back(NPC(x, y, 30.0f, 1.0f));

         // Reset timer
         spawnTimer = 0.0f;
      }

      // Update bullets
      for (auto& bullet : p.getBullets()) {
         bullet.updateBullet();
      }

      // Remove bullets that are off-screen or marked for removal
      p.removeMarkedBullets();
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

// Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Menu
   if (currentState == MENU) {
      displayMenu(p);
   // Game
   } else if (currentState == GAME) {
      drawBorders();
      p.drawPlayer();
      for (auto &enemy: enemies) {
         enemy.drawNPC();
      }
      ui.drawUI();
      for (auto& bullet : p.getBullets()) {
         bullet.drawBullet();
      }
      glColor3f(0.0f, 1.0f, 0.0f); // green
      drawCircle(mouseX, mouseY, 5.0f, 12);
   }

   glutSwapBuffers();
}

void mouseMotion(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    mouseX = ((float)x / windowWidth) * 800 - 400; 
    mouseY = 300 - ((float)y / windowHeight) * 600; 
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        p.shootBullet(mouseX, mouseY);
    }
}

void drawCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();
}
>>>>>>> Stashed changes
