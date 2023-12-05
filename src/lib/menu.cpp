#include "menu.h"
#include "borders.h"
#include "ui.h"         // drawtext()

void displayMenu(Player p) {
    // Title
    drawText("Bullet Hell", -30, 265);
    // Player
    p.drawPlayer();                    
    // Controls
    glColor3f(1.0f, 1.0f, 1.0f); // White
    drawText("spacebar to start", -50, -250);
    drawText("wasd to move", -350, -250);
    drawText("right click to shoot", 250, -250);
}
