#include "Mob.h"

Mob::Mob() {
    for (int i = 0; i <= 1; i++) {
        idleAnimation[i] = NULL;
        attackAnimation[i] = NULL;
        moveAnimation[i] = NULL;
    }
    laser = NULL;
    melee = { 0, 0, 0, 0 };
    move = attack = idle = false;
    facing = direction = 1;
    frame = 0;
    type = 1;
    maxX = minX = 0;
    nextAttack = 0;
    idProjectile = 0;
    dmg = 0;
    hp = 0;
    mobId = 0;
    hostile = true;
    weapon = 0;
    frameAttack = 0;
    framePerAttack = 0;
    laser = NULL;
    prRadius = 0;
    prSpeed = 0;

    _idle = { 0, 0 };
    _move = { 0, 0 };
    _attack = { 0, 0 };

    for (int i = 0; i < 3; i++)
        itemDrop[i] = 0;

    inFollowRange = false;
    laserTick = 0;
}

Mob::~Mob() {
    Free();
    for (int i = 0; i <= 1; i++) {
        SDL_DestroyTexture(idleAnimation[i]);
        SDL_DestroyTexture(moveAnimation[i]);
        SDL_DestroyTexture(attackAnimation[i]);
    }
    SDL_DestroyTexture(laser);
    for (int i = 0; i <= 1; i++) {
        idleAnimation[i] = NULL;
        attackAnimation[i] = NULL;
        moveAnimation[i] = NULL;
    }
    laser = NULL;
}

bool Mob::loadMob(std::string path, SDL_Renderer* renderer) {
    bool success = true;

    for (int i = 0; i <= 1; i++) {

        std::string st = int2str(i) + ".png";

        // idle
        success = loadImage(path + "/idle" + st, renderer);
        if (success == true) {
            idleAnimation[i] = getObject();
            idle = true;
        }

        // move
        success = loadImage(path + "/move" + st, renderer);
        if (success == true) {
            moveAnimation[i] = getObject();
            move = true;
        }

        // attack
        success = loadImage(path + "/attack" + st, renderer);
        if (success == true) {
            attackAnimation[i] = getObject();
            attack = true;
        }
    }

    std::ifstream file(path + "/mob_info.txt");

    if (!file.is_open())
        return false;

    file >> _idle.first >> _idle.second;
    file >> _move.first >> _move.second;
    file >> _attack.first >> _attack.second;
    file >> framePerAttack;
    file >> idProjectile;
    file >> rect.w >> rect.h;
    file >> hp >> dmg;
    maxHp = hp;
    file >> type;   
    file >> velX;
    if (type == TYPE::MELEE) {
        file >> melee.x >> melee.y >> melee.w >> melee.h;
        file >> frameAttack;
    }
    else if (type == TYPE::THROW || type == TYPE::RANGED) {
        file >> prSpeed;
        if (type == TYPE::THROW) file >> prRadius;
    }
    else if (type == TYPE::FOLLOW)
    {
        file >> velY;
    }
    else if (type == TYPE::BOMB)
    {
        file >> prRadius;
    }
    file >> itemDrop[0] >> itemDrop[1];
    if (type == TYPE::LASER)
    {
        SDL_Surface* loadedSurface = IMG_Load((path + "/laser.png").c_str());
        laser = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface); loadedSurface = NULL;
    }
    file.close();

    return true;
}

void Mob::drawIdle(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = { 0, 0, charSize, charSize };
    SDL_Rect tRect = { rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h), charSize, charSize };

    nRect.x = (frame % _idle.first) * charSize;
    nRect.y = (frame / _idle.first) * charSize;

    SDL_RenderCopy(renderer, idleAnimation[facing], &nRect, &tRect);

    frame++;
    if (frame >= _idle.second) frame %= _idle.second;
}

void Mob::drawMove(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = { 0, 0, charSize, charSize };
    SDL_Rect tRect = { rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h), charSize, charSize };

    nRect.x = (frame % _move.first) * charSize;
    nRect.y = (frame / _move.first) * charSize;
    SDL_RenderCopy(renderer, moveAnimation[facing], &nRect, &tRect);
    frame++;
    if (frame >= _move.second) frame %= _move.second;
}

