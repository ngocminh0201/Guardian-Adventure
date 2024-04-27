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
	currentState = prev = STATE::MENU;
	current_character = 0;
	current_level = 1;
    currentMusic = currentSFX = true;
	for (int i = 0; i < numItem; i++)
		itemDrop[i] = NULL;

	for (int i = 0; i < numProjectile; i++)
		pr[i] = NULL;

	SupportItemTexture = NULL;

	for (int i = 0; i < 3; i++)
		SupportItem_Animation[i] = NULL;

	explosion = NULL;

	map = new GameMap;
    scr = new GSSelect;

	numGem = 0, numCoin = 0;

	paused = false;
	frame_back = 0;
	frame_char3 = 1000;

	id = 0;

	prev_char_level = NULL;

	char_growth = NULL;
}


GSPlay::~GSPlay()
{
	while (vProjectile.size()) vProjectile.pop_back();
	while (vMob.size()) vMob.pop_back();

	for (int i = 0; i < numItem; i++)
		SDL_DestroyTexture(itemDrop[i]);

	for (int i = 0; i < numProjectile; i++)
		SDL_DestroyTexture(pr[i]);

	SDL_DestroyTexture(SupportItemTexture);

	for (int i = 0; i < 3; i++)
		SDL_DestroyTexture(SupportItem_Animation[i]);

	SDL_DestroyTexture(explosion);

	delete(char_growth);
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_map1.png");

	// background
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
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
    load(Renderer::GetInstance()->GetRenderer());
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
	//_character[0]->handleInput(e);
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

void GSPlay::load(SDL_Renderer* renderer) {
    character_level = new int[numCharacter];
    prev_char_level = new int[numCharacter];

    char_growth = new int* [numCharacter];
    for (int i = 0; i < numCharacter; i++)
        char_growth[i] = new int[2];

    std::ifstream player_info("Data/player_info.txt");
    player_info >> numCoin >> numGem;
    player_info >> lastLevel;
    for (int i = 0; i < numCharacter; i++) {
        player_info >> character_level[i] >> char_growth[i][0] >> char_growth[i][1];
    }

    player_info.close();

    scr->loadTexture(Renderer::GetInstance()->GetRenderer());
    //////////////

    for (int i = 0; i < numCharacter; i++) {
        character[i] = new Character;
        if (!character[i]->loadCharacter("Data/Textures/Character/" + int2str(i), renderer, i))
        {
            std::cout << "Can't load character " << i << "!!!";
            exit(-1);
        }
    }
        
    /////////////

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
        pr[i] = SDL_CreateTextureFromSurface(renderer, sf);

        SDL_FreeSurface(sf); sf = NULL;
    }

    std::string path = "Data/Textures/img/explosion.png";
    SDL_Surface* sf = IMG_Load(path.c_str());

    explosion = SDL_CreateTextureFromSurface(renderer, sf);

    SDL_FreeSurface(sf);

    //////////////

    for (int i = 0; i < numItem; i++) {
        std::string path = "Data/Textures/img/item" + int2str(i) + ".png";

        SDL_Surface* sf = IMG_Load(path.c_str());
        if (sf == NULL)
        {
            std::cout << "Missing item image!!!";
            exit(-1);
        }
        itemDrop[i] = SDL_CreateTextureFromSurface(renderer, sf);
        SDL_FreeSurface(sf); sf = NULL;
    }

    //////////////

    SDL_Surface* loadSurface = IMG_Load("Data/Textures/img/lp.png");

    SupportItemTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);

    for (int i = 0; i < 3; i++)
    {
        std::string path = "Data/Textures/img/lp" + int2str(i) + ".png";
        loadSurface = IMG_Load(path.c_str());
        if (loadSurface == NULL)
        {
            std::cout << "Missing lp image!!!";
            exit(-1);
        }
        SupportItem_Animation[i] = SDL_CreateTextureFromSurface(renderer, loadSurface);
        SDL_FreeSurface(loadSurface); loadSurface = NULL;
    }

    std::ifstream file("Data/setting_sound.txt");
    file >> currentMusic >> currentSFX;
    file.close();

    Audio_Player.loadAudioFiles();
    Audio_Player.setMusic(currentMusic);
    Audio_Player.setSfx(currentSFX);

    boss.loadBoss(renderer);
}

