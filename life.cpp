#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

const int W = 60;
const int H = 20;

int count_neighbors(const bool *const state, const int x, const int y) {
    int count = 0;
    for (int xd = -1; xd <= 1; xd ++) {
        int x_ = (x + W + xd) % W;
        for (int yd = -1; yd <= 1; yd++) {
            if (yd == 0 && xd == 0) continue;
            int y_ = (y + H + yd) % H;
            count += state[y_ * W + x_];
        }
    }
    return count;
}

void compute_transition(const bool *const current, bool *const next) { 
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            int i = y * W + x;
            int n = count_neighbors(current, x, y);
            if (current[i]) {
                if (n == 2 || n == 3)
                    next[i] = true;
                else 
                    next[i] = false;
            } else {
                if (n == 3)
                    next[i] = true;
                else
                    next[i] = false;
            }
        }
    }
}

void print_grid(const bool *const grid) {
    cout << "\033[2J";
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            cout << (grid[y*W+x] ? "#" : " ");
        }
        cout << endl;
    }
}

int main() {
    bool *current = (bool*) malloc( sizeof(bool) * W * H );
    bool *next = (bool*) malloc( sizeof(bool) * W * H );

    for (int i = 0; i < W*H; ++i)
        current[i] = rand() % 2;

    for (int i = 0; i < 500; ++i) {
        print_grid(current);

        compute_transition(current, next);

        swap(current, next);
        this_thread::sleep_for(chrono::milliseconds(20));
    }
        
}