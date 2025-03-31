#include <iostream>
#include <vector>
#include <string>
#include <climits>                           // For INT_MAX

class Player {
public:
    int position;
    int maxWidth;

    Player(int maxWidth) : position(maxWidth / 2), maxWidth(maxWidth) {}

    void moveLeft() {
        if (position > 0) {
            position--;
            std::cout << "Player moved left.\n";
        } else {
            std::cout << "Player is already at the leftmost position.\n";
        }
    }

    void moveRight() {
        if (position < maxWidth - 1) {
            position++;
            std::cout << "Player moved right.\n";
        } else {
            std::cout << "Player is already at the rightmost position.\n";
        }
    }
};

class Enemy {
public:
    int position;
    bool isDestroyed;

    Enemy(int position) : position(position), isDestroyed(false) {}

    void destroy() {
        isDestroyed = true;
        std::cout << "Enemy destroyed!\n";
    }
};

class Bullet {
public:
    int position;

    Bullet(int position) : position(position) {}

    bool hitsEnemy(const Enemy& enemy) {
        return position == enemy.position && !enemy.isDestroyed;
    }
};

int main() {
    const int width = 10; 
    std::string playerName;
    int highScore = INT_MAX;
    std::string highScorer = "None"; 

    std::cout << "Welcome to Space Invaders (Text-Based Version)!\n";
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    bool playAgain = true;
    while (playAgain) {
        Player player(width);

        std::vector<Enemy> enemies;
        for (int i = 0; i < width; i += 2) {
            enemies.emplace_back(i); 
        }

        std::cout << "Enemies are hidden. Destroy them by shooting!\n";
        std::cout << "Player starts at position " << player.position << ".\n";

        bool running = true;
        int moveCount = 0; 

        while (running) {
            std::cout << "\nGame Grid: ";
            for (int i = 0; i < width; i++) {
                if (player.position == i) {
                    std::cout << "P "; 
                } else {
                    std::cout << ". "; 
                }
            }
            std::cout << "\n";

            std::cout << "Choose an action:\n";
            std::cout << "1. Move Left\n";
            std::cout << "2. Move Right\n";
            std::cout << "3. Shoot\n";
            std::cout << "4. Exit\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                player.moveLeft();
                moveCount++;
                break;
            case 2:
                player.moveRight();
                moveCount++;
                break;
            case 3: {
                moveCount++;
                Bullet bullet(player.position);
                bool hit = false;
                for (auto& enemy : enemies) {
                    if (bullet.hitsEnemy(enemy)) {
                        enemy.destroy();
                        hit = true;
                        break;
                    }
                }
                if (!hit) {
                    std::cout << "Bullet missed! No enemy at this position.\n";
                }
                break;
            }
            case 4:
                running = false;
                std::cout << "Exiting the game. Thanks for playing!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }

            bool allEnemiesDestroyed = true;
            for (const auto& enemy : enemies) {
                if (!enemy.isDestroyed) {
                    allEnemiesDestroyed = false;
                    break;
                }
            }
            if (allEnemiesDestroyed) {
                std::cout << "Congratulations, " << playerName << "! You destroyed all the enemies!\n";
                std::cout << "You finished the game in " << moveCount << " moves.\n";
                running = false;

                if (moveCount < highScore) {
                    highScore = moveCount;
                    highScorer = playerName;
                    std::cout << "New High Score! " << highScorer << " completed the game in " << highScore << " moves.\n";
                } else {
                    std::cout << "High Score remains: " << highScorer << " with " << highScore << " moves.\n";
                }
            }
        }

        std::cout << "Do you want to play again? (1 for Yes, 0 for No): ";
        std::cin >> playAgain;
        std::cin.ignore();
    }

    std::cout << "Thank you for playing Space Invaders!\n";
    std::cout << "High Score: " << highScorer << " with " << highScore << " moves.\n";

    return 0;
}