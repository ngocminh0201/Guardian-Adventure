#include "Character.h"

Character::Character()
{
    frame = 0;
    status = nStatus = 0;
    id = 0;
    isFalling = true;
    isJumping = false;
    finishAttack = true;
    nextAttack = 0;
    facing = 0;
    type = 1;

    _idle = { 0, 0 };
    _move = { 0, 0 };
    _attack = { 0, 0 };
    _died = { 0, 0 };
    _victory = { 0, 0 };

    
    velX = MAX_RUN_SPEED;
}

Character::~Character()
{
    _idle = { 0, 0 };
    _move = { 0, 0 };
    _attack = { 0, 0 };
    _died = { 0, 0 };
    _victory = { 0, 0 };

    frame = 0;
}

bool Character::loadCharacter(std::string path, SDL_Renderer* renderer, int _id)
{

    for (int i = 1; i >= 0; i--) {
        std::string s = int2str(i) + ".png";
        // idle
        auto texture = ResourceManagers::GetInstance()->GetTexture(path + "/idle" + s);
        animation = std::make_shared<SpriteAnimation>(texture, 1, 5, 4, 0.2f);
        animation->SetFlip(SDL_FLIP_HORIZONTAL);
        animation->SetSize(charSize, charSize);

        idleAnimation.push_back(animation);

        // jump
        texture = ResourceManagers::GetInstance()->GetTexture(path + "/jump" + s);
        animation = std::make_shared<SpriteAnimation>(texture, 1, 1, 1, 0.2f);
        animation->SetFlip(SDL_FLIP_HORIZONTAL);
        animation->SetSize(charSize, charSize);
        jumpAnimation.push_back(animation);

        // move
        texture = ResourceManagers::GetInstance()->GetTexture(path + "/move" + s);
        animation = std::make_shared<SpriteAnimation>(texture, 1, 3, 4, 0.2f);
        animation->SetFlip(SDL_FLIP_HORIZONTAL);
        animation->SetSize(charSize, charSize);
        moveAnimation.push_back(animation);
        
        // died
        texture = ResourceManagers::GetInstance()->GetTexture(path + "/died" + s);
        animation = std::make_shared<SpriteAnimation>(texture, 1, 8, 9, 0.2f);
        animation->SetFlip(SDL_FLIP_HORIZONTAL);
        animation->SetSize(charSize, charSize);
        diedAnimation.push_back(animation);
        
        // attack
        texture = ResourceManagers::GetInstance()->GetTexture(path + "/attack" + s);
        animation = std::make_shared<SpriteAnimation>(texture, 1, 4, 3, 0.2f);
        animation->SetFlip(SDL_FLIP_HORIZONTAL);
        animation->SetSize(charSize, charSize);
        attackAnimation.push_back(animation);
    }

    // victory
    auto texture = ResourceManagers::GetInstance()->GetTexture(path + "/victory.png");
    victoryAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 4, 0.2f);
    victoryAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
    victoryAnimation->SetSize(charSize, charSize);
    
    

    /*loadedSurface = IMG_Load((path + "/portrait.png").c_str());

    if (loadedSurface == NULL) return 0;

    portrait = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);*/

    id = _id;

    {
        std::ifstream file("Data/Textures/Character/0/char_info.txt");
        file >> rect.w >> rect.h;
        file >> type;
        file >> _idle.first >> _idle.second;
        file >> _move.first >> _move.second;
        file >> _attack.first >> _attack.second;
        file >> _died.first >> _died.second;
        file >> _victory.first >> _victory.second;
        file >> framePerAttack;
        file >> baseHp >> baseDmg;
        maxHp = baseHp;
        if (type == TYPE::MELEE) {
            file >> melee.x >> melee.y >> melee.w >> melee.h;
            file >> frameAttack;
        }
        else {
            file >> idProjectile >> prSpeed >> prLastTime;
        }
        file.close();
    }
    
    return 1;
}

void Character::drawIdle(SDL_Renderer* renderer, int view)
{
    if (nStatus != status) {
        
    }
    status = STATUS::IDLE;
    idleAnimation[facing]->Set2DPosition(rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h));
    idleAnimation[facing]->Draw(renderer);
}

