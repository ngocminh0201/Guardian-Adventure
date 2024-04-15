#pragma once
#include "Define.h"
#include "GameMap.h"
#include "GameObject.h"

class Projectile : public GameObject {
public:
    Projectile();
    ~Projectile();
    void tick(GameMap* MAP);
    void shoot(SDL_Rect character, SDL_Rect mob, int _id, int _dmg, int _speed);
    void setSpeed(double _speed) { speed = _speed; }
    bool done();
    double getAngle();
    int getId();
    SDL_Rect getHitBox(int view);
    SDL_Rect getHitBox();
    void setHostile(bool _h) { hostile = _h; }
    bool getHostile() { return hostile; }

    void setRadius(int _radius) { radius = _radius; }
    int getRadius() { return radius; }

    void setThrew(bool _threw) { threw = _threw; }
    bool getThrew() { return threw; }

    void setLastTime(int _lastTime) { lastTime = _lastTime; }


protected:
    double angle;
    double speed;
    bool threw;
    int curTime;
    int lastTime;
    int id;
    bool hostile;
    int radius;
};