bool GSPlay::loadLevel(int level, SDL_Renderer* renderer)
{
    if (!map->loadMap("Data/Textures/img", renderer, level))
        return false;

    std::string map_path = "Data/Textures/img/Level_" + int2str(level) + "/";
    std::ifstream fileMob((map_path + "level_info.txt").c_str());
    {
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
    }

    int nCoin, nGem;

    fileMob >> nCoin;
    fileMob >> nGem;
    map->setNumCoin(nCoin);
    map->setNumGem(nGem);

    fileMob.close();

    for (int i = 0; i < vMob.size(); i++) {
        if (!vMob[i].loadMob(map_path + int2str(vMob[i].getId()), renderer))
        {
            return false;
        }
    }
    

    if (level < numLevel)
    {
        SupportItem new_SupportItem;
        new_SupportItem.setType(1);
        new_SupportItem.setW(70);
        new_SupportItem.setH(70);
        new_SupportItem.setX(map->get_supportItem_pos().back());
        map->pop();
        new_SupportItem.loadVar({ 4, 14 }, { 4, 11 }, { 4, 17 });
        v_SupportItem.push_back(new_SupportItem);
    }

    return 1;
}

void GSPlay::Update(float deltaTime)
{	
    SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
    prev_map = current_level;
    prev_char = current_character;
    for (int i = 0; i < numCharacter; i++)
        prev_char_level[i] = character_level[i];
    prev = currentState;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            currentState = STATE::NONE;
            std::ofstream player_info("Data/player_info.txt");
            player_info << numCoin << ' ' << numGem << '\n';
            player_info << lastLevel << '\n';
            for (int i = 0; i < numCharacter; i++)
                player_info << character_level[i] << ' ' << char_growth[i][0] << ' ' << char_growth[i][1] << '\n';

            player_info.close();

            std::ofstream setting_info("Data/setting_sound.txt");
            setting_info << currentMusic << ' ' << currentSFX;
            setting_info.close();
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            
            int x, y;
            SDL_GetMouseState(&x, &y);
            scr->handleMouseInput(x, y, currentState, current_level, current_character, character_level, 
                                  numCoin, numGem, lastLevel, paused, currentMusic, currentSFX);

            bool click = true;

            if (current_level != prev_map)
            {
                Audio_Player.changeMap();
                click = false;
            }

            if (prev_char != current_character)
            {
                Audio_Player.selectCharacter();
                click = false;
            }

            if (prev_char_level[current_character] != character_level[current_character])
            {
                if (prev_char_level[current_character]) Audio_Player.upgradeCharacter();
                else Audio_Player.unlockCharacter();
                click = false;
            }

            if (prev == STATE::SELECT && currentState == STATE::PLAY)
            {
                Audio_Player.playButton();
                click = false;
                character[current_character]->setX(0);
                character[current_character]->setY(0);
                vMob.clear();
                rectMob.clear();
                vItem.clear();
                vItem_temp.clear();
                vProjectile.clear();
                vExplosion.clear();
                v_SupportItem.clear();
                character[current_character]->setLevel(character_level[current_character]);

                int newDmg = character[current_character]->getBaseDmg();
                if (character_level[current_character] > 0)
                    newDmg += (character_level[current_character] - 1) * char_growth[current_character][0];
                character[current_character]->setDmg(newDmg);

                int newHp = character[current_character]->getBaseHp();
                if (character_level[current_character] > 0)
                    newHp += (character_level[current_character] - 1) * char_growth[current_character][1];
                character[current_character]->setMaxHp(newHp);

                character[current_character]->setHp(character[current_character]->getMaxHp());
                character[current_character]->setStatus(Character_STATUS::IDLE);
                character[current_character]->setFrame(0);
                frame_back = 0;
                delete(map);
                map = new GameMap;
                boss.reset();
                loadLevel(current_level, renderer);
            }
            if (click) Audio_Player.mouse_click();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            scr->handleKeyInput(event, paused, currentState);
        }
        if (currentState == STATE::PLAY) {
            character[current_character]->handleInput(event);
        }
    }

    SDL_RenderClear(renderer);
    //std::cout << "Running: " << currentState << '\n';
    if (prev != currentState) Audio_Player.stopAudio();

    if (currentState == STATE::MENU) {
        time += 0.033f;
        //std::cout << time << '\n';
        if (time <= 1.0f) {
            scr->startIntro(renderer);
        }
        else {
            scr->startScreen(renderer);
        }
        Audio_Player.playBackgroundMusic(currentState, current_level);
    }
    else if (currentState == STATE::SELECT) {
        int baseHp = character[current_character]->getBaseHp();
        int baseDmg = character[current_character]->getBaseDmg();
        scr->levelSelection(renderer, current_level, current_character, character_level, numCoin, numGem, lastLevel, baseHp, baseDmg, char_growth);
        Audio_Player.playBackgroundMusic(currentState, current_level);
    }
    else if (currentState == STATE::PLAY) {
        if (paused) return;

        for (int i = 0; i < vMob.size(); i++) {
            rectMob.push_back({ vMob[i].getRect(), vMob[i].getHp() });
            //std::cout << i << ' ' << vMob[i].getHp() << '\n';
        }

        frame_char3++;

        if (frame_char3 <= 3 * 30)
            character[current_character]->setVelX(MAX_RUN_SPEED + 10);
        else
            character[current_character]->setVelX(MAX_RUN_SPEED);

        if(character[current_character]->jumped())
            Audio_Player.character_jump();

        if (character[current_character]->getMove() && 
                                        character[current_character]->getStatus() < Character_STATUS::DIED && 
                                                character[current_character]->onGround())
        {
            if (current_character == 1 || current_character == 2)
                Audio_Player.character_move(1);
            else
                Audio_Player.character_move(0);
        }
        else Audio_Player.setMove();

        if (current_level == numLevel)
            boss.Update(character[current_character], vItem);

        character[current_character]->Update(map, rectMob, vProjectile, &Audio_Player);


        if (character[current_character]->startAttack() && character[current_character]->getStatus() == Character_STATUS::ATTACK)
            Audio_Player.character_attack(current_character);

        character[current_character]->setObjectId(++id, 0);

        if (character[current_character]->getStatus() == Character_STATUS::DIED || 
               character[current_character]->getStatus() == Character_STATUS::VICTORY)
        {
            if (frame_back == 0)
            {
                Audio_Player.stopAudio();
                if (character[current_character]->getStatus() == Character_STATUS::DIED)
                    Audio_Player.loseGame();
                else
                    Audio_Player.winGame();
            }
            frame_back++;
            if (frame_back == 5 * 30) {
                currentState = STATE::SELECT;
                if (character[current_character]->getStatus() == Character_STATUS::VICTORY && lastLevel == current_level)
                    lastLevel++;
                character[current_character]->setStatus(Character_STATUS::IDLE);
                Audio_Player.stopAudio();
            }
        }
        else
        {
            Audio_Player.playBackgroundMusic(currentState, current_level);
        }

        if (vItem.size())
            for (int i = vItem.size() - 1; i >= 0; i--)
            {
                vItem[i].Update(character[current_character]->getRect(), map);

                vItem[i].setObjectId(++id, 0);

                if (collision(vItem[i].getRect(), character[current_character]->getRect()) && vItem[i].getFell())
                {
                    if (vItem[i].getId() == 3)
                        vItem[i].dropItem(vItem_temp, Rand(1, map->getNumCoin()), Rand(1, map->getNumGem()), character[current_character]->getMaxHp());
                    else if (vItem[i].getId() == 2)
                    {
                        if (character[current_character]->getStatus() < Character_STATUS::DIED) {
                            int nHp = min(character[current_character]->getMaxHp(), character[current_character]->getHp() + vItem[i].getVal());
                            character[current_character]->setHp(nHp);
                            Audio_Player.character_heal();
                        }
                    }
                    else if (vItem[i].getId() == 1)
                    {
                        numGem += vItem[i].getVal();
                        Audio_Player.collectItem();
                    }
                    else
                    {
                        numCoin += vItem[i].getVal();
                        Audio_Player.collectItem();
                    }
                    std::swap(vItem[i], vItem.back());
                    vItem.pop_back();
                }
                else if (vItem[i].getY() + vItem[i].getH() >= SCREEN_HEIGHT - 1)
                {
                    std::swap(vItem[i], vItem.back());
                    vItem.pop_back();
                }
            }

        while (vItem_temp.size())
        {
            vItem.push_back(vItem_temp.back());
            vItem_temp.pop_back();
        }

        if (map->get_supportItem_pos().size() && map->get_supportItem_pos().back() <= character[current_character]->getX())
        {
            SupportItem new_supportItem;
            new_supportItem.setX(SCREEN_WIDTH);
            new_supportItem.setVelX(-5);
            new_supportItem.setType(0);
            map->pop();
            v_SupportItem.push_back(new_supportItem);
        }

        if (vMob.size())
            for (int i = vMob.size() - 1; i >= 0; i--)
            {
                vMob[i].setHp(rectMob[i].second);
                vMob[i].setObjectId(++id, 0);
                if (rectMob[i].second == 0)
                {
                    Audio_Player.mobDie();
                    vMob[i].spawnItem(vItem);
                    std::swap(rectMob[i], rectMob.back());
                    std::swap(vMob[i], vMob.back());
                    rectMob.pop_back();
                    vMob.pop_back();
                }
                else
                    vMob[i].update(map, vProjectile, character[current_character], vExplosion, &Audio_Player);
            }
        if (vProjectile.size())
        {
            if (current_character == 1)
                character1();
            else
            {
                for (int i = vProjectile.size() - 1; i >= 0; i--)
                {
                    vProjectile[i].update(map);
                    vProjectile[i].setObjectId(++id, 0);
                    if (vProjectile[i].done())
                    {
                        if (vProjectile[i].getThrew())
                        {
                            vExplosion.push_back({ vProjectile[i].getHitBox(), vProjectile[i].getRadius(), vProjectile[i].getDmg(), 15 });
                            Audio_Player.bomb_explosion();
                        }
                        std::swap(vProjectile[i], vProjectile.back());
                        vProjectile.pop_back();
                    }
                    else if (vProjectile[i].getHostile())
                    {
                        if (collision(vProjectile[i].getHitBox(), character[current_character]->getRect()))
                        {
                            int chance = Rand(1, 2);
                            if (current_character != 2 || chance == 1)
                            {
                                int lastHp = character[current_character]->getHp();
                                character[current_character]->takeDamage(vProjectile[i].getDmg());
                                if (lastHp > 0) {
                                    Audio_Player.stopSfx();
                                    Audio_Player.character_hurt();
                                }
                            }
                            if (vProjectile[i].getThrew())
                            {
                                vExplosion.push_back({ vProjectile[i].getHitBox(), vProjectile[i].getRadius(), 0, 15 });
                                Audio_Player.bomb_explosion();
                            }
                            std::swap(vProjectile[i], vProjectile.back());
                            vProjectile.pop_back();
                        }
                    }
                    else if (!vProjectile[i].getHostile())
                    {
                        if (current_level == numLevel)
                        {
                            if (collision(vProjectile[i].getHitBox(), boss.getBossHitbox()) && boss.vulnerable())
                            {
                                if (current_character == 3)
                                    frame_char3 = 0;
                                if (current_character == 4)
                                {
                                    int chance = Rand(1, 4);
                                    if (chance == 3)
                                    {
                                        int newHp = character[current_character]->getHp() + character[current_character]->getMaxHp() / 10;
                                        character[current_character]->setHp(newHp);
                                        Audio_Player.character_heal();
                                    }
                                }
                                int lastHp = boss.getHp();
                                boss.takeDamage(vProjectile[i].getDmg());
                                if (lastHp > 0)
                                    Audio_Player.boss_hurt();
                                std::swap(vProjectile[i], vProjectile.back());
                                vProjectile.pop_back();
                            }
                        }
                        if (vMob.size())
                            for (int j = vMob.size() - 1; j >= 0; j--)
                            {
                                if (collision(rectMob[j].first, vProjectile[i].getRect()))
                                {
                                    if (current_character == 3)
                                        frame_char3 = 0;
                                    if (current_character == 4)
                                    {
                                        int chance = Rand(1, 4);
                                        if (chance == 3)
                                        {
                                            int newHp = character[current_character]->getHp() + character[current_character]->getMaxHp() / 10;
                                            character[current_character]->setHp(newHp);
                                            Audio_Player.character_heal();
                                        }
                                    }
                                    rectMob[j].second = max(0, rectMob[j].second - vProjectile[i].getDmg());
                                    vMob[j].setHp(rectMob[j].second);
                                    if (rectMob[j].second > 0)
                                        Audio_Player.mobHurt();
                                    std::swap(vProjectile[i], vProjectile.back());
                                    vProjectile.pop_back();
                                    break;
                                }
                            }
                    }
                }
            }
        }

        if (v_SupportItem.size())
        {
            for (int i = v_SupportItem.size() - 1; i >= 0; i--)
            {
                v_SupportItem[i].update(character[current_character]->getRect(), map, vItem);
                if (v_SupportItem[i].get_done())
                {
                    std::swap(v_SupportItem[i], v_SupportItem.back());
                    v_SupportItem.pop_back();
                }
            }
        }
        rectMob.clear();
        for (int i = 0; i < vExplosion.size(); i++)
        {
            if (distance(vExplosion[i].rect, character[current_character]->getRect()) <= vExplosion[i].radius && vExplosion[i].frame == 15)
            {
                int lastHp = character[current_character]->getHp();
                character[current_character]->takeDamage(vExplosion[i].dmg);
                if (lastHp > 0) {
                    Audio_Player.stopSfx();
                    Audio_Player.character_hurt();

                }
            }
            vExplosion[i].frame--;
        }
    }
    else if (currentState == STATE::CREDIT) {
        scr->screenCredit(renderer);
        Audio_Player.playBackgroundMusic(currentState, current_level);
    }
    else if (currentState == STATE::SETTING) {
        if (!currentMusic) Audio_Player.stopAudio();
        if (!currentSFX) Audio_Player.stopSfx();
        scr->screenSetting(renderer, currentMusic, currentSFX);
        Audio_Player.setMusic(currentMusic);
        Audio_Player.setSfx(currentSFX);
        Audio_Player.playBackgroundMusic(currentState, current_level);
    } 
    else if (currentState == STATE::HELP) {
        scr->screenHelp(renderer);
        Audio_Player.playBackgroundMusic(currentState, current_level);
    }
}