void Character::drawMove(SDL_Renderer* renderer, int view)
{
    if (nStatus != status) {

    }

    status = STATUS::MOVE;
    moveAnimation[facing]->Set2DPosition(rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h));
    moveAnimation[facing]->Draw(renderer);
}

void Character::drawDied(SDL_Renderer* renderer, int view)
{

    if (nStatus != status) {

    }
    status = STATUS::DIED;
    diedAnimation[facing]->Set2DPosition(rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h));
    diedAnimation[facing]->Draw(renderer);
}

void Character::drawVictory(SDL_Renderer* renderer, int view)
{
    if (nStatus != status) {

    }


    status = STATUS::VICTORY;
    victoryAnimation->Set2DPosition(rect.x - charSize / 3 - view, rect.y - charSize / 3 - (charSize / 3 - rect.h));
    victoryAnimation->Draw(renderer);
}

void Character::drawAttack(SDL_Renderer* renderer, int view)
{
    if (nStatus != status && finishAttack) {
        //attackAnimation[facing]->m_currentFrame = 0;
        //attackAnimation[facing]->m_spriteRow = 1;
        //printf("kkk\n");
    }

    if (attackAnimation[facing]->m_currentFrame + 1 == attackAnimation[facing]->m_frameCount && 
        attackAnimation[facing]->m_spriteRow + 1 == attackAnimation[facing]->m_numAction)
    {
        finishAttack = true;
    }
    status = STATUS::ATTACK;
    attackAnimation[facing]->Set2DPosition(rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h));
    attackAnimation[facing]->Draw(renderer);
}

void Character::show(SDL_Renderer* renderer, int view)
{

    //SDL_Rect pRect = { 10, 10, portraitSize, portraitSize };

    //SDL_RenderCopy(renderer, portrait, NULL, &pRect);

    //if (nStatus != status && (finishAttack || nextAttack == 0)) frame = 0;

    if (nStatus == STATUS::DIED)
    {
        drawDied(renderer, view);
        return;
    }
    if (nStatus == STATUS::VICTORY)
    {
        drawVictory(renderer, view);
        return;
    }

    nextAttack++;

    if (nStatus == STATUS::ATTACK)
    {
        drawAttack(renderer, view);
    }
    else if (isJumping || isFalling)
    {
        jumpAnimation[facing]->Set2DPosition(rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing, rect.y - charSize / 3 - (charSize / 3 - rect.h));
        jumpAnimation[facing]->Draw(renderer);
        status = STATUS::JUMP;
        return;
    }
    else if (nStatus == STATUS::IDLE) drawIdle(renderer, view);
    else if (nStatus == STATUS::MOVE) drawMove(renderer, view);
}

void Character::handleInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        {
            pressed['a'] = 1;
            pressed['d'] = 0;
        }
        break;
        case SDLK_d:
        {
            pressed['a'] = 0;
            pressed['d'] = 1;
        }
        break;
        case SDLK_SPACE:
        {
            if (isFalling == false) {
                pressed[' '] = 1;
            }
        }
        break;
        case SDLK_k:
        {
            //pressed['k'] = 1;
            if (nextAttack >= framePerAttack) {
                pressed['k'] = 1;
            }
        }
        break;
        }
    }

    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        {
            pressed['a'] = 0;
        }
        break;
        case SDLK_d:
        {
            pressed['d'] = 0;
        }
        break;
        case SDLK_SPACE:
        {
            pressed[' '] = 0;
        }
        case SDLK_k:
        {
            pressed['k'] = 0;
        }
        break;
        }


    }
}

