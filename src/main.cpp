#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cstring>
#include "npc.h"

// Initialize NPCs
NPC enemies[3] = {
   NPC(0.0f, 100.0f, 30.0f, 1.0f),
   NPC(100.0f, 0.0f, 30.0f, 1.0f),
   NPC(200.0f, 100.0f, 30.0f, 1.0f)
};

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

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
}

// Update function
void update(int value) {
   for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].updateNPC();
    }

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // Approx 60 FPS
}

int main(int argc, char** argv) {
   // Initialize window and game
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Temporary name");
    // init();

    // Handle display and keyboard updates
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0); // ~60 fps

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
    return 0;
}

