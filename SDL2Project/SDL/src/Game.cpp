#include <stdio.h>
#include <string>
#include "Game.h"
#include "GameStateBase.h"
#include "GameStateMachine.h"
//Screen dimension constants
#include"SDL_mixer.h"
#include"KeyState.h"
const Uint32 targetTime = 1 / LIMIT_FPS;
Game::Game()
{
	//Init create window for rendering
	Init();
}
bool Game::Init()
{
	bool success=	Renderer::GetInstance()->Init();
	GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
	return success;
}

void Game::Run()
{
	TTF_Init();
	SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
	gsplay.load(renderer);
	int currentTime, lastTime = 0;

	while (gsplay.getCurrentState() != STATE::NONE)
	{
		currentTime = SDL_GetTicks();

		if (currentTime - lastTime >= LIMIT_FPS) {

			gsplay.Update(0.2f);

			gsplay.Draw(renderer);

			lastTime = currentTime;
		}

	}

	int numCoin = gsplay.getCoin();
	int numGem = gsplay.getGem();
	int lastLevel = gsplay.getLastLevel();
	int* character_level = gsplay.getCharacterLevel();
	int** char_growth = gsplay.getCharGrowth();
	std::ofstream player_info("Data/player_info.txt");
	player_info << numCoin << ' ' << numGem << '\n';
	player_info << lastLevel << '\n';
	for (int i = 0; i < numCharacter; i++)
		player_info << character_level[i] << ' ' << char_growth[i][0] << ' ' << char_growth[i][1] << '\n';

	player_info.close();

	bool currentMusic = gsplay.getCurrentMusic();
	bool currentSFX = gsplay.getCurrentSfx();
	std::ofstream setting_info("Data/setting_sound.txt");
	setting_info << currentMusic << ' ' << currentSFX;
	setting_info.close();
			////Main loop flag
			//bool quit = false;
			////Event handler
			//SDL_Event e;
			//Uint32 lastUpdate = SDL_GetTicks();

			////int currentTime, lastTime = 0;

			//while (!quit)
			//{
			//	//Handle events on queue
			//	while (SDL_PollEvent(&e) != 0)
			//	{
			//		
			//		//User requests quit
			//		if (e.type == SDL_QUIT)
			//		{
			//			quit = true;
			//		}
			//		
			//		if (GameStateMachine::GetInstance()->HasState())
			//		{
			//			GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(e);
			//		}

			//		//Handle Touch Event
			//		if (GameStateMachine::GetInstance()->HasState())
			//		{
			//			GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(e);
			//		}

			//	}
			//	
			//	// Handle Key States (instead of Key events)
			//	/*if (GameStateMachine::GetInstance()->HasState())
			//	{
			//		GameStateMachine::GetInstance()->CurrentState()->HandleKeyStates();
			//	}*/
			//	KeyState::HandleKeyState();
			//	
			//	Uint32 current = SDL_GetTicks();

			//	float dT = (current - lastUpdate) / 1000.0f; // to convert to seconds

			//	lastUpdate = current;
			//	////Limit FPS
			//	if (dT < targetTime)
			//	{
			//		Update(targetTime);
			//		SDL_Delay(targetTime - dT);
			//	}
			//	else
			//	{
			//		Update(dT);	
			//	}
			//	
			//	//Update screen
			//	SDL_RenderPresent(Renderer::GetInstance()->GetRenderer());
			//}
}

void Game::Update(float deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();
	if (GameStateMachine::GetInstance()->HasState())
	{
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
		//Clear screen
		SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Renderer::GetInstance()->GetRenderer());  // function fills the screen with the color that was last set with SDL_SetRenderDrawColor
		GameStateMachine::GetInstance()->CurrentState()->Draw(Renderer::GetInstance()->GetRenderer());
	}
}


Game::~Game()
{
	Renderer::GetInstance()->FreeInstance();
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

