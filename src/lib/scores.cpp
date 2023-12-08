#include "scores.h"
#include "ui.h"
#include "borders.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

// Leaderboard 
void displayLeaderboard() {
    // Load leaderboard data from a file
    std::vector<int> leaderboard;
    int score = 0;
    std::ifstream inputFile("lib/text/leaderboard.txt");
    if (inputFile.is_open()) {
        while (inputFile >> score) {
            leaderboard.push_back(score);
        }
        inputFile.close();
    }

    // Display the top 5 scores
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    drawText("Leaderboard", 200, 250);
    for (int i = 0.; i < leaderboard.size(); i++) {
        drawText(std::to_string(i) + ". " + std::to_string(leaderboard[i]), 200, 225 - i * 25);
    }
}

// Update the leaderboard
void updateLeaderboard(int playerScore) {
    // Load leaderboard data from a file
    std::vector<int> leaderboard;
    int score = 0;
    std::ifstream inputFile("lib/text/leaderboard.txt");
    if (inputFile.is_open()) {
        while (inputFile >> score) {
            leaderboard.push_back(score);
        }
        inputFile.close();
    }

    // Add the player's score to the leaderboard
    leaderboard.push_back(playerScore);

    // Sort the leaderboard
    std::sort(leaderboard.begin(), leaderboard.end());
    std::reverse(leaderboard.begin(), leaderboard.end());

    // Keep only the top 5 scores
    if (leaderboard.size() > 5) {
        leaderboard.resize(5);
    }

    // Save the updated leaderboard to the file
    std::ofstream outputFile("lib/text/leaderboard.txt");
    if (outputFile.is_open()) {
        for (int score : leaderboard) {
            outputFile << score << "\n";
        }
        outputFile.close();
    }
}