void Character::Update(GameMap* MAP, float deltaTime)
{
    for (int i = 0; i <= 1; i++) {
        idleAnimation[i]->Update(deltaTime);
        moveAnimation[i]->Update(deltaTime);
        attackAnimation[i]->Update(deltaTime);
        diedAnimation[i]->Update(deltaTime);
        jumpAnimation[i]->Update(deltaTime);
    }
    
    if (isJumping || isFalling) {
        velY += gravity;
        
        if (velY > MAX_FALL_SPEED)
            velY = MAX_FALL_SPEED;
        //printf("%f\n", velY);
    }
    
    rect.y += velY;
    printf("%f %d\n", velY, rect.y);

    if (rect.y < 0) rect.y = 0;

    if (rect.y + rect.h >= MAP->getMapHeight() * TILE_SIZE - 2) rect.y = MAP->getMapHeight() * TILE_SIZE - rect.h - 2;

    collisionY(MAP);

    if (rect.y + rect.h >= MAP->getMapHeight() * TILE_SIZE - 2 || hp == 0)
    {
        nStatus = STATUS::DIED;
        return;
    }

    if (rect.x >= MAP->getVictory() || nStatus == STATUS::VICTORY)
    {
        nStatus = STATUS::VICTORY;
        return;
    }

    if (!isFalling && !pressed['a'] && !pressed['d'] && (!pressed['k'] || (pressed['k'] && nextAttack < framePerAttack))) {
        nStatus = STATUS::IDLE;
    }
        
    if (pressed[' '] && isFalling == false)
    {
        isJumping = isFalling = true;
        nStatus = STATUS::JUMP;
        velY = -40;
    }
    else if (isFalling == true)
    {
        nStatus = STATUS::JUMP;
    }

    if (pressed['a'])
    {
        facing = 1;
        nStatus = STATUS::MOVE;
        rect.x -= velX;
        //rect.x--;
    }
    else if (pressed['d'])
    {
        facing = 0;
        nStatus = STATUS::MOVE;
        rect.x += velX;
        //rect.x++;
    }
    pressed[' '] = false;

    if (rect.x < 0) rect.x = 0;
    if (rect.x > MAP->getMapWidth() * TILE_SIZE - rect.w) rect.x = MAP->getMapWidth() * TILE_SIZE - rect.w;

    collisionX(MAP);
    if (pressed['k'] && nextAttack >= framePerAttack)
    {
        nStatus = STATUS::ATTACK;
        
        finishAttack = false;
        nextAttack = 0;
    }
    else if (!finishAttack) {
        nStatus = STATUS::ATTACK;
    }
        

    /*if (!finishAttack && frame == frameAttack && type == TYPE::MELEE) {

        SDL_Rect tempRect = rect;
        tempRect.x += melee.x;
        tempRect.y += melee.y;
        tempRect.w = melee.w;
        tempRect.h = melee.h;

        if (facing) tempRect.x -= 2 * melee.x + melee.w - rect.w;

    }*/

    
}

void Character::collisionX(GameMap* MAP)
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

void Character::collisionY(GameMap* MAP)
{
    bool ok = 1;
    int pos_x1 = rect.x / TILE_SIZE;
    int pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    int pos_y1 = (rect.y - 1) / TILE_SIZE;
    int pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    for (int i = pos_x1; i <= pos_x2; i++)
        if (MAP->getInfo()[pos_y1][i])
        {
            velY = 0;
            rect.y = (pos_y1 + 1) * TILE_SIZE;
            isJumping = false;
            isFalling = true;
            nStatus = STATUS::JUMP;
            break;
        }

    pos_x1 = rect.x / TILE_SIZE;
    pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    pos_y1 = rect.y / TILE_SIZE;
    pos_y2 = (rect.y + rect.h + 1) / TILE_SIZE;

    for (int i = pos_x1; i <= pos_x2; i++)
        if (MAP->getInfo()[pos_y2][i])
        {
            velY = 0;
            ok = 0;
            rect.y = pos_y2 * TILE_SIZE - rect.h - 1;
            isJumping = isFalling = false;
            break;
        }

    if (ok) isFalling = true;

}
std::pair<int, int> Character::getAttackBar()
{
    return { nextAttack, framePerAttack };
}

void Character::setStatus(int _status)
{
    nStatus = _status;
}

int Character::getStatus()
{
    return nStatus;
}

bool Character::getAttack()
{
    return finishAttack;
}

SDL_Rect Character::getMelee()
{
    SDL_Rect tempRect = rect;
    tempRect.x += melee.x;
    tempRect.y += melee.y;
    tempRect.w = melee.w;
    tempRect.h = melee.h;

    if (facing) tempRect.x -= 2 * melee.x + melee.w - rect.w;
    return tempRect;
}
