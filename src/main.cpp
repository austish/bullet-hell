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
#include <cstdlib>
#include <ctime>


// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y);
// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y);
// Update function
void update(int value);
// Display callback function
void display();
// Mouse functionality
void mouse(int button, int state, int x, int y);

// Initialize game
Player p;
UI ui;
std::vector<NPC> enemies;
float spawnTimer = 0.0f; // timer for spawning NPCs

// Menu or game state
enum AppState {
    MENU,
    GAME
};
AppState currentState = MENU;



int main(int argc, char** argv) {
   //Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1200, 800);
   glutCreateWindow("Bullet Hell");
   srand(static_cast<unsigned int>(time(nullptr)));   // Random seed

   //Handle display and keyboard updates
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
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
      float y = borderBottom + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (borderTop + abs(borderBottom)))); // Random Y

      // Spawn new NPC
      enemies.push_back(NPC(x, y, 30.0f, 1.0f));

      // Reset timer
      spawnTimer = 0.0f;
   }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

// Display callback function
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   if (currentState == MENU) {
      displayMenu();
    } else if (currentState == GAME) {
      drawBorders();
      p.drawPlayer();
      for (auto &enemy: enemies) {
         enemy.drawNPC();
      }
      ui.drawUI();
   }

   glutSwapBuffers();
}

// Mouse functionality
void mouse(int button, int state, int x, int y) {
   if (currentState == MENU) {
      if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
         // windowHeight should be set to 800
         y = 800 - y;

         // Check if the click is within the start button bounds
         if (x >= startButton.x && x <= startButton.x + startButton.width &&
               y >= startButton.y && y <= startButton.y + startButton.height) {
               currentState = GAME;
         }
      }
   }
}