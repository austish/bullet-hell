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
#include "lib/scores.h"
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

// Initialize game
Player p;
std::vector<NPC> enemies;
float spawnTimer = 0.0f; // timer for spawning NPCs
bool leaderboardUpdated = false;

// State of game
enum AppState {
    START,
    GAME,
    END
};
AppState currentState = START;

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
   if ((currentState == START || currentState == END) && key == ' ')
      currentState = GAME;
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
   float playerPosX = p.getX();
   float playerPosY = p.getY();
   if (currentState == GAME) {
      // TEMPORARY update calls. should be called whenever health or score changes
      p.updateHealth(1);
      p.updateScore(1);

      for (auto &enemy: enemies) {
         enemy.updateNPC(playerPosX, playerPosY);
      }

      // Spawn NPCs
      spawnTimer += 16.0f; // Increment by 16 milliseconds (time per frame)
      if (spawnTimer >= 1000.0f) {  // Spawn every second
         // Random position within borders
         float x = borderLeft + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderRight + abs(borderLeft)))); // Random X
         float y = borderBottom + 40 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderTop + abs(borderBottom) - 50))); // Random Y
          
         ShapeType randomShape = static_cast<ShapeType>(rand() % 3); // There are three shape types

         // Spawn new NPC
         enemies.push_back(NPC(x, y, 30.0f, 1.0f, randomShape));

         // Reset timer
         spawnTimer = 0.0f;
      }// Collision detection and NPC removal
      auto it = enemies.begin();
      while (it != enemies.end()) {
        if (it->checkCollisionWithPlayer(p.getX(), p.getY(), p.getSize())) {
            it = enemies.erase(it);  // Remove NPC if collision detected
        } else {
            ++it;
        }
    }
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
      leaderboardUpdated = false;
      drawBorders();
      p.drawPlayer();
      for (auto &enemy: enemies) {
         enemy.drawNPC();
      }
      drawUI(p);
   // End
   } else if (currentState == END) {
      if (!leaderboardUpdated) {
         updateLeaderboard(p.getScore());
         leaderboardUpdated = true;
      }
      displayLeaderboard();
      displayEnd(p);
   }

   glutSwapBuffers();
}
