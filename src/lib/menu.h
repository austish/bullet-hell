// Menu 
#ifndef MENU_H
#define MENU_H
#include <string>

struct Button {
    float x, y, width, height;
    std::string text;
};

void drawButton(const Button& button);
void displayMenu();
void mouse(int button, int state, int x, int y);

#endif