#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int gridSize = 10;
const int cellSize = 30;

int numbers[gridSize][gridSize] = {};
bool isBlack[gridSize][gridSize] = {};

void randomizeGrid() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            isBlack[i][j] = std::rand() % 2;  // Инициализация случайным образом
        }
    }
}

void calculateNumbers() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int count = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < gridSize && nj >= 0 && nj < gridSize) {
                        count += isBlack[ni][nj];
                    }
                }
            }
            numbers[i][j] = count;
        }
    }
}

void drawGrid(sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            if (isBlack[i][j]) {
                cell.setFillColor(sf::Color::Black);
                sf::Text text(std::to_string(numbers[i][j]), font, 16);
                text.setPosition(i * cellSize + 10, j * cellSize + 5);
                text.setFillColor(sf::Color::White);
                window.draw(cell);
                window.draw(text);
            }
            else {
                cell.setFillColor(sf::Color::White);
                sf::Text text(std::to_string(numbers[i][j]), font, 16);
                text.setPosition(i * cellSize + 10, j * cellSize + 5);
                text.setFillColor(sf::Color::Black);
                window.draw(cell);
                window.draw(text);
            }
        }
    }
}

void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button) {
    int i = mousePos.x / cellSize;
    int j = mousePos.y / cellSize;

    if (button == sf::Mouse::Left) {
        isBlack[i][j] = !isBlack[i][j];  // Переключение состояния при нажатии левой кнопки мыши
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Jhaphan_mosaika");

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return EXIT_FAILURE;
    }

    randomizeGrid();
    calculateNumbers();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(mousePos, sf::Mouse::Left);
                }
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window, font);
        window.display();
    }

    return 0;
}
