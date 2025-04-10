#pragma once
#include <windows.h>

struct Vector2
{
	constexpr Vector2(
		const float x = 0.f,
		const float y = 0.f) noexcept :
		x(x), y(y) { }

	float x, y;
};

struct Vector3
{
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	const bool WordlToScreen(Vector2& out, float(*ViewMatrix)[4][4]);

	float x, y, z;
};
