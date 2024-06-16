#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"
#include "Transform.h"

using namespace std::chrono;

// 전역 변수로 Player 객체 선언
Player player;

// 시간 측정을 위한 변수
high_resolution_clock::time_point lastTime;

// Error callback 함수
void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s", description);
}

// Key callback 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !player.isJumping) {
        player.velocityY = 1000.0f; // 점프 시작 (5m = 500픽셀)
        player.isJumping = true;
    }
}

// Physics 함수
int Physics() {
    return 0;
}

// Initialize 함수
int Initialize() {
    glClearColor(0.0f, 0.11f, 0.25f, 1.0f);
    lastTime = high_resolution_clock::now();
    return 0;
}

// Update 함수
int Update(EnemyBlock& enemy, Player& player, float deltaTime) {
    float gravity = 9.8f * 100; // 중력 가속도 (픽셀 단위)

    // 플레이어 위치 업데이트
    applyGravityAndJump(player.posY, player.velocityY, player.isJumping, gravity, deltaTime);

    // 적 위치 업데이트
    float speed = 300.0f; // 1초에 300픽셀 이동
    updatePosition(enemy.posX1, speed, deltaTime);
    updatePosition(enemy.posX2, speed, deltaTime);
    updatePosition(enemy.posX3, speed, deltaTime);
    updatePosition(enemy.posX4, speed, deltaTime);
    resetPosition(enemy.posX1, enemy.posX2, enemy.posX3, enemy.posX4, -2600.0f);

    return 0;
}

// Render 함수
int Render(EnemyBlock& enemy, Player& player) {
    glClear(GL_COLOR_BUFFER_BIT);

    Object other;
    player.OnCollisionEnter(other);

    Floor floor;
    floor.OnCollisionEnter(other);

    enemy.OnCollisionEnter(other);

    return 0;
}

// main 함수
int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    EnemyBlock enemy;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // deltaTime 계산
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        duration<float> elapsedTime = duration_cast<duration<float>>(currentTime - lastTime);
        float deltaTime = elapsedTime.count();
        lastTime = currentTime;

        Physics();
        Update(enemy, player, deltaTime);
        Render(enemy, player);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}







