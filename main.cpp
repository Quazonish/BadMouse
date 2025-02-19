#include <windows.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
using namespace std;

float calculate_dis(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float dis = 0;
POINT prev_pos;
POINT curr_pos;
chrono::milliseconds duration;
float time_elapsed = 0;
bool canFly = true;
chrono::milliseconds del2 = chrono::milliseconds(1000);
void shakeMouse() {
    while (true) {
        this_thread::sleep_for(del2);
        SetCursorPos(curr_pos.x + (rand() % 3 - 1), curr_pos.y + (rand() % 3 - 1));
        if (canFly) {
            if (rand() % 101 == 50) {
                SetCursorPos(rand() % 1281, rand() % 721);
            }
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow){
//int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    chrono::milliseconds del = chrono::milliseconds(10);
    GetCursorPos(&prev_pos);
    chrono::steady_clock::time_point prev_time = chrono::high_resolution_clock::now();
    chrono::steady_clock::time_point curr_time = chrono::high_resolution_clock::now();
    thread wtf(shakeMouse);
    while (true) {
        GetCursorPos(&curr_pos);
        curr_time = chrono::high_resolution_clock::now();
        dis = calculate_dis(prev_pos.x, prev_pos.y, curr_pos.x, curr_pos.y);
        duration = chrono::duration_cast<chrono::milliseconds>(curr_time - prev_time);
        time_elapsed = duration.count() / 1000.0f;

        if (time_elapsed > 0) {
            if (dis / time_elapsed > 2000) {
                canFly = false;
                SetCursorPos(curr_pos.x + (rand() % 3 - 1) * 20, curr_pos.y + (rand() % 3 - 1) * 20);
            }
            else {
                canFly = true;
            }
        }

        prev_pos = curr_pos;
        prev_time = curr_time;

        this_thread::sleep_for(del);
    }

    return 0;
}