void Mob::drawAttack(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = { 0, 0, charSize, charSize };
    SDL_Rect tRect = { rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h), charSize, charSize };

    nRect.x = (frame % _attack.first) * charSize;
    nRect.y = (frame / _attack.first) * charSize;
    SDL_RenderCopy(renderer, attackAnimation[facing], &nRect, &tRect);
    frame++;
}

void Mob::show(SDL_Renderer* renderer, int view)
{
    if (type != TYPE::FOLLOW && type != TYPE::LASER)
    {
        if (nextAttack >= _attack.second)
        {
            if (nextAttack == _attack.second) frame = 0;
            if (idle) drawIdle(renderer, view);
            else drawMove(renderer, view);
        }
        else
        {
            drawAttack(renderer, view);
        }

        nextAttack++;
        if (nextAttack == framePerAttack)
        {
            nextAttack -= framePerAttack;
            frame = 0;
        }
    }
    else if (type == FOLLOW)
    {
        nextAttack++;
        if (nextAttack >= framePerAttack)
            nextAttack = 0;
        if (inFollowRange)
        {
            if (frame >= _attack.second)
                frame -= _attack.second;
            drawAttack(renderer, view);
        }
        else
            drawIdle(renderer, view);

    }
    else
    {
        if (nextAttack >= framePerAttack)
        {
            laserTick = 0;
            nextAttack = 0;
        }
        if (laserTick < 90)
        {
            if (frame >= _attack.second)
                frame %= _attack.second;
            drawAttack(renderer, view);
            SDL_Rect range = { rect.x - view + rect.w / 2, rect.y, SCREEN_WIDTH, 70 };
            if (!facing) range.x -= SCREEN_WIDTH;
            SDL_RenderCopy(renderer, laser, NULL, &range);
        }
        else
        {
            drawIdle(renderer, view);
        }
        nextAttack++;
        laserTick++;
    }
    
}

void Mob::update(GameMap* MAP, std::vector<Projectile>& vProjectile, Character* character, std::vector<Explosion>& vExplosion, Sound* audio)
{
    if (type != TYPE::FOLLOW && type != TYPE::LASER)
    {
        if (move)
        {
            if (direction) rect.x -= velX;
            else rect.x += velX;
            
        }
        if (type == TYPE::RANGED || type == TYPE::THROW)
        {
            if (rect.x >= character->getX()) facing = 1;
            else facing = 0;
        }
        else
        {
            facing = direction;
        }

        if (move) {
            if (rect.x > maxX - rect.w)
            {
                rect.x = maxX - rect.w;
                direction = 1;
            }
            else if (rect.x < minX)
            {
                rect.x = minX;
                direction = 0;
            }
        }

        collisionX(MAP);

        rect.y += MAX_FALL_SPEED;
        collisionY(MAP);
    }
    

    if (nextAttack == 0 && type == TYPE::RANGED && abs(rect.x - character->getX()) <= SCREEN_WIDTH / 2)
    {
        Projectile temp;
        temp.shoot(character->getRect(), rect, idProjectile, dmg, prSpeed);
        temp.setHostile(true);
        vProjectile.push_back(temp);
    }

    if (nextAttack == 0 && type == TYPE::THROW && abs(rect.x - character->getX()) <= SCREEN_WIDTH / 2)
    {
        Projectile temp;
        temp.setThrew(true);
        temp.setRadius(prRadius);
        temp.shoot(character->getRect(), rect, idProjectile, dmg, prSpeed);
        temp.setHostile(true);
        vProjectile.push_back(temp);
    }

    if (nextAttack == frameAttack && type == TYPE::MELEE) {

        SDL_Rect tempRect = rect;
        tempRect.x += melee.x;
        tempRect.y += melee.y;
        tempRect.w = melee.w;
        tempRect.h = melee.h;

        if (facing) tempRect.x -= 2 * melee.x + melee.w - rect.w;

        if (collision(tempRect, character->getRect())) {
            int lastHp = character->getHp();
            character->takeDamage(dmg);
            if (lastHp > 0) {
                audio->stopSfx();
                audio->character_hurt();
            }
            int chance = Rand(1, 2);
            if (chance == 1 && character->getId() == 2)
                hp = max(0, hp - dmg);
        }
    }

    if (nextAttack == _attack.second - 1 && type == TYPE::BOMB && abs(rect.x - character->getX()) <= SCREEN_WIDTH / 2)
    {
        vExplosion.push_back({ rect, prRadius, dmg, 15 });
        audio->bomb_explosion();
    }

    if (type == TYPE::FOLLOW)
    {
        if (abs(rect.x - character->getX()) <= SCREEN_WIDTH / 2)
        {
            if (rect.x > character->getX()) rect.x -= velX;
            else if (rect.x < character->getX()) rect.x += velX;

            if (rect.y > character->getY()) rect.y -= velY;
            else if (rect.y < character->getY()) rect.y += velY;

            inFollowRange = true;
        }
        else inFollowRange = false;
        if (collision(character->getRect(), rect) && nextAttack == 0) {
            int lastHp = character->getHp();
            character->takeDamage(dmg);
            if (lastHp > 0) {
                audio->stopSfx();
                audio->character_hurt();
            }
        }
            
    }

    if (type == TYPE::LASER)
    {
        SDL_Rect range = { rect.x + rect.w / 2, rect.y + 20, SCREEN_WIDTH, 100 };
        if (!facing) range.x -= SCREEN_WIDTH;
        if (laserTick % 20 == 0 && laserTick < 90 && collision(character->getRect(), range)) {
            int lastHp = character->getHp();
            character->takeDamage(dmg);
            if (lastHp > 0) {
                audio->stopSfx();
                audio->character_hurt();
            }
        }
            
    }

}

