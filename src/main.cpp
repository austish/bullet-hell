#ifdef APPLE // Check OS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
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
// Circle representing user crosshair
void drawCircle(float centerX, float centerY, float radius, int numSegments);

// Initialize game
Player p;
UI ui;
std::vector<NPC> enemies;
float spawnTimer = 0.0f; // timer for spawning NPCs

// State of game
enum AppState {
    MENU,
    GAME
};
AppState currentState = MENU;

// Global variables for mouse position
float mouseX = 0.0f, mouseY = 0.0f;

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

    // Register mouse callbacks
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
         enemy.shootBullets();
         for (auto &bullet : enemy.getBullets()){
            bullet.updateBullet();
         }
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
         for (auto &bullet : enemy.getBullets()){
            bullet.drawBullet();
         }
      }
      ui.drawUI();
      for (auto& bullet : p.getBullets()) {
         bullet.drawBullet();
      }
      // Draw aiming circle at cursor position
      glColor3f(0.0f, 1.0f, 0.0f); // green
      drawCircle(mouseX, mouseY, 5.0f, 12); // Radius 5 and 12 segments

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