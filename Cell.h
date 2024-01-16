#pragma once
#include <SFML/Graphics.hpp>

class Cell {
public:
    enum class State { Hidden, Revealed, Filled };

    Cell() : state(State::Hidden) {}

    void reveal() {
        state = State::Revealed;
    }

    void fill() {
        state = State::Filled;
    }

    State getState() const {
        return state;
    }

private:
    State state;
};