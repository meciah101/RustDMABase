#pragma once
ViewMatrix GetViewMatrix(uint64_t camera);
Vector2 WorldToScreen(const Vector3& position, const ViewMatrix& viewMatrix);