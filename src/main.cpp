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

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw player
    glTranslatef(playerPosX, playerPosY, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-playerSize / 2, -playerSize / 2);
        glVertex2f(playerSize / 2, -playerSize / 2);
        glVertex2f(playerSize / 2, playerSize / 2);
        glVertex2f(-playerSize / 2, playerSize / 2);
    glEnd();

    glutSwapBuffers();
}

// Update function
void update(int value) {
   updatePlayer();
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

