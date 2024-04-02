//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색

//https://www.glfw.org/
//학번 : 202127064
//이름 : 이지호
#pragma comment (lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool IsRightBtnDown = false; // 마우스 오른쪽 버튼이 눌렸는지를 판단하는 변수
bool IsLeftBtnDown = false; // 마우스 왼쪽 버튼이 눌렸는지를 판단하는 변수
bool IsRightBtnDrag = false; // 마우스 오른쪽 버튼 드래그를 하는지 판단하는 변수
bool IsLeftBtnDrag = false; // 마우스 왼쪽 버튼 드래그를 하는지 판단하는 변수

// 마우스 클릭 콜백 함수
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) // 오른쪽 마우스 버튼 클릭 시 동작
    {
        if (action == GLFW_PRESS) // 마우스를 클릭했을 때
        {
            IsRightBtnDown = true;
            IsRightBtnDrag = false;
        }
        else if (action == GLFW_RELEASE) // 마우스 클릭을 해제했을 때
            IsRightBtnDown = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT) // 왼쪽 마우스 버튼 클릭 시 동작
    {
        if (action == GLFW_PRESS) // 마우스를 클릭했을 때
        {
            IsLeftBtnDown = true;
            IsLeftBtnDrag = false;
        }
        else if (action == GLFW_RELEASE) // 마우스 클릭을 해제했을 때
            IsLeftBtnDown = false;
    }
}

// 마우스 이동 콜백 함수
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (IsRightBtnDown && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // 오른쪽 마우스 버튼을 누른 상태가 지속될 때
    {
        IsRightBtnDrag = true;
        IsLeftBtnDrag = false;
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 화면을 파란색으로 변경
    }
    else if (IsLeftBtnDown && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // 왼쪽 마우스 버튼을 누른 상태가 지속될 때
    {
        IsRightBtnDrag = false;
        IsLeftBtnDrag = true;
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 화면을 보라(마젠타)색으로 변경
    }
    else
    {
        IsRightBtnDrag = false;
        IsLeftBtnDrag = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 윈도우 컨텍스트 설정
    glfwMakeContextCurrent(window);
    // 마우스 클릭 콜백 함수 등록
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // 마우스 이동 콜백 함수 등록
    glfwSetCursorPosCallback(window, cursor_position_callback);
    // 화면 처리 속도 증가 메서드
    glfwSwapInterval(1);

    //구동 루프
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (IsRightBtnDown) // 오른쪽 마우스를 누르면
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 화면을 빨간색으로 변경
        }
        else if (IsLeftBtnDown)
        {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 화면을 초록색으로 변경
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 아무것도 안 누른 상태면 화면을 검정색으로 변경
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
