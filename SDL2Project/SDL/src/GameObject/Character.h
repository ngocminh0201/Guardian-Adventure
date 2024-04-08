#pragma once
/*#include "Define.h"
#include "GameMap.h"
#include "GameObject.h"

class Character : public GameObject {
public:
	Character();
	~Character();
	void show(int view);
	void handleInput(SDL_Event event);
	void loadCharacter(std::string path, int _id, int view);

	void collisionX(GameMap* MAP);
	void collisionY(GameMap* MAP);
	void Update(float deltatime);
	void drawIdle(int view);

	void drawMove(int view);

	void tick(GameMap* MAP);

	void setStatus(int nStatus) { this->nStatus = nStatus; }
	int getStatus() { return nStatus; }
	void setFrame(int frame) { this->frame = frame; }
protected:
	SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();

	std::shared_ptr<SpriteAnimation> animation;
	std::vector<std::shared_ptr<SpriteAnimation>> idleAnimation;
	std::vector<std::shared_ptr<SpriteAnimation>> moveAnimation;
	//SDL_Texture* idleAnimation[2];
	pii _idle, _move;

	int id;
	int frame;
	bool isJumping;
	bool isFalling;
	int status;
	int nStatus;

	enum STATUS {
		IDLE = 0,
		MOVE = 1,
		JUMP = 2,
		ATTACK = 3,
		DIED = 4,
		VICTORY = 5,
	};
	bool facing;
	bool pressed[300] = { false };
};*/

#include "GameObject.h"
#include "Define.h"
#include "GameMap.h"

class Character : public GameObject
{
public:
    Character();
    ~Character();
    void show(SDL_Renderer* renderer, int view);
    void handleInput(SDL_Event event);
    bool loadCharacter(std::string path, SDL_Renderer* renderer, int _id);
    void Update(GameMap* MAP, float deltaTime);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void drawIdle(SDL_Renderer* renderer, int view);
    void drawMove(SDL_Renderer* renderer, int view);
    void drawAttack(SDL_Renderer* renderer, int view);
    void drawDied(SDL_Renderer* renderer, int view);
    void drawVictory(SDL_Renderer* renderer, int view);
    void setStatus(int _status);
    void setFrame(int _frame) { frame = _frame; }
    int getStatus();
    bool getAttack();
    int getId() { return id; }
    std::pair<int, int> getAttackBar();
    bool startAttack() { return nextAttack == 0; }
    bool getMove() { return (pressed['a'] || pressed['d']); }
    bool onGround() { return (!isFalling); }
    bool jumped() { return pressed[' '] && isFalling == false; }
    SDL_Rect getMelee();
    bool meleeAttack() { return !finishAttack && frame == frameAttack && type == TYPE::MELEE; }

protected:
    //SDL_Texture* moveAnimation[2];
    //SDL_Texture* attackAnimation[2];
    //SDL_Texture* diedAnimation[2];
    //SDL_Texture* victoryAnimation;
    //SDL_Texture* jumpAnimation[2];
    SDL_Texture* portrait;
    SDL_Rect melee;

    std::shared_ptr<SpriteAnimation> animation;
    std::vector<std::shared_ptr<SpriteAnimation>> idleAnimation;
    std::vector<std::shared_ptr<SpriteAnimation>> moveAnimation;
    std::vector<std::shared_ptr<SpriteAnimation>> attackAnimation;
    std::vector<std::shared_ptr<SpriteAnimation>> diedAnimation;
    std::vector<std::shared_ptr<SpriteAnimation>> jumpAnimation;
    std::shared_ptr<SpriteAnimation> victoryAnimation;

    std::pair<int, int> _idle;
    std::pair<int, int> _move;
    std::pair<int, int> _attack;
    std::pair<int, int> _died;
    std::pair<int, int> _victory;

    int id;
    int frame;
    bool isJumping;
    bool isFalling;
    int status;
    int nStatus;
    /** Notes:
    0. idle
    1. move
    2. jump
    3. attack
    4. died
    5. victory
    **/
    enum STATUS {
        IDLE = 0,
        MOVE = 1,
        JUMP = 2,
        ATTACK = 3,
        DIED = 4,
        VICTORY = 5,
    };

    bool leftP = false, rightP = false;
    bool pressed[300] = { false };
    bool finishAttack;
    int nextAttack, framePerAttack, frameAttack;
    bool facing;
    int type;
    int idProjectile, prSpeed, prLastTime;

    enum TYPE {
        RANGED = 0,
        MELEE = 1,
    };
};