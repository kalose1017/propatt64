#pragma once
#include <GLFW/glfw3.h>

void PixelToOpenGL(float FloorXpixel, float FloorYpixel);

// �⺻ Ŭ����
class Object {
public:
    virtual void OnCollisionEnter(Object& other) {}
};

// Player Ŭ����
class Player : public Object {
public:
    float posY = 450.0f;    // �ʱ� y ��ġ
    float velocityY = 0.0f; // y �� �ӵ�
    bool isJumping = false; // ���� ����

    void OnCollisionEnter(Object& other) override {
        drawPlayer();
    }
    void drawPlayer();
};

// EnemyBlock Ŭ����
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

// Floor Ŭ����
class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        drawFloor();
    }
    void drawFloor();
};

// Star Ŭ����
class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {}
};

// PhysicsAABB �Լ�
int PhysicsAABB(Object A, Object B);
