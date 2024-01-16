#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int gridSize = 10;
const int cellSize = 30;

int grid[gridSize][gridSize] = {};

// Добавляем массив для хранения цифр
int numbers[gridSize][gridSize] = {};

void randomizeGrid() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = std::rand() % 2;
        }
    }
}

// Функция для вычисления и добавления цифр в массив numbers
void calculateNumbers() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // Если текущая ячейка закрашена, вычисляем количество закрашенных соседей
            if (grid[i][j] == 1) {
                int count = 0;

                // Проверяем восемь соседей
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int ni = i + x;
                        int nj = j + y;

                        // Проверяем, находится ли сосед в пределах сетки и не выходит ли за ее границы
                        if (ni >= 0 && ni < gridSize && nj >= 0 && nj < gridSize) {
                            count += grid[ni][nj];
                        }
                    }
                }

                // Записываем количество закрашенных соседей в массив numbers
                numbers[i][j] = count;
            }
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

            if (grid[i][j] == 1) {
                cell.setFillColor(sf::Color::Black);

                sf::Text text(std::to_string(numbers[i][j]), font, 16);
                text.setPosition(i * cellSize + 10, j * cellSize + 5);
                text.setFillColor(sf::Color::White);
                window.draw(cell);
                window.draw(text);
            }
            else {
                cell.setFillColor(sf::Color::White);

                window.draw(cell);

                if (grid[i][j] == 0) {
                    sf::Text text(std::to_string(numbers[i][j]), font, 16);
                    text.setPosition(i * cellSize + 10, j * cellSize + 5);
                    text.setFillColor(sf::Color::Black);
                    window.draw(text);
                }
            }
        }
    }
}


void handleMouseClick(sf::Vector2i mousePos) {
    int i = mousePos.x / cellSize;
    int j = mousePos.y / cellSize;

    grid[i][j] = 1 - grid[i][j];
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "Jhaphan_mosaika");

    // Определение шрифта
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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Обработка клика мыши
                    // (не забудьте обновить numbers после изменения grid)
                    handleMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    calculateNumbers();
                }
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window, font); // Передача шрифта в функцию отрисовки
        window.display();
    }

    return 0;
    }
