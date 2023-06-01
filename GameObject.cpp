#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(float x, float y, float w, float h,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: m_Transform{ x, y, w, h } // Initialize the transform with the provided values
	, m_Color{ r, g, b, a } // Initialize the color with the provided values
{

}

void GameObject::Draw(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	// Set the render draw color to the object's color

	SDL_RenderFillRectF(pRenderer, &m_Transform);
	// Render a filled rectangle on the renderer using the object's transform
}

void GameObject::UpdatePositionX(float x)
{
	m_Transform.x += x;
	// Update the object's x position by adding the provided value
}

void GameObject::UpdatePositionY(float y)
{
	m_Transform.y += y;
	// Update the object's y position by adding the provided value
}
