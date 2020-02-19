#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

const int W = 1000;
const int H = 1000;

int count_neighbors(const bool *const state, const int x, const int y) {
    int count = 0;
    for (int yd = -1; yd <= 1; yd++) {
        int y_ = (y + H + yd) % H;
        for (int xd = -1; xd <= 1; xd++) {
            if (yd == 0 && xd == 0) continue;
            int x_ = (x + W + xd) % W;
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
                next[i] = (n == 2 || n == 3);
            } else {
                next[i] = (n == 3);
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

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; ++i) {
        compute_transition(current, next);
        swap(current, next);
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << ms.count() << "ms" << endl;
}