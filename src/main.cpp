#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cstring>

// Player properties
float playerPosX = 0.0f;
float playerPosY = 0.0f;
const float playerSize = 40.0f;
const float playerSpeed = 5.0f;

// Array to track state of each key
bool keyStates[256];

// Initialize game
<<<<<<< Updated upstream
void init() {
   // set all keyStates to 0
   memset(keyStates, 0, sizeof(keyStates));
   // Initialize player, npcs, etc. here
}

// Player movement
void updatePlayer() {
   if (keyStates['w'])
      playerPosY += playerSpeed;
   if (keyStates['s'])
      playerPosY -= playerSpeed;
   if (keyStates['a'])
      playerPosX -= playerSpeed;
   if (keyStates['d'])
      playerPosX += playerSpeed;
}
=======
// void init() {

// Initialize NPCs
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

// }
>>>>>>> Stashed changes

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

<<<<<<< Updated upstream
    // Draw player
    glTranslatef(playerPosX, playerPosY, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-playerSize / 2, -playerSize / 2);
        glVertex2f(playerSize / 2, -playerSize / 2);
        glVertex2f(playerSize / 2, playerSize / 2);
        glVertex2f(-playerSize / 2, playerSize / 2);
    glEnd();

    glutSwapBuffers();
=======
   // Draw player (Red)
   glColor3f(1.0f, 0.0f, 0.0f);
   float playerSize = p.getSize();
   glTranslatef(p.getPosX(), p.getPosY(), 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, -playerSize / 2);
   glVertex2f(playerSize / 2, playerSize / 2);
   glVertex2f(-playerSize / 2, playerSize / 2);
   glEnd();

   // Draw Enemy NPCs (yellow)
   glColor3f(1.0f, 1.0f, 0.0f);
   for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); ++i) {
      float enemiesSize = enemies[i].getSize();
      glTranslatef(enemies[i].getPosX(), enemies[i].getPosY(), 0.0f);
      glBegin(GL_QUADS);
      glVertex2f(-enemiesSize / 2, -enemiesSize / 2);
      glVertex2f(enemiesSize / 2, -enemiesSize / 2);
      glVertex2f(enemiesSize / 2, enemiesSize / 2);
      glVertex2f(-enemiesSize / 2, enemiesSize / 2);
      glEnd();
    }

   glutSwapBuffers();
>>>>>>> Stashed changes
}

// Update function
void update(int value) {
<<<<<<< Updated upstream
   updatePlayer();
=======
   p.updatePlayer();

   for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].updateNPC();
    }

>>>>>>> Stashed changes
   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

// Keyboard button pressed
void keyboardDown(unsigned char key, int x, int y) {
    keyStates[key] = true;
}

// Keyboard button released 
void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

int main(int argc, char** argv) {
   // Initialize window and game
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1100, 800);
   glutCreateWindow("Temporary name");
   init();

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

