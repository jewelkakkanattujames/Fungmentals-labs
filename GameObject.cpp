#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(float x, float y, float w, float h,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: m_PositionSize{ x, y, w, h }, // Initialize the transform with the provided values
	m_ObjectColor{ r, g, b, a } // Initialize the color with the provided values
{
	// You can add additional initialization logic here if needed
}


void GameObject::Draw(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, m_ObjectColor.r, m_ObjectColor.g, m_ObjectColor.b, m_ObjectColor.a);
	// Set the render draw color to the object's color

	SDL_RenderFillRectF(pRenderer, &m_PositionSize);
	// Render a filled rectangle on the renderer using the object's transform
}

void GameObject::UpdatePositionX(float x)
{
	m_PositionSize.x += x;
	// Update the object's x position by adding the provided value
}

void GameObject::UpdatePositionY(float y)
{
	m_PositionSize.y += y;
	// Update the object's y position by adding the provided value
}
