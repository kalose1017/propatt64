#include <iostream>
#include <chrono>
#include <thread>

//학번 : 202127064
//이름 : 이지호

using namespace std;

int main()
{
    int count = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    chrono::steady_clock::time_point prev_end = start;
    chrono::steady_clock::time_point end = start;

    while (count < 10)
    {
        prev_end = chrono::steady_clock::now(); //이전 반복의 종료 시간 측정
        end = chrono::steady_clock::now(); // 현재 반복의 종료 시간 측정
        prev_end = end; // 이전 반복의 종료 시간을 저장

        chrono::steady_clock::duration diff = start - prev_end;
        int delay_time_ms = 1000 - chrono::duration_cast<chrono::milliseconds>(diff).count();

        count++;

        this_thread::sleep_for(chrono::milliseconds(delay_time_ms)); // 딜레이 적용

        prev_end = chrono::steady_clock::now(); //이전 반복의 종료 시간 측정
        end = chrono::steady_clock::now(); // 현재 반복의 종료 시간 측정
        prev_end = end; // 이전 반복의 종료 시간을 저장
        chrono::steady_clock::duration actual_diff = prev_end - start;
        int actual_delay_time_ms = chrono::duration_cast<chrono::milliseconds>(actual_diff).count();

        // 딜레이 시간이 음수인 경우도 함께 출력
        cout << "1초 딜레이 측정: " << actual_delay_time_ms << "ms (오차: " << (actual_delay_time_ms - 1000) << "ms)" << endl;
        start = chrono::steady_clock::now(); // 현재 반복의 시작 시간 측정
    }
    return 0;
}
