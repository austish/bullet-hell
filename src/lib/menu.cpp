#include "menu.h"
#include "borders.h"

// Define the menu elements with respect to a 1200x800 window
Button startButton = {500, 100, 200, 50, "Start"}; // Centered horizontally
float playerSquareSize = 50;
float playerSquareX = 600; // Center of the window width
float playerSquareY = 400; // Center of the window height

void drawButton(const Button& button) {
    // Draw the button background
    glColor3f(1.0f, 0.0f, 0.0f); // Red button
    glBegin(GL_QUADS);
        glVertex2f(button.x, button.y);
        glVertex2f(button.x + button.width, button.y);
        glVertex2f(button.x + button.width, button.y + button.height);
        glVertex2f(button.x, button.y + button.height);
    glEnd();

    // Draw the button text
    glColor3f(1.0f, 1.0f, 1.0f); // White text
    drawText(button.text, button.x + 20, button.y + 15);
}

void displayMenu() {
    // Title
    drawText("Bullet Hell", 540, 750);

    // Player
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(playerSquareX - playerSquareSize / 2, playerSquareY - playerSquareSize / 2);
        glVertex2f(playerSquareX + playerSquareSize / 2, playerSquareY - playerSquareSize / 2);
        glVertex2f(playerSquareX + playerSquareSize / 2, playerSquareY + playerSquareSize / 2);
        glVertex2f(playerSquareX - playerSquareSize / 2, playerSquareY + playerSquareSize / 2);
    glEnd();

    // Start button
    drawButton(startButton);

    // Controls
    drawText("wasd to move", 100, 150); // Position this closer to the left edge
    drawText("right click to shoot", 900, 150); // Position this closer to the right edge
}
