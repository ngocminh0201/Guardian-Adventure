#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Sprite2D.h"

typedef std::pair<int, int> pii;
typedef long long ll;

struct Explosion {
	SDL_Rect rect;
	int radius;
	int dmg;
	int frame;
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const std::string SCREEN_NAME = "Guardian Adventure";

#define LIMIT_FPS 33
#define min(a, b) ((a) < (b) ? a : b)
#define max(a, b) ((a) > (b) ? a : b)

// function
std::string int2str(int num);
bool operator == (SDL_Color a, SDL_Color b);
bool collision(SDL_Rect A, SDL_Rect B);
bool inRect(int x, int y, SDL_Rect rect);
double distance(SDL_Rect A, SDL_Rect B);
ll Rand(ll L, ll R);
ll getCost(int level);

// Map
const int TILE_SIZE = 36;

const SDL_Color red = { 255, 0, 0, 255 };
const SDL_Color blue = { 0, 0, 255, 255 };
const SDL_Color green = { 0, 255, 0, 255 };
const SDL_Color black = { 0, 0, 0, 255 };
const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color yellow = { 255, 255, 0, 255 };
const SDL_Color pink = { 255, 0, 255, 255 };
const SDL_Color cyan = { 0, 255, 255, 255 };
const SDL_Color textColor = { 245, 220, 189, 255 };
const SDL_Color backColor = { 45, 38, 32, 255 };

// Character and Mob
const double gravity = 3;
const double MAX_FALL_SPEED = 25;
const double MAX_RUN_SPEED = 15;
enum Character_STATUS {
	IDLE = 0,
	MOVE = 1,
	JUMP = 2,
	ATTACK = 3,
	DIED = 4,
	VICTORY = 5,
};

const int numCharacter = 6;
const int numItem = 4;
const int charSize = 300;
const int portraitSize = 100;
const int bossSize = 900;
const int numStatus = 11;
const int numBossProjectile = 2;

const int numLevel = 6;

// Boss
const int hpBoss = 10000;
const int dmg_attack1 = 200;
const int dmg_attack2 = 200;
const int dmg_attack3 = 200;
const int dmg_attack4 = 200;

//Projectiles
const int numProjectile = 8;
const double pi = acos(-1);

// STATE
enum STATE {
	NONE,
	MENU,
	SELECT,
	PLAY,
	CREDIT,
	SETTING,
	HELP
};