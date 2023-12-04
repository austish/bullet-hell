#include "ui.h"
#include "borders.h"

UI::UI() {
    health = 100;
    score = 0;
}

void UI::drawUI() {
    glColor3f(0.5f, 0.5f, 0.5f); // Grey background
    glBegin(GL_QUADS);
    glVertex2f(borderLeft, borderTop + UIheight);
    glVertex2f(borderRight, borderTop + UIheight); // Account for UI height
    glVertex2f(borderRight, borderTop);
    glVertex2f(borderLeft, borderTop);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White text
    std::string h = "Health: " + std::to_string(health);
    drawText(h, borderLeft + 10, borderTop + UIheight - 30);
    std::string s = "Score: " + std::to_string(score);
    drawText(s, borderRight - 100, borderTop + UIheight - 30);
}

void UI::drawText(const std::string &text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void UI::updateHealth(int amount) {
    health += amount;
}

void UI::updateScore(int amount) {
    score += amount;
}