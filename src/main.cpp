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
#include "lib/ui.h"
#include "lib/menu.h"
#include "lib/bullet.h"
#include "lib/scores.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

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
std::vector<NPC> enemies;
float spawnTimer = 0.0f; // timer for spawning NPCs
bool leaderboardUpdated = false;
bool gameEnded = false;
GameState currentState = START;

// Global variables for mouse position
float mouseX = 0.0f, mouseY = 0.0f;

int main(int argc, char** argv) {
   // Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1200, 800);
   glutCreateWindow("Bullet Hell");
   srand(static_cast<unsigned int>(time(nullptr)));   // Random seed

   // Handle display and keyboard updates
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboardDown);
   glutKeyboardUpFunc(keyboardUp);
   glutTimerFunc(16, update, 0);

   // Hanle keyboard updates
   glutPassiveMotionFunc(mouseMotion);
   glutMouseFunc(mouseClick);

   // Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-400, 400, -300, 300, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   glutMainLoop();
   return 0;
}

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
   if ((currentState == START || currentState == END) && key == ' ')
      currentState = GAME;
   p.updateKey(key, true);
}

// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
   p.updateKey(key, false);
}

// Update function
void update(int value) {
   p.updatePlayer();
   // Checks if game is going on
   if (currentState == GAME) {
      float playerPosX = p.getPosX();
      float playerPosY = p.getPosY();

      for (auto &enemy: enemies) {
         enemy.updateNPC(playerPosX, playerPosY);
      }

      // Spawn NPCs
      spawnTimer += 16.0f; // Increment by 16 milliseconds
      if (spawnTimer >= 1000.0f) {  // Spawn every second with a random position
         float x = borderLeft + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderRight + abs(borderLeft)))); // Random X
         float y = borderBottom + 40 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderTop + abs(borderBottom) - 50))); // Random Y

         ShapeType randomShape = static_cast<ShapeType>(rand() % 3); // Randomly chose the NPC shape

         enemies.push_back(NPC(x, y, 30.0f, 1.0f, randomShape));
         spawnTimer = 0.0f;
      }

      // NPC and player collision detection
      auto it = enemies.begin();
      while (it != enemies.end()) {
         // If they collide remove NPC and update player score
         if (it->checkCollisionWithPlayer(p.getPosX(), p.getPosY(), p.getSize())) {
            it = enemies.erase(it);
            p.updateScore(100);
         } else {
            ++it;
         }
      }

      // Update bullets
      for (auto& bullet : p.getBullets()) {
         bullet.updateBullet();

         // NPC and bullet collision detection
         for (auto& enemy : enemies) {
               // If they collide remove NPC and bullet and update player score
               if (enemy.checkCollisionWithBullet(bullet.getPosX(), bullet.getPosY(), bullet.getSize())) {
                  enemy.markForRemoval();
                  bullet.markForRemoval();
                  p.removeMarkedBullets();
                  p.updateScore(100);
               }
         }
      }

      // Update NPCs
      for (auto& enemy : enemies) {
         enemy.updateNPC(playerPosX, playerPosY);
         enemy.shootBullets();

         // Player and bullet collision detection
         for (auto& enemyBullet : enemy.getBullets()) {
            enemyBullet.updateBullet();
               // If they collide remove bullet and update player health
               if (p.checkCollisionWithBullet(enemyBullet.getPosX(), enemyBullet.getPosY(), enemyBullet.getSize())) {
                  p.updateHealth(-1);
                  // If health is 0 then clean up bullets then end the game
                  if(p.getHealth() == 0){
                     for (auto& bullet : p.getBullets()) {
                        bullet.markForRemoval();
                     }
                     p.removeMarkedBullets();
                  currentState = END; // End game
                  }
                  enemyBullet.markForRemoval();
                  enemy.removeMarkedBullets(); // Remove bullet that hit player
               }
         }
      }


      // Remove NPCs marked for removal
      enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const NPC& enemy) { return enemy.getMarkedForRemoval(); }), enemies.end());
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

// Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Menu
   if (currentState == START) {
      displayStart(p);
   // Game
   } else if (currentState == GAME) {
      if (gameEnded) {
         p.resetPlayer();
         enemies.clear();
         spawnTimer = 0.0f;
         gameEnded = false;
      }
      leaderboardUpdated = false;
      drawBorders();
      p.drawPlayer();
      for (auto &enemy: enemies) {
         enemy.drawNPC();
         for (auto &bullet : enemy.getBullets()) {
            bullet.drawBullet();
         }
      }
      for (auto& bullet : p.getBullets()) {
         bullet.drawBullet();
      }
      // Draw aiming circle at cursor position
      glColor3f(0.0f, 1.0f, 0.0f); // green
      drawCircle(mouseX, mouseY, 5.0f, 12);

      drawUI(p);
   // End
   } else if (currentState == END) {
      gameEnded = true;
      if (!leaderboardUpdated) {
         updateLeaderboard(p.getScore());
         leaderboardUpdated = true;
      }
      displayLeaderboard();
      displayEnd(p);
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
