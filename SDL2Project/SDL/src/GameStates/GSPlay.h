#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "GameMap.h"
#include "Character.h"
#include "Mob.h"
#include "GSSelect.h"
#include "BossLevel.h"
#include "Item.h"
#include "SupportItem.h"
class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;
	

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;
	
	int getCurrentState() const { return this->currentState; }
	bool loadLevel(int level, SDL_Renderer* renderer);
	void load(SDL_Renderer* renderer);
	void character1();
private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;
	int x = 240;
	int y = 400;
	int view;
	GameMap* map;
	std::vector<Mob> vMob;
	std::shared_ptr<Sprite2D> m_map;
	std::list<std::shared_ptr<Sprite2D>> m_listMap;
	int currentState, current_level, current_character;
	bool currentMusic, currentSFX;
	Character* character[numCharacter];
	std::vector<Projectile> vProjectile;
	std::vector<Explosion> vExplosion;
	std::vector<Item> vItem, vItem_temp;
	std::vector<SupportItem> v_SupportItem;
	std::vector<std::pair<SDL_Rect, int> > rectMob;
	SDL_Texture* explosion;
	int pr_w[numProjectile];
	int pr_h[numProjectile];
	SDL_Texture* pr[numProjectile];
	SDL_Texture* itemDrop[numItem];
	SDL_Texture* SupportItemTexture;
	SDL_Texture* SupportItem_Animation[3];
	Sound Audio_Player;
	SDL_Event event;
	GSSelect* scr;
	int* character_level;
	int numGem, numCoin;
	int lastLevel;
	bool paused;
	int frame_back;
	int frame_char3;
	int id;
	int prev, prev_map, prev_char;
	int* prev_char_level;
	int** char_growth;
	BossLevel boss;

	float  m_currentTicks;
	Uint32 m_lastUpdate;
};

