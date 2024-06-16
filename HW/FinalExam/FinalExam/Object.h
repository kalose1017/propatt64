#pragma once
#include <GLFW/glfw3.h>

void PixelToOpenGL(float FloorXpixel, float FloorYpixel);

// 기본 클래스
class Object {
public:
    virtual void OnCollisionEnter(Object& other) {}
};

// Player 클래스
class Player : public Object {
public:
    float posY = 450.0f;    // 초기 y 위치
    float velocityY = 0.0f; // y 축 속도
    bool isJumping = false; // 점프 상태

    void OnCollisionEnter(Object& other) override {
        drawPlayer();
    }
    void drawPlayer();
};

// EnemyBlock 클래스
class EnemyBlock : public Object {
public:
    float posX1 = 800.0f;
    float posX2 = 1600.0f;
    float posX3 = 2400.0f;
    float posX4 = 2500.0f;

    void OnCollisionEnter(Object& other) override {
        drawCac();
    }
    void drawCac();
};

// Floor 클래스
class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        drawFloor();
    }
    void drawFloor();
};

// Star 클래스
class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {}
};

// PhysicsAABB 함수
int PhysicsAABB(Object A, Object B);
