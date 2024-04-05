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
	auto texture = ResourceManagers::GetInstance()->GetTexture("img/intro1.jpg");
	intro = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	intro->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	intro->Set2DPosition(0, 0);
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
	intro->Draw(renderer);
}
