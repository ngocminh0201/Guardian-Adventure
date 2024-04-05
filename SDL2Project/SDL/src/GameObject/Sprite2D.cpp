#include "Sprite2D.h"
#include "TextureManager.h"
//Sprite2D::Sprite2D()
//{
//	Init();
//}

Sprite2D::Sprite2D(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(texture->originWidth), m_iHeight(texture->originHeight)
{

	m_flip = flip;
	Init();
	
}

void Sprite2D::Init()
{
	// Init Camera
}

void Sprite2D::Draw(SDL_Renderer * renderer)
{
	//Get2DPosition();
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
	
}

void Sprite2D::Update(float deltatime)
{
	// Check for input events (e.g., keyboard input)
	SDL_PumpEvents();
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		// Set flip to flip horizontally
		m_flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		// If the left arrow key is not pressed, set flip to default (no flip)
		m_flip = SDL_FLIP_NONE;
	}
}

void Sprite2D::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector3 Sprite2D::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Sprite2D::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Sprite2D::GetWidth()
{
	return m_iWidth;
}

int Sprite2D::GetHeight()
{
	return m_iHeight;
}

void Sprite2D::SetRotation(double angle)
{
	m_angle = angle;
}

void Sprite2D::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;

}

