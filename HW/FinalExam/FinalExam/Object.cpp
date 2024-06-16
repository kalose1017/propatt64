#include "Object.h"
#include "Transform.h"

void PixelToOpenGL(float FloorXpixel, float FloorYpixel) {
    int Width = 800;
    int Height = 600;

    float FloorXgl = 2.0f * (FloorXpixel / Width) - 1.0f;
    float FloorYgl = 1.0f - 2.0f * (FloorYpixel / Height);

    glVertex2f(FloorXgl, FloorYgl);
}

void Player::drawPlayer() {
    // 검은색 테두리 사각형
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(97.0f, posY - 3.0f);
    PixelToOpenGL(97.0f, posY + 53.0f);
    PixelToOpenGL(153.0f, posY + 53.0f);
    PixelToOpenGL(153.0f, posY - 3.0f);
    glEnd();

    // 빨간색 사각형
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(100.0f, posY);
    PixelToOpenGL(100.0f, posY + 50.0f); // 50 픽셀 높이
    PixelToOpenGL(150.0f, posY + 50.0f);
    PixelToOpenGL(150.0f, posY);
    glEnd();
}

void EnemyBlock::drawCac() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(posX1, 400.0f);
    PixelToOpenGL(posX1, 500.0f);
    PixelToOpenGL(posX1 + 50.0f, 500.0f);
    PixelToOpenGL(posX1 + 50.0f, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX2, 200.0f);
    PixelToOpenGL(posX2, 500.0f);
    PixelToOpenGL(posX2 + 50.0f, 500.0f);
    PixelToOpenGL(posX2 + 50.0f, 200.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX3, 400.0f);
    PixelToOpenGL(posX3, 500.0f);
    PixelToOpenGL(posX3 + 50.0f, 500.0f);
    PixelToOpenGL(posX3 + 50.0f, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX4, 200.0f);
    PixelToOpenGL(posX4, 500.0f);
    PixelToOpenGL(posX4 + 50.0f, 500.0f);
    PixelToOpenGL(posX4 + 50.0f, 200.0f);
    glEnd();
}

void Floor::drawFloor() {
    glColor3f(1.0f, 0.78f, 0.05f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(0.0f, 500.0f);
    PixelToOpenGL(0.0f, 600.0f);
    PixelToOpenGL(800.0f, 600.0f);
    PixelToOpenGL(800.0f, 500.0f);
    glEnd();
}

int PhysicsAABB(Object A, Object B) {
    return 0;
}
