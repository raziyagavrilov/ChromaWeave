#include "Game.hpp"
#include <algorithm>

class Thread : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    char color; // 'R', 'G', 'B'
    bool active;

public:
    Thread(float x, float y, char c) : position(x, y), color(c), active(true) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(c == 'R' ? sf::Color::Red : c == 'G' ? sf::Color::Green : sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override {} // Threads not countered
    char getColor() const { return color; }
};

class Anomaly : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Anomaly(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override { active = false; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), disruption(0.f), rng(std::random_device{}()), isPatternMatched(false) {
    grid.resize(5, std::vector<char>(5, ' '));
    targetPattern.resize(3, std::vector<char>(3));
    // Simple target pattern
    targetPattern[0] = {'R', 'G', 'B'};
    targetPattern[1] = {'G', 'B', 'R'};
    targetPattern[2] = {'B', 'R', 'G'};
    // Place anomalies
    std::uniform_int_distribution<int> dist(0, 4);
    for (int i = 0; i < 2; ++i) {
        anomalies.push_back(std::make_unique<Anomaly>(250.f + dist(rng) * 50.f, 150.f + dist(rng) * 50.f));
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::LControl && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                grid.assign(5, std::vector<char>(5, ' '));
                anomalies.clear();
                std::uniform_int_distribution<int> dist(0, 4);
                for (int i = 0; i < 2; ++i) {
                    anomalies.push_back(std::make_unique<Anomaly>(250.f + dist(rng) * 50.f, 150.f + dist(rng) * 50.f));
                }
                cursorPos = {0, 0};
                disruption = 0.f;
                isPatternMatched = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::R) {
                grid[cursorPos.y][cursorPos.x] = 'R';
            } else if (event.key.code == sf::Keyboard::G) {
                grid[cursorPos.y][cursorPos.x] = 'G';
            } else if (event.key.code == sf::Keyboard::B) {
                grid[cursorPos.y][cursorPos.x] = 'B';
            } else if (event.key.code == sf::Keyboard::Space) {
                for (auto& anomaly : anomalies) {
                    if (anomaly->isActive() && std::abs(anomaly->getPosition().x - (250.f + cursorPos.x * 50.f)) < 10.f &&
                        std::abs(anomaly->getPosition().y - (150.f + cursorPos.y * 50.f)) < 10.f) {
                        anomaly->counter();
                    }
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                // Check pattern match
                bool matched = true;
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 3; ++x) {
                        if (grid[y + 1][x + 1] != targetPattern[y][x]) {
                            matched = false;
                            break;
                        }
                    }
                }
                isPatternMatched = matched;
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update anomalies
    std::uniform_int_distribution<int> dist(0, 4);
    for (auto& anomaly : anomalies) {
        if (anomaly->isActive() && dist(rng) % 20 == 0) {
            int x = (anomaly->getPosition().x - 250.f) / 50.f;
            int y = (anomaly->getPosition().y - 150.f) / 50.f;
            if (x >= 0 && x < 5 && y >= 0 && y < 5) {
                grid[y][x] = dist(rng) % 3 == 0 ? 'R' : dist(rng) % 2 == 0 ? 'G' : 'B';
                disruption += 5.f; // Increase disruption per anomaly action
            }
        }
    }

    // Cap disruption
    if (disruption > 100.f) disruption = 100.f;
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw threads
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (grid[y][x] != ' ') {
                Thread thread(250.f + x * 50.f, 150.f + y * 50.f, grid[y][x]);
                thread.render(window);
            }
        }
    }

    // Draw target pattern
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (targetPattern[y][x] != ' ') {
                Thread thread(500.f + x * 30.f, 150.f + y * 30.f, targetPattern[y][x]);
                thread.render(window);
            }
        }
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Draw anomalies
    for (const auto& anomaly : anomalies) {
        anomaly->render(window);
    }

    // Draw disruption meter
    sf::RectangleShape disruptionBar(sf::Vector2f(200.f * (disruption / 100.f), 20.f));
    disruptionBar.setPosition(300.f, 50.f);
    disruptionBar.setFillColor(disruption > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(disruptionBar);

    // Draw win/lose condition
    if (isPatternMatched) {
        sf::Text winText;
        winText.setString("Pattern Matched!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (disruption >= 100.f) {
        sf::Text loseText;
        loseText.setString("Grid Disrupted!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