void Mob::collisionX(GameMap* MAP)
{
    int pos_x1 = (rect.x - 1) / TILE_SIZE;
    int pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    int pos_y1 = rect.y / TILE_SIZE;
    int pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    for (int i = pos_y1; i <= pos_y2; i++)
        if (MAP->getInfo()[i][pos_x1])
        {
            rect.x = (pos_x1 + 1) * TILE_SIZE;
            break;
        }

    pos_x1 = rect.x / TILE_SIZE;
    pos_x2 = (rect.x + rect.w + 1) / TILE_SIZE;
    pos_y1 = rect.y / TILE_SIZE;
    pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    for (int i = pos_y1; i <= pos_y2; i++)
        if (MAP->getInfo()[i][pos_x2])
        {
            rect.x = pos_x2 * TILE_SIZE - rect.w - 1;
            break;
        }

}

void Mob::collisionY(GameMap* MAP)
{
    bool ok = 1;
    int pos_x1 = rect.x / TILE_SIZE;
    int pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    int pos_y1 = (rect.y - 1) / TILE_SIZE;
    int pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    for (int i = pos_x1; i <= pos_x2; i++)
        if (MAP->getInfo()[pos_y1][i])
        {
            rect.y = (pos_y1 + 1) * TILE_SIZE;
            break;
        }

    pos_x1 = rect.x / TILE_SIZE;
    pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    pos_y1 = rect.y / TILE_SIZE;
    pos_y2 = (rect.y + rect.h + 1) / TILE_SIZE;

    for (int i = pos_x1; i <= pos_x2; i++)
        if (MAP->getInfo()[pos_y2][i])
        {
            ok = 0;
            rect.y = pos_y2 * TILE_SIZE - rect.h - 1;
            break;
        }
}

void Mob::spawnItem(std::vector<Item>& vItem) const
{
    for (int id = 0; id < 3; id++)
        for (int i = 0; i < min(itemDrop[id], 10); i++) {
            Item nItem;
            nItem.setX((rect.x * 2 + rect.w) / 2);
            nItem.setY((rect.y * 2 + rect.h) / 2);
            nItem.setVelY(-30);
            nItem.setVelX(Rand(-10, 10));
            nItem.setW(30);
            nItem.setH(30);
            nItem.setId(id);
            int val = itemDrop[id] / 10;
            if (i < itemDrop[id] % 10) val++;
            nItem.setVal(val);
            vItem.push_back(nItem);
        }
}