void GSPlay::character1()
{
    for (int i = vProjectile.size() - 1; i >= 0; i--)
    {
        vProjectile[i].update(map);
        vProjectile[i].setObjectId(++id, 0);
        if (vProjectile[i].done())
        {
            if (vProjectile[i].getThrew()) {
                if (distance(vProjectile[i].getHitBox(), character[current_character]->getRect()) <= vProjectile[i].getRadius())
                {
                    int curHp = character[current_character]->getHp() - vProjectile[i].getDmg();
                    character[current_character]->setHp(curHp);
                }
                vExplosion.push_back({ vProjectile[i].getHitBox(), vProjectile[i].getRadius(), vProjectile[i].getDmg(), 15 });
                Audio_Player.bomb_explosion();
            }
            std::swap(vProjectile[i], vProjectile.back());
            vProjectile.pop_back();
        }
        else if (vProjectile[i].getHostile())
        {
            if (collision(vProjectile[i].getHitBox(), character[current_character]->getRect()))
            {
                int curHp = character[current_character]->getHp() - vProjectile[i].getDmg();
                character[current_character]->setHp(curHp);
                if (vProjectile[i].getThrew())
                {
                    vExplosion.push_back({ vProjectile[i].getHitBox(), vProjectile[i].getRadius(), vProjectile[i].getDmg(), 15 });
                    Audio_Player.bomb_explosion();
                }
                std::swap(vProjectile[i], vProjectile.back());
                vProjectile.pop_back();
            }
        }
        else if (!vProjectile[i].getHostile())
        {
            if (vMob.size())
                for (int j = vMob.size() - 1; j >= 0; j--)
                {
                    if (collision(rectMob[j].first, vProjectile[i].getHitBox()) && vMob[j].getObjectId() != vProjectile[i].getObjectId())
                    {
                        vMob[j].setObjectId(vProjectile[i].getObjectId(), 1);
                        rectMob[j].second = max(0, rectMob[j].second - vProjectile[i].getDmg());
                        vMob[j].setHp(rectMob[j].second);
                    }
                }
            if (current_level == numLevel)
            {
                if (collision(vProjectile[i].getHitBox(), boss.getBossHitbox()) && boss.vulnerable())
                {
                    int lastHp = boss.getHp();
                    boss.takeDamage(vProjectile[i].getDmg());
                    if (lastHp > 0)
                        Audio_Player.boss_hurt();
                }
            }
        }

    }
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
    if (currentState == STATE::PLAY) {

        if (character[current_character]->getX() >= SCREEN_WIDTH / 2)
            view = character[current_character]->getX() - (SCREEN_WIDTH / 2);
        else view = 0;

        if (current_level == numLevel) view = 0;

        map->render(renderer, view, vMob.empty(), current_level == numLevel);

        for (int i = 0; i < vItem.size(); i++) {
            SDL_Rect nRect = vItem[i].getRect();
            nRect.x -= view;
            SDL_RenderCopy(renderer, itemDrop[vItem[i].getId()], NULL, &nRect);
        }

        for (int i = 0; i < vMob.size(); i++) {
            vMob[i].show(renderer, view);

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

        int level_end = 0;
        if (character[current_character]->getStatus() == Character_STATUS::DIED) level_end = 1;
        else if (character[current_character]->getStatus() == Character_STATUS::VICTORY) level_end = 2;
        scr->ingame(renderer, character[current_character]->getHp(), character[current_character]->getDmg(), numCoin, numGem, paused, level_end);

        character[current_character]->show(renderer, view);

        if (current_level == numLevel)
            boss.show(renderer, &Audio_Player);

        {

            SDL_Rect rect = { character[current_character]->getX() - view, character[current_character]->getY() - 20, 42, 7 };

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderFillRect(renderer, &rect);

            int w = character[current_character]->getHp() * 40 / character[current_character]->getMaxHp();

            rect = { character[current_character]->getX() + 1 - view, character[current_character]->getY() - 19, w, 5 };

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

            SDL_RenderFillRect(renderer, &rect);

            rect.x--;
            rect.y += 6;
            rect.h = 7;
            rect.w = 42;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            std::pair<int, int> temp = character[current_character]->getAttackBar();
            temp.first = min(temp.first, temp.second);

            rect.x++;
            rect.y++;
            rect.h = 5;
            rect.w = temp.first * 40 / temp.second;

            SDL_SetRenderDrawColor(renderer, 107, 107, 107, 255);
            if (temp.first == temp.second)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);

        }
        for (int i = 0; i < vProjectile.size(); i++) {

            vProjectile[i].setW(pr_w[vProjectile[i].getId()]);
            vProjectile[i].setH(pr_h[vProjectile[i].getId()]);

            SDL_Rect tRect = vProjectile[i].getRect();
            tRect.x -= view;
            SDL_RenderCopyEx(renderer, pr[vProjectile[i].getId()], NULL, &tRect, vProjectile[i].getAngle(), NULL, SDL_FLIP_NONE);
        }

        for (int i = 0; i < v_SupportItem.size(); i++)
        {
            if (v_SupportItem[i].getType() == 1)
                v_SupportItem[i].show(renderer, view, SupportItem_Animation[v_SupportItem[i].getStatus()]);
            else
                v_SupportItem[i].show(renderer, view, SupportItemTexture);
        }

        if (vExplosion.size())
            for (int i = vExplosion.size() - 1; i >= 0; i--) {
                SDL_Rect tRect = vExplosion[i].rect;
                int r = vExplosion[i].radius;
                tRect.x = (2 * vExplosion[i].rect.x + vExplosion[i].rect.w) / 2 - sqrt(2) / 2 * r - view;
                tRect.y = (2 * vExplosion[i].rect.y + vExplosion[i].rect.h) / 2 - sqrt(2) / 2 * r;
                tRect.w = sqrt(2) * r;
                tRect.h = sqrt(2) * r;
                SDL_RenderCopy(renderer, explosion, NULL, &tRect);
                if (vExplosion[i].frame == 0)
                {
                    std::swap(vExplosion[i], vExplosion.back());
                    vExplosion.pop_back();
                }
            }
    }
    SDL_RenderPresent(renderer);
}