#pragma comment(lib, "OpenGL32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

float blueBoxY = -0.95f; // 파란색 상자의 초기 위치 (바닥)
float blueBoxSpeed = 0.0f;
const float maxJumpSpeed = 10.0f; // 최대 점프 속도
const float gravity = -9.8f; // 중력 가속도
bool isJumping = false;
bool isFalling = false; // 하강 중인지 여부
bool isSpacePressed = false;
const float speedIncrement = 0.1f; // 점프 속도 증가량

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) // 스페이스바를 누르면 점프 시작
    {
        isJumping = true; // 점프 상태로 설정
        isFalling = false; // 하강 상태 해제
        blueBoxSpeed = 2.0f; // 초기 점프 속도 설정
        isSpacePressed = true; // 스페이스바 눌림 상태 설정
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) // 스페이스바를 떼면
    {
        isSpacePressed = false; // 스페이스바 눌림 상태 해제
    }
}

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void gravityBox(float deltaTime)
{
    if (isSpacePressed && isJumping && !isFalling) // 스페이스바가 눌린 상태에서 점프 중이고 하강 중이 아니면
    {
        blueBoxSpeed += speedIncrement; // 점프 속도 증가
        if (blueBoxSpeed > maxJumpSpeed) // 최대 점프 속도 제한
        {
            blueBoxSpeed = maxJumpSpeed;
        }
    }

    blueBoxSpeed += gravity * deltaTime;  // 중력 적용
    blueBoxY += blueBoxSpeed * deltaTime;  // 속도를 위치에 적용

    if (blueBoxSpeed < 0) // 상향 속도가 0보다 작아지면 하강 상태로 전환
    {
        isFalling = true;
    }

    if (blueBoxY <= -0.95f)
    {
        blueBoxY = -0.95f; // 바닥에 닿았을 때 위치 고정
        blueBoxSpeed = 0.0f; // 속도 제거
        isJumping = false; // 점프 상태 해제
        isFalling = false; // 하강 상태 해제
    }
}

void render()
{
    // 땅 그리기
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-1.0f, -0.95f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.95f);
    glEnd();

    // 파란색 사각형 그리기
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.1f, blueBoxY + 0.2f); // 사각형의 윗 변
    glVertex2f(-0.1f, blueBoxY);
    glVertex2f(0.1f, blueBoxY);
    glVertex2f(0.1f, blueBoxY + 0.2f); // 사각형의 윗 변
    glEnd();
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1000, 1000, "Dino", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    auto previousTime = std::chrono::high_resolution_clock::now(); // 현재 시간 가져오기

    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now(); // 현재 시간 가져오기
        std::chrono::duration<float> deltaTime = currentTime - previousTime; // 경과 시간 계산
        previousTime = currentTime; // 이전 시간 갱신

        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gravityBox(deltaTime.count());
        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
