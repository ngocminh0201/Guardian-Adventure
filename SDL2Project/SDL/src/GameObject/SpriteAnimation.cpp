#include "SpriteAnimation.h"
#include "TextureManager.h"
#include <iostream>
SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_pTexture = texture;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	

	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Init()
{

}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
	if (m_flip == SDL_FLIP_HORIZONTAL) {
		std::cout << "Sprite is flipped horizontally." << std::endl;
	}
	else {
		std::cout << "Sprite is not flipped horizontally." << std::endl;
	}
}

void SpriteAnimation::Update(float deltatime)
{
	//m_currentTicks += deltatime;
		//if(m_currentTicks  >= m_frameTime) {
		//m_currentFrame++;
		//if (m_currentFrame >= m_frameCount) {
		//	m_currentFrame = 0;
		//}
		//m_currentTicks -= m_frameTime;
	m_currentTicks = SDL_GetTicks();
	m_frameTime = m_currentTicks - m_lastUpdate;
	m_lastUpdate = m_currentTicks;

	
	m_currentTime += m_frameTime;
	if (m_currentTime > m_frameTime) {
		m_currentFrame++;
		m_currentTime -= m_frameTime;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = m_frameCount-1;
		}
	}
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

void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{ 
	m_flip ==!flip;
	
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}

void SpriteAnimation::MoveLeft(float deltaTime)
{
	m_position.x += 20 * deltaTime;
	m_Vec2DPos.x -= m_animSpeed * deltaTime;
	SetFlip(SDL_FLIP_HORIZONTAL);
}
void SpriteAnimation::MoveRight(float deltaTime)
{
	m_position.x += 20 * deltaTime;
	m_Vec2DPos.x -= m_animSpeed * deltaTime;
	
}
