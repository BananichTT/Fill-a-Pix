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

bool isPuzzleSolved() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (isBlack[i][j]) {
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

                if (count != numbers[i][j]) {
                    std::cout << "Puzzle not solved: (" << i << ", " << j << ") is black, but has " << count << " neighbors." << std::endl;
                    return false;
                }
            }
            else {
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

                if (count != numbers[i][j]) {
                    std::cout << "Puzzle not solved: (" << i << ", " << j << ") is white, but has " << count << " neighbors." << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}


void showCongratulations(sf::RenderWindow& window, sf::Font& font) {
    // Создаем два объекта sf::Text для двух строк
    sf::Text text1("Congratulations!", font, 30);
    sf::Text text2("Puzzle Solved!", font, 30);

    // Устанавливаем текст по центру окна
    sf::FloatRect textRect1 = text1.getLocalBounds();
    text1.setOrigin(textRect1.left + textRect1.width / 2.0f,
        textRect1.top + textRect1.height / 2.0f);
    text1.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 20.0f); // Поднимаем первую строку немного выше

    sf::FloatRect textRect2 = text2.getLocalBounds();
    text2.setOrigin(textRect2.left + textRect2.width / 2.0f,
        textRect2.top + textRect2.height / 2.0f);
    text2.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 20.0f); // Опускаем вторую строку немного ниже

    // Устанавливаем цвет текста
    text1.setFillColor(sf::Color::Black);
    text2.setFillColor(sf::Color::Black);

    window.clear(sf::Color::White);
    window.draw(text1);
    window.draw(text2);
    window.display();

    // Подождем некоторое время
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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

            if (isBlack[i][j]) {
                cell.setFillColor(sf::Color::Black);
                sf::Text text(std::to_string(numbers[i][j]), font, 16);
                text.setPosition(i * cellSize + 10, j * cellSize + 5);
                text.setFillColor(sf::Color::White);
                window.draw(cell);
                window.draw(text);
            }
            else {
                // Если не черный, отрисовываем белый квадрат и цифру
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

void handleKeyPress(sf::Keyboard::Key key, sf::Vector2i mousePos, sf::RenderWindow& window, sf::Font& font) {
    int i = mousePos.x / cellSize;
    int j = mousePos.y / cellSize;

    std::cout << "Key pressed: " << key << std::endl;

    if (key == sf::Keyboard::Space) {
        std::cout << "Space key pressed" << std::endl;
        // Переключение состояния всех черных квадратов при нажатии пробела
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (isBlack[i][j]) {
                    isBlack[i][j] = !isBlack[i][j];
                }
            }
        }
        
    }
    else if (key == sf::Keyboard::L) {
        std::cout << "L key pressed" << std::endl;
        // Переключение состояния квадрата по координатам при нажатии левой кнопки мыши
        isBlack[i][j] = !isBlack[i][j];
    }
    else if (key == sf::Keyboard::Enter) {
        std::cout << "Enter key pressed" << std::endl;
        if (isPuzzleSolved()) {
            std::cout << "Puzzle is solved" << std::endl;
            showCongratulations(window, font);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize + 100), "Fill-a-Pix");
    

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return EXIT_FAILURE;
    }

    randomizeGrid();
    calculateNumbers();

    
    sf::Text infoText1("Press Space to toggle black squares.", font, 16);
    sf::Text infoText2("Press Enter to check puzzle.", font, 16);

    float textWidth1 = infoText1.getGlobalBounds().width;
    float textWidth2 = infoText2.getGlobalBounds().width;

    infoText1.setPosition((window.getSize().x - textWidth1) / 2.0f, window.getSize().y - 50);
    infoText2.setPosition((window.getSize().x - textWidth2) / 2.0f, window.getSize().y - 30);

    infoText1.setFillColor(sf::Color::Black);
    infoText2.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleKeyPress(sf::Keyboard::L, mousePos, window, font);
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code, sf::Mouse::getPosition(window), window, font);
            }
        }

        window.clear(sf::Color::White);
        window.draw(infoText1);
        window.draw(infoText2);
        drawGrid(window, font);
        window.display();
    }

    return 0;
}
