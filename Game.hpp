#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<char>> grid; // 'R'=red, 'G'=green, 'B'=blue, ' '=empty
    std::vector<std::vector<char>> targetPattern; // Target pattern to match
    std::vector<std::unique_ptr<Entity>> anomalies; // Anomalies
    sf::Vector2i cursorPos;
    float disruption; // Disruption level (0 to 100)
    std::mt19937 rng;
    bool isPatternMatched;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
