#include <iostream>
#include <bitset>
#include <string>

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

int main() {
    int keycode = 0;
    std::cout << "학번 : 202127064\n";
    std::cout << "이름 : 이지호\n\n";
    while (keycode >= 0 && keycode < 64)
    {
        std::cout << "화면에 그릴 물체 코드를 입력하세요 : ";
        std::cin >> keycode;

        // 입력된 숫자를 8비트 2진수로 변환
        std::bitset<8> binary(keycode);
        std::string binaryString = binary.to_string();

        // 2진수에서 2진수 1이 있는 자리에 색깔 출력
        std::cout << "2진수 값에 색깔 입히기!! : ";
        for (int i = 2; i < 8; ++i) {
            if (binaryString[i] == '1') {
                if (i == 7)
                    std::cout << "\x1b[37m"; // 흰색으로 출력
                else if (i == 6)
                    std::cout << "\x1b[31m"; // 빨강색으로 출력
                else if (i == 5)
                    std::cout << "\x1b[32m"; // 녹색으로 출력
                else if (i == 4)
                    std::cout << "\x1b[33m"; // 노란색으로 출력
                else if (i == 3)
                    std::cout << "\x1b[36m"; // 청록색으로 출력
                else if (i == 2)
                    std::cout << "\x1b[35m"; // 보라색으로 출력
            }
            std::cout << binaryString[i] << "\x1b[37m"; // 출력 후 재입력칸 흰색으로 출력
        }
        std::cout << std::endl;
    }
    std::cout << "프로그램을 종료합니다.";
    return 0;
}
/* *흰색 블록을 그리는 키코드 : 1 (1)
     * 빨강색 블록을 그리는 키코드 : 2 (10)
     * 녹색 블록을 그리는 키코드 : 4 (100)
     * 노란색 블록을 그리는 키코드 : 8 (1000)
     * 청록색 블록을 그리는 키코드 : 16 (10000)
     * 마젠타색 블록을 그리는 키코드 : 32 (100000)
     * 프로그램 종료 : 64 (1000000)
     *
     *프로그램을 시작하면 아래와 같이 쓰시오
     *
     *
     *화면에 그림을 그리는 프로그램입니다.
     * 학번 : 349218347(본인학번)
     *이름 : 본인이름
     *
     *화면에 그릴 물체코드를 입력하세요 :
 *(반복)*/