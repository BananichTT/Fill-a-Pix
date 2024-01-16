#include <SFML/Graphics.hpp>
#include "Cell.h" 
#include "Grid.h" 

const int cellSize = 40;
const int gridRows = 10;
const int gridCols = 10;

void generateRandomLevel(Grid& grid) {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            // Заполняем ячейки случайным образом
            int randomValue = std::rand() % 2;  // Генерируем 0 или 1
            if (randomValue == 0) {
                grid.fillCell(i, j);  // Заполнение ячейки
            }
            else {
                grid.revealCell(i, j);  // Открытие ячейки
            }
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Mosaica");

    // Создание объекта сетки
    Grid grid(10, 10);  // Пример: сетка 10x10
    generateRandomLevel(grid);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Обработка щелчка левой кнопкой мыши
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // Расчет координат ячейки по пиксельным координатам
                    int cellX = mouseX / cellSize;  // Предположим, что cellSize определено
                    int cellY = mouseY / cellSize;

                    // Здесь можно вызвать методы Grid для изменения состояния ячейки
                    grid.revealCell(cellY, cellX);
                    // Или grid.fillCell(cellY, cellX); для заполнения ячейки
                }
            }
        }

        window.clear();
        // Отрисовка мозаики
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                const Cell& cell = grid.getCell(i, j);

                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                cellShape.setPosition(j * cellSize, i * cellSize);

                if (cell.getState() == Cell::State::Revealed) {
                    cellShape.setFillColor(sf::Color::White);  // Ячейка открыта
                }
                else if (cell.getState() == Cell::State::Filled) {
                    cellShape.setFillColor(sf::Color::Black);  // Ячейка заполнена
                }
                else {
                    cellShape.setFillColor(sf::Color::Magenta);   // Ячейка скрыта
                }

                window.draw(cellShape);

            }
        }

        // Отрисовка вертикальных линий-разграничителей
        for (int i = 0; i <= gridCols; ++i) {
            sf::RectangleShape line(sf::Vector2f(1, gridRows * cellSize));
            line.setPosition(i * cellSize, 0);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }

        // Отрисовка горизонтальных линий-разграничителей
        for (int i = 0; i <= gridRows; ++i) {
            sf::RectangleShape line(sf::Vector2f(gridCols * cellSize, 1));
            line.setPosition(0, i * cellSize);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }
        window.display();
    }

    return 0;
}