#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct moves {
    int start, dest;
};

void print_moves(vector<moves> mov) {
    for (int i = 0; i < mov.size(); i++)
        cout << "move from " << mov[i].start << " to " << mov[i].dest << endl;
}

void swap_cars(vector<int> *current_state, vector<int> final_state, map<int, int> *car_positions, int car1, int car2, int now_fixing) {
    int car2_position  = (*car_positions)[car2];
    (*car_positions)[car1] = car2_position;
    (*current_state)[now_fixing] = car2;
    (*car_positions)[car2] = now_fixing;
    (*current_state)[car2_position] = car1;
}

vector<moves> add_new_move(vector<moves> moves_to_final, int start_pos, int end_pos) {
    moves new_move;
    new_move.start = start_pos;
    new_move.dest = end_pos;
    moves_to_final.push_back(new_move);
    return moves_to_final;
}

vector<moves> arrange_cars(int n, vector<int> initial, const vector<int> final_state) {
    vector<moves> moves_to_final;
    map<int, int> car_positions;

    for (int i = 0; i < n; i++) {
        car_positions.insert(make_pair(initial[i], i));
    }
    
    vector<int> current_state = initial;
    int now_fixing = 0;
    
    while (now_fixing < n) {
        if (current_state[now_fixing] != final_state[now_fixing]) {
            /* move empty space to position we're fixing */
            int empty_space = car_positions[0];
            swap_cars(&current_state, final_state, &car_positions, current_state[now_fixing], 0, now_fixing);
            /* add move */
            if (empty_space != now_fixing) {
                moves_to_final = add_new_move(moves_to_final, now_fixing, empty_space);
            }
            /* move right car to current position */
            int right_cars_position = car_positions[final_state[now_fixing]];
            swap_cars(&current_state, final_state, &car_positions, 0, final_state[now_fixing], now_fixing);
            /* add move */
            if(right_cars_position != now_fixing) {
                moves_to_final = add_new_move(moves_to_final, right_cars_position, now_fixing);
            }
        }
        now_fixing++;
    }
    return moves_to_final;
}

int main() {
    vector<int> init = {1, 2, 0, 3};
    vector<int> final = {3, 1, 2, 0};
    
    vector<moves> mov = arrange_cars(4, init, final);
    print_moves(mov);

    return 0;
}
