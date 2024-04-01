#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSOption::GSOption()
{
}


GSOption::~GSOption()
{
}

void GSOption::Exit()
{
}


void GSOption::Pause()
{

}
void GSOption::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	m_option = std::make_shared<Text>("Data/Caslon.ttf", textColor);
	m_option->SetSize(300, 50);
	m_option->Set2DPosition((SCREEN_WIDTH - m_option->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
	m_option->LoadFromRenderText("ADVENTURE");

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

}

void GSOption::HandleEvents()
{

}

void GSOption::HandleKeyEvents(SDL_Event& e)
{

}

void GSOption::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{

}

void GSOption::Update(float deltaTime)
{


	// Key State event

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}


	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_option->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}