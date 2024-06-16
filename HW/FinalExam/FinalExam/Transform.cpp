#include "Transform.h"

void updatePosition(float& x, float speed, float deltaTime) {
    x -= speed * deltaTime;
}

void resetPosition(float& posX1, float& posX2, float& posX3, float& posX4, float resetThreshold) {
    if (posX1 < resetThreshold) {
        posX1 = 800.0f;
        posX2 = 1600.0f;
        posX3 = 2400.0f;
        posX4 = 2500.0f;
    }
}

void applyGravityAndJump(float& posY, float& velocityY, bool& isJumping, float gravity, float deltaTime) {
    if (isJumping) {
        velocityY -= gravity * deltaTime;
        posY -= velocityY * deltaTime;  // Á¡ÇÁ ½Ã yÁÂÇ¥¸¦ ³·Ãã

        if (posY >= 450.0f) { // ¹Ù´Ú À§Ä¡·Î °íÁ¤
            posY = 450.0f;
            velocityY = 0.0f;
            isJumping = false;
        }
    }
}
