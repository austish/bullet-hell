#include "menu.h"
#include "borders.h"

void displayStart(Player p) {
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    // Title
    drawText("Bullet Hell", -30, 265);
    // Player
    p.drawPlayer();                    
    // Controls
    drawText("spacebar to start", -50, -250);
    drawText("wasd to move", -350, -250);
    drawText("left click to shoot", 250, -250);
}

void displayEnd(Player p) {
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    // Game over
    drawText("Game over", -300, 200);
    std::string s = "Score: " + std::to_string(p.getScore());
    drawText(s, -300, 125);
    // Player
    p.drawPlayer();                    
    // Controls
    drawText("spacebar to start", -50, -250);
}