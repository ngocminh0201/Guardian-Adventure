#pragma once
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <SDL_ttf.h>
#include <random>
#include <chrono>
#include <Renderer.h>
#include <Sprite2D.h>
#include <ResourceManagers.h>

typedef std::pair<int, int> pii;
typedef long long ll;

struct Explosion {
	SDL_Rect rect;
	int radius;
	int dmg;
	int frame;
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIDHT = 720;

#define LIMIT_FPS 60
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
const double MAX_FAIL_SPEED = 25;
const double MAX_RUN_SPPED = 15;

const int numCharacter = 6;
const int numItem = 4;
const int charSize = 300;
const int portraitSize = 100;
const int bossSize = 900;
const int numStatus = 11;
const int numBossProjectile = 2;

const int numLevel = 6;

//Projectiles
const int numProjectiles = 8;
const double pi = acos(-1);
