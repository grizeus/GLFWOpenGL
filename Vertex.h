#pragma once

struct triangle_vertex
{
	triangle_vertex(float x, float y, float z, float r, float g, float b)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	float pos[3]	= { 0.f, 0.f, 0.f };	// x y z
	float color[3]	= { 0.f, 0.f, 0.f };	// r g b
};

struct text_vertex
{
	text_vertex(float x, float y, float z, float q, float r, float g, float b, float tx, float ty)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		pos[3] = q;
		color[0] = r;
		color[1] = g;
		color[2] = b;
		coords[0] = tx;
		coords[1] = ty;
	}

	float pos[4] = { 0.f, 0.f, 0.f };	// x y z q(?)
	float color[3] = { 0.f, 0.f, 0.f };	// r g b
	float coords[2] = { 0.f, 0.f };
};

struct draw_details
{
	draw_details(uint32_t v, uint32_t e)
	{
		vao = v;
		numElements = e;
	}
	uint32_t vao = 0;
	uint32_t numElements = 0;
};
