#include "GSMenu.h"
const int POSITION_X_GUARDIAN = 120;
const int POSITION_Y_GUARDIAN = 5;
const int POSITION_X_ADVENTURE = 15;
const int POSITION_Y_ADVENTURE = 180;
const int Y_GUARDIAN_PER_LOADING = 2;
const int Y_AVENTURE_PER_LOADING = -4;

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIGHT - btnPlay->GetHeight()) / 2 + 50);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	//Setting button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 150);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//CREDIT button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2 + 57, SCREEN_HEIGHT / 2 + 250);
	btnCredit->SetSize(100, 100);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnCredit);

	// game title
	texture = ResourceManagers::GetInstance()->GetTexture("img/guardian.png");
	GSMenu_Guardian = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	GSMenu_Guardian->SetSize(texture->originWidth, texture->originHeight);
	GSMenu_Guardian->Set2DPosition(POSITION_X_GUARDIAN, -200);

	texture = ResourceManagers::GetInstance()->GetTexture("img/adventure.png");
	GSMenu_Adventure = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	GSMenu_Adventure->SetSize(texture->originWidth, texture->originHeight);
	GSMenu_Adventure->Set2DPosition(POSITION_X_ADVENTURE, 721);

	//Set Sound
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/startScreen.wav");
	m_Sound->PlaySound();
	
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->stopAudio();
	// button close
	
}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	if (GSMenu_Guardian->GetPosition().y < POSITION_Y_GUARDIAN)
		GSMenu_Guardian->Set2DPosition(POSITION_X_GUARDIAN, min(POSITION_Y_GUARDIAN, GSMenu_Guardian->GetPosition().y + Y_GUARDIAN_PER_LOADING));
	GSMenu_Guardian->Draw(renderer);

	if (GSMenu_Adventure->GetPosition().y > POSITION_Y_ADVENTURE && GSMenu_Guardian->GetPosition().y == POSITION_Y_GUARDIAN)
		GSMenu_Adventure->Set2DPosition(POSITION_X_ADVENTURE, max(POSITION_Y_ADVENTURE, GSMenu_Adventure->Get2DPosition().y + Y_AVENTURE_PER_LOADING));
	GSMenu_Adventure->Draw(renderer);
}
