
#include <cstdlib>
#include <iostream>
#include "../state/state.hpp"
#include "./alphabeta.hpp"

int alphabeta(State *, int, int, int, int);

Move Alphabeta::get_move(State *state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();
//
    auto actions = state->legal_actions;
    int value = -1000000;
    Move best_move = actions[0];
    for (auto action: actions) {
        State *next_state = state->next_state(action);
        int new_value = alphabeta(next_state, depth, 1000000, -1000000, 1);
        if (new_value > value) {
            value = new_value;
            best_move = action;
        }
    }
    return best_move;
}

/*
function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth == 0 or node is terminal then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            if value > β then
                break (* β cutoff *)
            α := max(α, value)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            if value < α then
                break (* α cutoff *)
            β := min(β, value)
        return value
 */
int alphabeta(State *state, int depth, int alpha, int beta, int maximizingPlayer) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    if (depth == 0 || state->legal_actions.size() == 0) {
        return state->evaluate();
    }

    if (maximizingPlayer) {
        int value = -1000000;
        for (auto action: state->legal_actions) {
            State *next_state = state->next_state(action);
            value = std::max(value, alphabeta(next_state, depth - 1, alpha, beta, false));
            if (value > beta)
                break;
            alpha = std::max(alpha, value);
        }
        return value;
    } else {
        int value = 1000000;
        for (auto action: state->legal_actions) {
            State *next_state = state->next_state(action);
            value = std::min(value, alphabeta(next_state, depth - 1, alpha, beta, true));
            if (value < alpha)
                break;
            beta = std::min(beta, value);
        }
        return value;
    }
}