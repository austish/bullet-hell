// UI class
#ifndef UI_H
#define UI_H
#include <string>

class UI {
    private:
        int health;
        int score;
    public:
        UI();
        void drawUI();
        void updateHealth(int amount);
        void updateScore(int amount);
        int getScore();
};

void drawText(const std::string &text, float x, float y);

#endif