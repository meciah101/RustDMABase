#include "Pch.h"
#include "Camera.h"

constexpr int screenWidth = 1920; //QUERY AUTOMATICALLY EVENTUALLY
constexpr int screenHeight = 1080;

Vector2 WorldToScreen(const Vector3& position, const ViewMatrix& viewMatrix)
{
    Vector3 transform(viewMatrix.matrix[0][3], viewMatrix.matrix[1][3], viewMatrix.matrix[2][3]);
    Vector3 right(viewMatrix.matrix[0][0], viewMatrix.matrix[1][0], viewMatrix.matrix[2][0]);
    Vector3 up(viewMatrix.matrix[0][1], viewMatrix.matrix[1][1], viewMatrix.matrix[2][1]);

    float w = Vector3::Dot(transform, position) + viewMatrix.matrix[3][3];

    if (w < 1.f)
        return Vector2(0, 0);

    float x = Vector3::Dot(right, position) + viewMatrix.matrix[3][0];
    float y = Vector3::Dot(up, position) + viewMatrix.matrix[3][1];

    return Vector2(
        (screenWidth / 2) * (1.f + x / w),
        (screenHeight / 2) * (1.f - y / w)
    );
}

ViewMatrix GetViewMatrix(uint64_t camera)
{
    ViewMatrix Matrix = TargetProcess.Read<ViewMatrix>(camera + 0x30C);
    return Matrix;
}