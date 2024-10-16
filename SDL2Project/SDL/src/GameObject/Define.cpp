#include "Define.h"

std::string int2str(int num) {
	if (num == 0) return "0";
	std::string res;
	while (num > 0) {
		res = char(num % 10 + 48) + res;
		num /= 10;
	}
	return res;
}

bool operator == (SDL_Color a, SDL_Color b) {
	return a.r == b.r && a.g == b.g && a.b == b.b;
}

bool collision(SDL_Rect A, SDL_Rect B) {
	return !(A.x > B.x + B.w || A.x + A.w < B.x || A.y > B.y + B.h || A.y + A.h < B.y);
}

bool inRect(int x, int y, SDL_Rect rect) {
	return (rect.x <= x && x < rect.w + rect.x && rect.y <= y && y < rect.y + rect.h);
}

double distance(SDL_Rect A, SDL_Rect B) {
	double x = (2 * A.x + A.w - 2 * B.x - B.w) / 2;
	double y = (2 * A.y + A.h - 2 * B.y - B.h) / 2;

	return sqrt(x * x + y * y);
}

std::mt19937_64 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
ll Rand(ll L, ll R) {
	return std::uniform_int_distribution<long long>(L, R) (rng);
}

ll getCost(int level) {
	return 1LL * level * (level + 1) / 2;
}