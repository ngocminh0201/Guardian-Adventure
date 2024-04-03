#include "GSIntro.h"
#include "GameManager/ResourceManagers.h"
#include "GameObject/Define.h"
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	auto guardian = ResourceManagers::GetInstance()->GetTexture("img/guardian.png");
	m_logo2 = std::make_shared<Sprite2D>(guardian, SDL_FLIP_NONE);
	m_logo2->SetSize(600, 100);
	m_logo2->Set2DPosition((float)(SCREEN_WIDTH - m_logo2->GetWidth()) / 2, (float)(SCREEN_HEIDHT - m_logo2->GetHeight()) / 3);

	auto advanture = ResourceManagers::GetInstance()->GetTexture("img/adventure.png");
	m_logo1 = std::make_shared<Sprite2D>(advanture, SDL_FLIP_NONE);
	m_logo1->SetSize(800, 100);
	m_logo1->Set2DPosition((float)(SCREEN_WIDTH - m_logo1->GetWidth())/2 , (float)(SCREEN_HEIDHT - m_logo1->GetHeight())/3*2);
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{

}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(SDL_Event& e)
{
}

void GSIntro::HandleTouchEvents(SDL_Event& e)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5f)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw(SDL_Renderer* renderer)
{
	m_logo1->Draw(renderer);
	m_logo2->Draw(renderer);
}
