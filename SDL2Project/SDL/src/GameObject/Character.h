#pragma once
#include "GameObject.h"
#include "Define.h"
#include "GameMap.h"

class Character : public GameObject
{
public:
    Character();
    ~Character();
    void show(int view);
    void handleInput(SDL_Event event);
    bool loadCharacter(std::string path, int _id);
    void Update(GameMap* MAP);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void drawIdle(int view);
    void drawMove(int view);
    void drawAttack(int view);
    void drawDied(int view);
    void drawVictory(int view);
    void setStatus(int status);
    void setFrame(int frame) { this->frame = frame; }
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
    SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();

    SDL_Texture* portrait;
    SDL_Texture* idleAnimation[2];
    SDL_Texture* moveAnimation[2];
    SDL_Texture* attackAnimation[2];
    SDL_Texture* diedAnimation[2];
    SDL_Texture* victoryAnimation;
    SDL_Texture* jumpAnimation[2];

    SDL_Rect melee;

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