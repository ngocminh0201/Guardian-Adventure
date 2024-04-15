#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include <iostream>

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_map1.png");

	// background
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		isRunning = -1;
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	/*texture = ResourceManagers::GetInstance()->GetTexture("Character/0/idle1.png");
	obj = std::make_shared<SpriteAnimation>( texture, 1, 5, 4, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(charSize, charSize);
	obj->Set2DPosition(240, 400);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);*/


	m_KeyPress = 0;

	map = new GameMap;
	bool ccc = map->loadMap("Data/Textures/img", 1);
	
	character[0] = new Character;
	bool cc = character[0]->loadCharacter("Data/Textures/Character/0", 0);
	if (!cc || !ccc) {
		std::cout << "cc";
		exit(0);
	}

	std::ifstream fileMob("Data/Textures/img/Level_1/level_info.txt");
	if (fileMob.is_open() == false) {
		std::cout << "Missing mob file!!!";
	}
	int numMob = 0, typeMob = 0;
	fileMob >> typeMob;
	for (int i = 0; i < typeMob; i++)
	{
		fileMob >> numMob;
		for (int j = 0; j < numMob; j++)
		{
			Mob mob;
			int x, y;
			fileMob >> x >> y;
			mob.setX(x);
			mob.setY(y);
			mob.setId(i);
			int l, r;
			fileMob >> l >> r;
			mob.setRange(l, r);
			vMob.push_back(mob);
		}
	}
	int nCoin, nGem;

	fileMob >> nCoin;
	fileMob >> nGem;
	map->setNumCoin(nCoin);
	map->setNumGem(nGem);

	fileMob.close();

	for (int i = 0; i < vMob.size(); i++) {
		if (!vMob[i].loadMob("Data/Textures/img/Level_1/" + int2str(vMob[i].getId())))
		{
			std::cout << "no_MOB";
			exit(0);
		}
	}
	isRunning = 1;
	//character[0].setX(0);
	//character[0].setY(0);
	//character[0].setLevel(1);
	character[0]->setStatus(0);
	character[0]->setFrame(0);
	character[0]->setHp(100);

	for (int i = 0; i < numProjectile; i++)
	{
		std::string path = "Data/Textures/img/Projectile/" + int2str(i) + ".png";

		SDL_Surface* sf = IMG_Load(path.c_str());
		if (sf == NULL)
		{
			std::cout << "Missing projectile image!!!";
			exit(-1);
		}
		pr_w[i] = sf->w;
		pr_h[i] = sf->h;
		pr[i] = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), sf);

		SDL_FreeSurface(sf);
	}

	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	character[0]->handleInput(e);
	//If a key was pressed
	if (e.type == SDL_KEYDOWN )//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)                                                                                            
		{                                                                                                                     
		case SDLK_LEFT:
			//printf("MOVE LEFT");
			m_KeyPress |= 1;
			x -= 3;
			obj->Set2DPosition(x, y);
			break;
		case SDLK_DOWN:
			//printf("MOVE DOWN");
			m_KeyPress |= 1 << 1;
			y += 15;
			obj->Set2DPosition(x, y);

			break;
		case SDLK_RIGHT:
			//printf("MOVE RIGHT");
			m_KeyPress |= 1 << 2;
			x += 3;
			obj->Set2DPosition( x, y); 
			break;
		case SDLK_UP:
			//printf("MOVE UP");
			y -= 15;
			m_KeyPress |= 1 << 3;
			obj->Set2DPosition(x, y);
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP )//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	// Key State event

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{
			
		//	it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
	}
	m_currentTicks += 0.03;
	if (m_currentTicks >= 0.2) {
		
		character[0]->Update(map);
		
		
		m_currentTicks -= 0.2;
	}
	
	for (int i = vMob.size() - 1; i >= 0; i--)
	{
		vMob[i].tick(map, vProjectile, character[0], vExplosion, &Audio_Player);
	}
	for (int i = vProjectile.size() - 1; i >= 0; i--)
	{
		vProjectile[i].tick(map);
		//vProjectile[i].setObjectId(++id, 0);


	}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	//m_background->Draw(renderer);
	
	int view;
	if (character[0]->getX() >= SCREEN_WIDTH / 2)
		view = character[0]->getX() - SCREEN_WIDTH / 2;
	else view = 0;
	map->render(view, 0, 0);
	
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
	character[0]->show(view);
	
	for (int i = 0; i < vMob.size(); i++) {
		vMob[i].show(view);

		/// h / mh = x / 40 x = h * 40

		SDL_Rect tRect = { vMob[i].getX() - view, vMob[i].getY() - 20, 42, 7 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderFillRect(renderer, &tRect);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		int w = vMob[i].getHp() * 40 / vMob[i].getMaxHp();

		tRect = { vMob[i].getX() + 1 - view, vMob[i].getY() - 19, w, 5 };

		SDL_RenderFillRect(renderer, &tRect);

		tRect.x--;
		tRect.y += 6;
		tRect.h = 7;
		tRect.w = 42;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &tRect);

		std::pair<int, int> temp = vMob[i].getAttackBar();
		temp.first = min(temp.first, temp.second);

		tRect.x++;
		tRect.y++;
		tRect.h = 5;
		tRect.w = temp.first * 40 / temp.second;

		SDL_SetRenderDrawColor(renderer, 107, 107, 107, 255);
		if (temp.first == temp.second)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &tRect);

	}
	for (int i = 0; i < vProjectile.size(); i++) {

		vProjectile[i].setW(pr_w[vProjectile[i].getId()]);
		vProjectile[i].setH(pr_h[vProjectile[i].getId()]);

		SDL_Rect tRect = vProjectile[i].getRect();
		tRect.x -= view;
		SDL_RenderCopyEx(renderer, pr[vProjectile[i].getId()], NULL, &tRect, vProjectile[i].getAngle(), NULL, SDL_FLIP_NONE);
	}
	
}