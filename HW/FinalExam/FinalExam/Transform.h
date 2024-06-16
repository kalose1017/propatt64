#pragma once
namespace Transform
{
	struct Vertex
	{
		float x;
		float y;
	};

	struct Vector
	{
		float x_meter;
		float y_meter;
	};

	Vertex MoveVertex(Vertex point, Vector meter);
	Vertex RotateVertex(Vertex point, float angle_degree);
	Vertex ScaleVertex(Vertex point, Vector meter);

};

void updatePosition(float& x, float speed, float deltaTime);
void resetPosition(float& posX1, float& posX2, float& posX3, float& posX4, float resetThreshold);
void applyGravityAndJump(float& posY, float& velocityY, bool& isJumping, float gravity, float deltaTime);
