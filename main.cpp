#include <SFML/Graphics.hpp>
#include "Cell.h" 
#include "Grid.h" 

const int cellSize = 40;
const int gridRows = 10;
const int gridCols = 10;

void generateRandomLevel(Grid& grid) {
    // ������������� ���������� ��������� �����
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            // ��������� ������ ��������� �������
            int randomValue = std::rand() % 2;  // ���������� 0 ��� 1
            if (randomValue == 0) {
                grid.fillCell(i, j);  // ���������� ������
            }
            else {
                grid.revealCell(i, j);  // �������� ������
            }
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Mosaica");

    // �������� ������� �����
    Grid grid(10, 10);  // ������: ����� 10x10
    generateRandomLevel(grid);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ��������� ������ ����� ������� ����
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // ������ ��������� ������ �� ���������� �����������
                    int cellX = mouseX / cellSize;  // �����������, ��� cellSize ����������
                    int cellY = mouseY / cellSize;

                    // ����� ����� ������� ������ Grid ��� ��������� ��������� ������
                    grid.revealCell(cellY, cellX);
                    // ��� grid.fillCell(cellY, cellX); ��� ���������� ������
                }
            }
        }

        window.clear();
        // ��������� �������
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                const Cell& cell = grid.getCell(i, j);

                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                cellShape.setPosition(j * cellSize, i * cellSize);

                if (cell.getState() == Cell::State::Revealed) {
                    cellShape.setFillColor(sf::Color::White);  // ������ �������
                }
                else if (cell.getState() == Cell::State::Filled) {
                    cellShape.setFillColor(sf::Color::Black);  // ������ ���������
                }
                else {
                    cellShape.setFillColor(sf::Color::Magenta);   // ������ ������
                }

                window.draw(cellShape);

            }
        }

        // ��������� ������������ �����-���������������
        for (int i = 0; i <= gridCols; ++i) {
            sf::RectangleShape line(sf::Vector2f(1, gridRows * cellSize));
            line.setPosition(i * cellSize, 0);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }

        // ��������� �������������� �����-���������������
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