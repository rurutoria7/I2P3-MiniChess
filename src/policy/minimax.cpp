
#include <cstdlib>
#include <iostream>
#include "../state/state.hpp"
#include "./minimax.hpp"

int minimax(State*, int, int);

Move Minimax::get_move(State *state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    int value = -1000000;
    Move best_move = actions[0];
    for (auto action : actions) {
        State *next_state = state->next_state(action);
        int new_value = minimax(next_state, depth, 1);
        if (new_value > value) {
            value = new_value;
            best_move = action;
        }
    }
    return best_move;
}

int minimax(State *state, int depth, int maximizingPlayer){
    if (depth == 0 || state->game_state != 3) {
        return state->evaluate();
    }
    if (maximizingPlayer) {
        int value = -1000000;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            value = std::max(value, minimax(next_state, depth - 1, false));
        }
        return value;
    } else {
        int value = 1000000;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            value = std::min(value, minimax(next_state, depth - 1, true));
        }
        return value;
    }
}