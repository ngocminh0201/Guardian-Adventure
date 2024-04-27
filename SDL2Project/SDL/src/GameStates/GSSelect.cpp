#include "GSSelect.h"
#include "fstream"

GSSelect::GSSelect() {
	level_background = NULL;
	character_texture = NULL;
	gem = NULL;
	coin = NULL;
	lock = NULL;
	star = NULL;
	nostar = NULL;
	statArrow = NULL;
	for (int i = 0; i < numCharacter; i++)
		portrait[i] = NULL;
	for (int i = 0; i < 2; i++)
		rectBar[i] = { 0, 0, 0, 0 };
	curAlpha = 0;
	change_level = true;
	change_character = true;
	arrow_flag = true;
	selected_flag = true;
	flag = false;
	font = NULL;
	textFont = NULL;
	textFontBig = NULL;
	textFontSmall = NULL;
	for (int i = 0; i < 3; i++)
		itemCount[i] = 0;
	frame = 0;
	ptSize = 150;
	cost = new long long[numCharacter];
	cost[0] = 20;
	cost[1] = 100;
	cost[2] = 300;
	cost[3] = 500;
	cost[4] = 1000;
	cost[5] = 3000;
	prev = 0;
	cw = 0;
	ch = 0;
}

GSSelect::~GSSelect() {
	for (int i = 0; i < numCharacter; i++)
		SDL_DestroyTexture(portrait[i]);

	SDL_DestroyTexture(level_background);
	SDL_DestroyTexture(character_texture);
	SDL_DestroyTexture(gem);
	SDL_DestroyTexture(coin);
	SDL_DestroyTexture(lock);
	SDL_DestroyTexture(star);
	SDL_DestroyTexture(nostar);
	SDL_DestroyTexture(statArrow);

	Free();
}

void GSSelect::Init() {
	loadTexture(Renderer::GetInstance()->GetRenderer());
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSSelect::Exit() {}
void GSSelect::Pause() {}
void GSSelect::Resume() {}

void GSSelect::HandleEvents()
{
}

void GSSelect::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed

}

void GSSelect::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSSelect::HandleMouseMoveEvents(int x, int y)
{
}

void GSSelect::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	std::cout << "Update\n";

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSSelect::Draw(SDL_Renderer* renderer)
{
	std::cout << "Draw\n";
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//	obj->Draw(renderer);

}

void GSSelect::loadTexture(SDL_Renderer* renderer) {
	std::string path = "Data/Textures/img/";
	std::string fontPath = "Data/Fonts/";

	intro_background.loadImage(path + "intro1.jpg", renderer);
	menu_background.loadImage(path + "background.png", renderer);
	credit_background.loadImage(path + "credit_background.png", renderer);
	Guardian.loadImage(path + "guardian.png", renderer);
	Adventure.loadImage(path + "adventure.png", renderer);
	back_button[0].loadImage(path + "back_0.png", renderer);
	back_button[1].loadImage(path + "back_1.png", renderer);
	start_button[0].loadImage(path + "start_0.png", renderer);
	start_button[1].loadImage(path + "start_1.png", renderer);
	exit_button[0].loadImage(path + "exit_0.png", renderer);
	exit_button[1].loadImage(path + "exit_1.png", renderer);
	credit_button[0].loadImage(path + "credit_0.png", renderer);
	credit_button[1].loadImage(path + "credit_1.png", renderer);
	setting_button[0].loadImage(path + "setting_0.png", renderer);
	setting_button[1].loadImage(path + "setting_1.png", renderer);
	music_button[0].loadImage(path + "music_on.png", renderer);
	music_button[1].loadImage(path + "music_off.png", renderer);
	sfx_button[0].loadImage(path + "sfx_on.png", renderer);
	sfx_button[1].loadImage(path + "sfx_off.png", renderer);
	help_button[0].loadImage(path + "help_0.png", renderer);
	help_button[1].loadImage(path + "help_1.png", renderer);
	hpIcon.loadImage(path + "hpIcon.png", renderer);
	dmgIcon.loadImage(path + "dmgIcon.png", renderer);
	statsRect.loadImage(path + "statsRect.png", renderer);
	option_box.loadImage(path + "optionbox.png", renderer);
	bar.loadImage(path + "bar.png", renderer);
	arrow[0].loadImage(path + "arrow0.png", renderer);
	arrow[1].loadImage(path + "arrow1.png", renderer);
	play_button[0].loadImage(path + "play_0.png", renderer);
	play_button[1].loadImage(path + "play_1.png", renderer);
	itemBox.loadImage(path + "itembox.png", renderer);
	charBox.loadImage(path + "charBox.png", renderer);
	infoBox.loadImage(path + "infoBox.png", renderer);
	costBox.loadImage(path + "costBox.png", renderer);
	selected.loadImage(path + "selected.png", renderer);
	paused_box.loadImage(path + "paused.png", renderer);
	paused_return[0].loadImage(path + "return_0.png", renderer);
	paused_return[1].loadImage(path + "return_1.png", renderer);
	paused_continue[0].loadImage(path + "continue_0.png", renderer);
	paused_continue[1].loadImage(path + "continue_1.png", renderer);
	win.loadImage(path + "win.png", renderer);
	lose.loadImage(path + "lose.png", renderer);

	hpIconStat = hpIcon;
	dmgIconStat = dmgIcon;

	bool success = true;

	for (int i = 0; i < numCharacter; i++)
	{
		success = loadImage("Data/Textures/Character/" + int2str(i) + "/portrait.png", renderer);
		if (success == false) return;
		portrait[i] = getObject();
	}

	success = loadImage(path + "item0.png", renderer);
	if (success == false) return;
	coin = getObject();

	success = loadImage(path + "item1.png", renderer);
	if (success == false) return;
	gem = getObject();

	success = loadImage(path + "lock.png", renderer);
	if (success == false) return;
	lock = getObject();

	success = loadImage(path + "star.png", renderer);
	if (success == false) return;
	star = getObject();

	success = loadImage(path + "nostar.png", renderer);
	if (success == false) return;
	nostar = getObject();

	success = loadImage(path + "statArrow.png", renderer);
	if (success == false) return;
	statArrow = getObject();

	font = TTF_OpenFont((fontPath + "REVUE.ttf").c_str(), 45);

	textFont = TTF_OpenFont((fontPath + "calibrib.ttf").c_str(), 25);

	textFontBig = TTF_OpenFont((fontPath + "calibrib.ttf").c_str(), 35);

	textFontSmall = TTF_OpenFont((fontPath + "calibrib.ttf").c_str(), 20);

	intro_background.setW(SCREEN_WIDTH);
	intro_background.setH(SCREEN_HEIGHT);
	
	menu_background.setW(SCREEN_WIDTH);
	menu_background.setH(SCREEN_HEIGHT);

	credit_background.setX(150);
	credit_background.setY(150);
	credit_background.setW((SCREEN_WIDTH - credit_background.getX() * 2));
	credit_background.setH((SCREEN_HEIGHT - credit_background.getY() * 2));

	back_button[0].setX(SCREEN_WIDTH - back_button[0].getW() - 3);
	back_button[0].setY(3);
	back_button[1].setX(SCREEN_WIDTH - back_button[1].getW());
	back_button[1].setY(0);

	//Guardian.setW(832 - 100);
	Guardian.setH(Guardian.getW() * 131 / 1040);
	Guardian.setX((SCREEN_WIDTH - Guardian.getW()) / 2);
	Guardian.setY(-200);

	//Adventure.setW(998 - 100);
	Adventure.setH(Adventure.getW() * 131 / 1248);
	Adventure.setX((SCREEN_WIDTH - Adventure.getW()) / 2);
	Adventure.setY(721);

	Guardian.setVelY(13);
	Adventure.setVelY(-20);

	// start button
	start_button[0].setW(start_button[0].getW() * SCREEN_WIDTH / 1280);
	start_button[0].setH(start_button[0].getH() * SCREEN_HEIGHT / 720);
	start_button[0].setX((SCREEN_WIDTH - 2 * (start_button[0].getW())) / 3);
	start_button[0].setY(150 + Adventure.getH() + (SCREEN_HEIGHT - 150 - Adventure.getH() - 2 * (start_button[0].getH())) / 3);

	start_button[1].setW(start_button[1].getW() * SCREEN_WIDTH / 1280);
	start_button[1].setH(start_button[1].getH() * SCREEN_HEIGHT / 720);
	start_button[1].setX(start_button[0].getX() - 10);
	start_button[1].setY(start_button[0].getY() - 10);

	// setting button
	setting_button[0].setW(setting_button[0].getW() * SCREEN_WIDTH / 1280);
	setting_button[0].setH(setting_button[0].getH() * SCREEN_HEIGHT / 720);
	setting_button[0].setX(start_button[0].getX());
	setting_button[0].setY(start_button[0].getY() + start_button[0].getH() + (SCREEN_HEIGHT - 150 - Adventure.getH() - 2 * (start_button[0].getH())) / 3);

	setting_button[1].setW(setting_button[1].getW() * SCREEN_WIDTH / 1280);
	setting_button[1].setH(setting_button[1].getH() * SCREEN_HEIGHT / 720);
	setting_button[1].setX(setting_button[0].getX() - 9);
	setting_button[1].setY(setting_button[0].getY() - 11);

	// credit button
	credit_button[0].setW(credit_button[0].getW() * SCREEN_WIDTH / 1280);
	credit_button[0].setH(credit_button[0].getH() * SCREEN_HEIGHT / 720);
	credit_button[0].setX(2 * start_button[0].getX() + start_button[0].getW());
	credit_button[0].setY(start_button[0].getY());

	credit_button[1].setW(credit_button[1].getW() * SCREEN_WIDTH / 1280);
	credit_button[1].setH(credit_button[1].getH() * SCREEN_HEIGHT / 720);
	credit_button[1].setX(credit_button[0].getX() - 11);
	credit_button[1].setY(credit_button[0].getY() - 10);

	// exit button
	exit_button[0].setW(exit_button[0].getW() * SCREEN_WIDTH / 1280);
	exit_button[0].setH(exit_button[0].getH() * SCREEN_HEIGHT / 720);
	exit_button[0].setX(credit_button[0].getX());
	exit_button[0].setY(setting_button[0].getY());

	exit_button[1].setW(exit_button[1].getW() * SCREEN_WIDTH / 1280);
	exit_button[1].setH(exit_button[1].getH() * SCREEN_HEIGHT / 720);
	exit_button[1].setX(exit_button[0].getX() - 10);
	exit_button[1].setY(exit_button[0].getY() - 8);

	// help button
	for (int i = 0; i <= 1; i++) {
		help_button[i].setW(80);
		help_button[i].setH(help_button[i].getW());
		help_button[i].setX(0);
		help_button[i].setY(SCREEN_HEIGHT - help_button[i].getH());
	}
	
	hpIcon.setW(hpIcon.getW() * SCREEN_WIDTH / 1280);
	hpIcon.setH(hpIcon.getH() * SCREEN_HEIGHT / 720);
	hpIcon.setX(10 + portraitSize);
	hpIcon.setY(15);

	dmgIcon.setW(dmgIcon.getW() * SCREEN_WIDTH / 1280);
	dmgIcon.setH(dmgIcon.getH() * SCREEN_HEIGHT / 720);
	dmgIcon.setX(10 + portraitSize);
	dmgIcon.setY(60);

	option_box.setW(option_box.getW() * SCREEN_WIDTH / 1280);
	option_box.setH(option_box.getH() * SCREEN_HEIGHT / 720);
	option_box.setX((SCREEN_WIDTH - option_box.getW()) / 2);
	option_box.setY(30);

	bar.setW(bar.getW() * SCREEN_WIDTH / 1280);
	bar.setH(bar.getH() * SCREEN_HEIGHT / 720);
	bar.setX(option_box.getX() + 5);
	bar.setY(35);

	rectBar[0] = bar.getRect();
	rectBar[1] = bar.getRect();
	rectBar[1].x += bar.getW() + 5;

	arrow[0].setW(arrow[0].getW() * SCREEN_WIDTH / 1280);
	arrow[0].setH(arrow[0].getH() * SCREEN_HEIGHT / 720);
	arrow[0].setX(SCREEN_WIDTH / 4 - arrow[0].getW() - 40);
	arrow[0].setY((SCREEN_HEIGHT - arrow[0].getH()) / 2);

	arrow_range = { arrow[0].getX(), arrow[0].getX() + 40 };

	arrow[1].setW(arrow[1].getW() * SCREEN_WIDTH / 1280);
	arrow[1].setH(arrow[1].getH() * SCREEN_HEIGHT / 720);
	arrow[1].setX(3 * SCREEN_WIDTH / 4 + 40);
	arrow[1].setY((SCREEN_HEIGHT - arrow[1].getH()) / 2);
	
	play_button[0].setW(150);
	play_button[0].setH(play_button[0].getW() * 73 / 156);
	play_button[0].setX((SCREEN_WIDTH - play_button[0].getW()) / 2);
	play_button[0].setY(3 * SCREEN_HEIGHT / 4 + 35);
	
	play_button[1].setW(play_button[0].getW() + 8);
	play_button[1].setH(play_button[0].getH() + 8);
	play_button[1].setX(play_button[0].getX() - 4);
	play_button[1].setY(play_button[0].getY() - 4);

	itemBox.setW(itemBox.getW() * SCREEN_WIDTH / 1280);
	itemBox.setH(itemBox.getH() * SCREEN_HEIGHT / 720);
	itemBox.setX(10);
	itemBox.setY(10);

	charBox.setW(charBox.getW() * SCREEN_WIDTH / 1280);
	charBox.setH(charBox.getH() * SCREEN_HEIGHT / 720);
	charBox.setX(10);
	charBox.setY(itemBox.getY() + 20 + 2 * itemBox.getH());

	infoBox.setW(infoBox.getW() * SCREEN_WIDTH / 1280);
	infoBox.setH(infoBox.getH() * SCREEN_HEIGHT / 720);
	infoBox.setX(20 + charBox.getW() + charBox.getX());
	infoBox.setY(charBox.getY());

	costBox.setW(costBox.getW() * SCREEN_WIDTH / 1280);
	costBox.setH(costBox.getH() * SCREEN_HEIGHT / 720);
	costBox.setX(infoBox.getX() + (infoBox.getW() - costBox.getW()) / 2);
	costBox.setY(infoBox.getY() + infoBox.getH() - costBox.getH() - 20);

	selected.setW(selected.getW() * SCREEN_WIDTH / 1280);
	selected.setH(selected.getH() * SCREEN_HEIGHT / 720);
	selected.setH(150);
	selected.setW(150);

	selected_range = { 150, 170 };

	paused_box.setW(paused_box.getW() * SCREEN_WIDTH / 1280);
	paused_box.setH(paused_box.getH() * SCREEN_HEIGHT / 720);
	paused_box.setX((SCREEN_WIDTH - paused_box.getW()) / 2);
	paused_box.setY((SCREEN_HEIGHT - paused_box.getH()) / 2);
	SDL_SetTextureAlphaMod(paused_box.getObject(), 200);

	paused_return[0].setW(380);
	paused_return[0].setH(paused_return[0].getW() * 125 / 500);
	paused_return[0].setX(paused_box.getX() + (paused_box.getW() - paused_return[0].getW()) / 2);
	paused_return[0].setY(paused_box.getY() + paused_box.getH() - paused_return[0].getH() - 10);

	paused_return[1].setW(paused_return[0].getW() + 13);
	paused_return[1].setH(paused_return[0].getH() + 8);
	paused_return[1].setX(paused_return[0].getX() - 7);
	paused_return[1].setY(paused_return[0].getY() - 5);

	paused_continue[0].setW(paused_return[0].getW());
	paused_continue[0].setH(paused_return[0].getH());
	paused_continue[0].setX(paused_return[0].getX());
	paused_continue[0].setY(paused_return[0].getY() - paused_continue[0].getH() - 10);

	paused_continue[1].setW(paused_continue[0].getW() + 13);
	paused_continue[1].setH(paused_continue[0].getH() + 8);
	paused_continue[1].setX(paused_continue[0].getX() - 7);
	paused_continue[1].setY(paused_continue[0].getY() - 5);

	win.setW(win.getW()* SCREEN_WIDTH / 1280);
	win.setH(win.getH()* SCREEN_HEIGHT / 720);
	win.setX((SCREEN_WIDTH - win.getW()) / 2);
	win.setY((SCREEN_HEIGHT / 4));

	lose.setW(lose.getW() * SCREEN_WIDTH / 1280);
	lose.setH(lose.getH() * SCREEN_HEIGHT / 720);
	lose.setX((SCREEN_WIDTH - lose.getW()) / 2);
	lose.setY((SCREEN_HEIGHT / 4));

	dmgIconStat.setW(dmgIconStat.getW() * SCREEN_WIDTH / 1280);
	dmgIconStat.setH(dmgIconStat.getH() * SCREEN_HEIGHT / 720);
	dmgIconStat.setX(infoBox.getX() + 20);
	dmgIconStat.setY(costBox.getY() - 20 - dmgIconStat.getH());

	hpIconStat.setW(hpIconStat.getW() * SCREEN_WIDTH / 1280);
	hpIconStat.setH(hpIconStat.getH() * SCREEN_HEIGHT / 720);
	hpIconStat.setX(dmgIconStat.getX());
	hpIconStat.setY(dmgIconStat.getY() - 10 - hpIconStat.getH());

	statsRect.setW(statsRect.getW()* SCREEN_WIDTH / 1280);
	statsRect.setH(statsRect.getH()* SCREEN_HEIGHT / 720);

	std::ifstream file_instruction("Data/instruction.txt");
	std::string str;
	while (std::getline(file_instruction, str))
		instruction.push_back(str);

	file_instruction.close();
}

void GSSelect::startIntro(SDL_Renderer* renderer) {
	intro_background.render(renderer, 0);
}

void GSSelect::startScreen(SDL_Renderer* renderer)
{
	menu_background.render(renderer, 0);

	if (Guardian.getY() < 5)
		Guardian.setY(min(5, Guardian.getY() +
			Guardian.getVelY()));

	if (Adventure.getY() > 150 && Guardian.getY() == 5)
		Adventure.setY(max(150, Adventure.getY() +
			Adventure.getVelY()));

	Guardian.render(renderer, 0);

	Adventure.render(renderer, 0);

	int x, y;

	SDL_GetMouseState(&x, &y);

	if (curAlpha == 255) {

		if (inRect(x, y, start_button[0].getRect()))
			start_button[1].render(renderer, 0);

		else
			start_button[0].render(renderer, 0);

		if (inRect(x, y, exit_button[0].getRect()))
			exit_button[1].render(renderer, 0);

		else
			exit_button[0].render(renderer, 0);

		if (inRect(x, y, setting_button[0].getRect()))
			setting_button[1].render(renderer, 0);

		else
			setting_button[0].render(renderer, 0);

		if (inRect(x, y, credit_button[0].getRect()))
			credit_button[1].render(renderer, 0);

		else
			credit_button[0].render(renderer, 0);

		if (inRect(x, y, help_button[0].getRect()))
			help_button[1].render(renderer, 0);

		else
			help_button[0].render(renderer, 0);
	}
	if (curAlpha < 255 && Adventure.getY() == 150) curAlpha += 17;
	
}

void GSSelect::screenCredit(SDL_Renderer* renderer) {
	menu_background.render(renderer, 0);
	credit_background.render(renderer, 0);

	/// back_button
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inRect(x, y, back_button[0].getRect()))
		back_button[1].render(renderer, 0);

	else
		back_button[0].render(renderer, 0);
	

	std::string s = "Credit By";
	SDL_Surface* sf_font = NULL;
	sf_font = TTF_RenderText_Solid(font, s.c_str(), black);
	int w = sf_font->w, h = sf_font->h;
	SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	SDL_Rect nRect = { 0, 0, w, h };
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y = credit_background.getY() + 10;

	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	
	s = "Le Ngoc Minh";
	sf_font = TTF_RenderText_Solid(font, s.c_str(), white);
	nRect.w = sf_font->w, nRect.h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y += 70;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	s = "Nguyen Bao Quang";
	sf_font = TTF_RenderText_Solid(font, s.c_str(), white);
	nRect.w = sf_font->w, nRect.h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y += 60;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	s = "Khanh Toan";
	sf_font = TTF_RenderText_Solid(font, s.c_str(), white);
	nRect.w = sf_font->w, nRect.h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y += 60;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	
}

void GSSelect::screenSetting(SDL_Renderer* renderer, bool& current_music, bool& current_sfx) {
	menu_background.render(renderer, 0);
	credit_background.render(renderer, 0);

	/// back_button
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inRect(x, y, back_button[0].getRect()))
		back_button[1].render(renderer, 0);

	else
		back_button[0].render(renderer, 0);
	

	std::string s = "Setting";
	SDL_Surface* sf_font = NULL;
	sf_font = TTF_RenderText_Solid(font, s.c_str(), black);
	int w = sf_font->w, h = sf_font->h;
	SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	SDL_Rect nRect = { 0, 0, w, h };
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y = credit_background.getY() + 10;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	s = "Music: ";
	sf_font = TTF_RenderText_Solid(font, s.c_str(), white);
	nRect.w = sf_font->w, nRect.h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y += 90;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	for (int i = 0; i <= 1; i++) {
		music_button[i].setW(80);
		music_button[i].setH(music_button[i].getW());
		music_button[i].setX(nRect.x + nRect.w + 20);
		music_button[i].setY(nRect.y - (music_button[i].getH() - nRect.h) / 2);
	}
	
	/// music_button
	if (current_music) music_button[0].render(renderer, 0);
	else music_button[1].render(renderer, 0);

	s = "SFX: ";
	sf_font = TTF_RenderText_Solid(font, s.c_str(), white);
	nRect.w = sf_font->w, nRect.h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y += 90;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	for (int i = 0; i <= 1; i++) {
		sfx_button[i].setW(music_button[i].getW());
		sfx_button[i].setH(music_button[i].getH());
		sfx_button[i].setX(nRect.x + nRect.w + 20);
		sfx_button[i].setY(nRect.y - (sfx_button[i].getH() - nRect.h) / 2);
	}

	/// sfx_button
	if (current_sfx) sfx_button[0].render(renderer, 0);
	else sfx_button[1].render(renderer, 0);
}

void GSSelect::screenHelp(SDL_Renderer* renderer) {
	menu_background.render(renderer, 0);
	credit_background.render(renderer, 0);

	/// back_button
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inRect(x, y, back_button[0].getRect()))
		back_button[1].render(renderer, 0);
	else
		back_button[0].render(renderer, 0);

	std::string s = "Help";
	SDL_Surface* sf_font = NULL;
	sf_font = TTF_RenderText_Solid(font, s.c_str(), black);
	int w = sf_font->w, h = sf_font->h;
	SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	SDL_Rect nRect = { 0, 0, w, h };
	nRect.x = (2 * credit_background.getX() + credit_background.getW() - nRect.w) / 2;
	nRect.y = credit_background.getY() + 10;

	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_FreeSurface(sf_font); sf_font = NULL;
	SDL_DestroyTexture(nTexture); nTexture = NULL;

	SDL_Rect dRect{};
	dRect.x = nRect.x - 240;
	dRect.y = nRect.y + nRect.h + 10;

	for (int i = 0; i < instruction.size(); i++)
	{
		SDL_Surface* sf = TTF_RenderText_Solid(font, instruction[i].c_str(), white);
		SDL_Texture* tt = SDL_CreateTextureFromSurface(renderer, sf);

		dRect.w = (sf->w + 10) * SCREEN_WIDTH / 1280;
		dRect.h = sf->h * SCREEN_HEIGHT / 720;

		SDL_RenderCopy(renderer, tt, NULL, &dRect);
		SDL_DestroyTexture(tt); tt = NULL;
		SDL_FreeSurface(sf); sf = NULL;

		dRect.y += 50;
	}
}

void GSSelect::levelSelection(SDL_Renderer* renderer, int cur_level, int cur_character, int* character_level,
	int numCoin, int numGem, int lastLevel, int baseHp, int baseDmg, int** char_growth)
{
	/// arrow
	if (arrow_flag == 0)
	{
		arrow[0].setX(arrow[0].getX() - 5);
		arrow[1].setX(arrow[1].getX() + 5);
	}
	else
	{
		arrow[0].setX(arrow[0].getX() + 5);
		arrow[1].setX(arrow[1].getX() - 5);
	}
	if (arrow[0].getX() == arrow_range.first)
		arrow_flag = 1;
	else if (arrow[0].getX() == arrow_range.second)
		arrow_flag = 0;

	/// upper bar
	if (flag == 1 && bar.getX() < rectBar[1].x)
		bar.setX(min(bar.getX() + 75, rectBar[1].x));
	else if (flag == 0 && bar.getX() > rectBar[0].x)
		bar.setX(max(bar.getX() - 75, rectBar[0].x));

	menu_background.render(renderer, 0);
	option_box.render(renderer, 0);
	bar.render(renderer, 0);

	/// back_button
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (inRect(x, y, back_button[0].getRect()))
		back_button[1].render(renderer, 0);
	else
		back_button[0].render(renderer, 0);

	std::string s = "Level Selection";
	SDL_Surface* sf_font = NULL;
	if (flag == 0) sf_font = TTF_RenderText_Solid(textFont, s.c_str(), backColor);
	else sf_font = TTF_RenderText_Solid(textFont, s.c_str(), textColor);
	int w = sf_font->w, h = sf_font->h;
	SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);

	SDL_Rect nRect = { 0, 0, w, h };
	nRect.x = rectBar[0].x + (rectBar[0].w - w) / 2;
	nRect.y = rectBar[0].y + (rectBar[0].h - h) / 2;

	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	s = "Characters";

	if (flag == 1) sf_font = TTF_RenderText_Solid(textFont, s.c_str(), backColor);
	else sf_font = TTF_RenderText_Solid(textFont, s.c_str(), textColor);

	w = sf_font->w, h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);

	nRect = { 0, 0, w, h };
	nRect.x = rectBar[1].x + (rectBar[1].w - w) / 2;
	nRect.y = rectBar[1].y + (rectBar[1].h - h) / 2;

	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	/// Gem and Coin box
	itemBox.render(renderer, 0);

	nRect = itemBox.getRect();
	nRect.y += itemBox.getH() + 5;
	SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &nRect);

	nRect.x += 5;
	nRect.y += 5;
	nRect.w = 30 * SCREEN_WIDTH / 1280;
	nRect.h = 30 * SCREEN_HEIGHT / 720;
	SDL_RenderCopy(renderer, gem, NULL, &nRect);

	nRect.y = itemBox.getY() + 5;
	SDL_RenderCopy(renderer, coin, NULL, &nRect);

	/// Coin text
	sf_font = TTF_RenderText_Solid(textFont, int2str(numCoin).c_str(), white);
	w = sf_font->w * SCREEN_WIDTH / 1280, h = sf_font->h * SCREEN_HEIGHT / 720;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = itemBox.getX() + itemBox.getW() - 10 - w;
	nRect.y = itemBox.getY() + 7;
	nRect.w = w, nRect.h = h;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	/// Gem text
	sf_font = TTF_RenderText_Solid(textFont, int2str(numGem).c_str(), white);
	w = sf_font->w * SCREEN_WIDTH / 1280, h = sf_font->h * SCREEN_HEIGHT / 720;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = itemBox.getX() + itemBox.getW() - 10 - w;
	nRect.y = itemBox.getY() + 7 + itemBox.getH() + 5;
	nRect.w = w, nRect.h = h;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	/// load Character
	if (change_character) { /// load Character in Level Selection
		description.clear();
		frame = 0;
		std::string path = "Data/Textures/Character/" + int2str(cur_character);
		SDL_Surface* sf = IMG_Load((path + "/idle0.png").c_str());
		character_texture = SDL_CreateTextureFromSurface(renderer, sf);
		change_character = false;
		std::ifstream file((path + "/char_info.txt").c_str());
		file >> cw >> ch;
		file >> fr.first;
		file >> fr.first >> fr.second;
		file.close();

		std::ifstream file_description((path + "/description.txt").c_str());
		std::string s;
		while (std::getline(file_description, s))
			description.push_back(s);

		file_description.close();

		SDL_FreeSurface(sf); sf = NULL;
	}
	SDL_Rect fRect = { 0, 0, charSize, charSize };
	fRect.x = (frame % fr.first) * charSize;
	fRect.y = (frame / fr.first) * charSize;

	if (flag == 0)
	{
		if (change_level)
		{
			std::string path = "Data/Textures/img/Level_" + int2str(cur_level) + "/background.png";
			SDL_Surface* sf = IMG_Load(path.c_str());
			level_background = SDL_CreateTextureFromSurface(renderer, sf);

			path = "Data/Textures/img/Level_" + int2str(cur_level) + "/name.png";
			level_name.loadImage(path, renderer);
			level_name.setW(level_name.getW() * SCREEN_WIDTH / 1280);
			level_name.setH(level_name.getH() * SCREEN_HEIGHT / 720);
			level_name.setX(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - level_name.getW()) / 2);
			level_name.setY(SCREEN_HEIGHT / 4 + 10);

			SDL_FreeSurface(sf); sf = NULL;
			change_level = false;
		}

		SDL_Rect nRect{}, tRect;
		nRect.x = SCREEN_WIDTH / 4;
		nRect.y = SCREEN_HEIGHT / 4;
		nRect.w = SCREEN_WIDTH / 2;
		nRect.h = SCREEN_HEIGHT / 2;
		tRect = nRect;
		tRect.x -= 4;
		tRect.y -= 4;
		tRect.w += 8;
		tRect.h += 8;
		SDL_SetRenderDrawColor(renderer, 120, 120, 0, 255);
		SDL_RenderFillRect(renderer, &tRect);

		SDL_RenderCopy(renderer, level_background, NULL, &nRect);

		nRect.x = nRect.x + nRect.w - 40;
		nRect.y = nRect.y + 10;
		nRect.w = nRect.h = 30;
		if (cur_level < lastLevel)
			SDL_RenderCopy(renderer, star, NULL, &nRect);
		else if (cur_level > lastLevel)
			SDL_RenderCopy(renderer, lock, NULL, &nRect);
		else SDL_RenderCopy(renderer, nostar, NULL, &nRect);

		level_name.render(renderer, 0);

		if (cur_level > 1) arrow[0].render(renderer, 0);
		if (cur_level < numLevel) arrow[1].render(renderer, 0);

		if (cur_level <= lastLevel) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (inRect(x, y, play_button[0].getRect()))
				play_button[1].render(renderer, 0);

			else
				play_button[0].render(renderer, 0);
		}

		SDL_Rect cRect = { 0, 0, charSize, charSize };
		cRect.x = (SCREEN_WIDTH - charSize) / 2 + (charSize / 3 - cw) / 2;
		cRect.y = (SCREEN_HEIGHT - charSize) / 2;
		SDL_RenderCopy(renderer, character_texture, &fRect, &cRect);
		frame++;
		while (frame >= fr.second) frame -= fr.second;
	}
	else
	{
		if (selected_flag == 0)
		{
			selected.setW(selected.getW() - 4);
			selected.setH(selected.getH() - 4);
		}
		else
		{
			selected.setW(selected.getW() + 4);
			selected.setH(selected.getH() + 4);
		}
		if (selected.getW() == selected_range.first)
			selected_flag = 1;
		else if (selected.getW() == selected_range.second)
			selected_flag = 0;

		charBox.render(renderer, 0);
		infoBox.render(renderer, 0);
		costBox.render(renderer, 0);
		int col = 5;
		int row = (numCharacter - 1) / col;
		int dis = 20;
		/// draw charBox
		for (int i = 0; i <= row; i++)
			for (int j = 0; j < col; j++)
			{
				int id = i * col + j;
				if (id >= numCharacter) break;
				SDL_Rect nRect = { 0, 0, ptSize, ptSize };
				nRect.w = nRect.w * SCREEN_WIDTH / 1280;
				nRect.h = nRect.h * SCREEN_HEIGHT / 720;
				nRect.x = charBox.getX() + dis + j * (dis + ptSize);
				nRect.y = charBox.getY() + dis + i * (dis + ptSize);
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				if (id == cur_character)
					SDL_RenderFillRect(renderer, &nRect);
				SDL_RenderDrawRect(renderer, &nRect);
				SDL_RenderCopy(renderer, portrait[id], NULL, &nRect);

				SDL_Rect nnRect = nRect;
				SDL_RenderDrawRect(renderer, &nnRect);

				nnRect.x = nnRect.x + nnRect.w - 40;
				nnRect.y = nnRect.y + 10;
				nnRect.w = 30 * SCREEN_WIDTH / 1280;
				nnRect.h = 30 * SCREEN_HEIGHT / 720;
				if (character_level[id] == 0)
					SDL_RenderCopy(renderer, lock, NULL, &nnRect);

				if (id == cur_character)
				{
					selected.setX(nRect.x - (selected.getW() - nRect.w) / 2);
					selected.setY(nRect.y - (selected.getH() - nRect.h) / 2);
				}
			}
		/// draw infoBox
		SDL_Rect cRect = { 0, 0, charSize, charSize };
		cRect.x = infoBox.getX() + (infoBox.getW() - charSize) / 2 + (charSize / 3 - cw) / 2;
		cRect.y = infoBox.getY() - 80;
		SDL_RenderCopy(renderer, character_texture, &fRect, &cRect);

		SDL_Surface* sf = NULL;
		SDL_Texture* tt = NULL;

		///draw Stat
		hpIconStat.render(renderer, 0);
		dmgIconStat.render(renderer, 0);

		int newHp = baseHp, newDmg = baseDmg;
		if (character_level[cur_character] > 0)
		{
			newHp += (character_level[cur_character] - 1) * char_growth[cur_character][1];
			newDmg += (character_level[cur_character] - 1) * char_growth[cur_character][0];
		}

		SDL_Rect hpRect, dmgRect;
		sf = TTF_RenderText_Solid(textFont, int2str(newDmg).c_str(), textColor);
		tt = SDL_CreateTextureFromSurface(renderer, sf);

		dmgRect = { 0, 0, sf->w * SCREEN_WIDTH / 1280,sf->h * SCREEN_HEIGHT / 720 };
		dmgRect.x = dmgIconStat.getX() + dmgIconStat.getW() + 10;
		dmgRect.y = dmgIconStat.getY() + (dmgIconStat.getH() - sf->h) / 2;
		SDL_RenderCopy(renderer, tt, NULL, &dmgRect);
		SDL_DestroyTexture(tt); tt = NULL;
		SDL_FreeSurface(sf); sf = NULL;

		if (character_level[cur_character] > 0)
		{
			sf = TTF_RenderText_Solid(textFontBig, int2str(newDmg + char_growth[cur_character][0]).c_str(), green);
			tt = SDL_CreateTextureFromSurface(renderer, sf);
			dmgRect.w = sf->w * SCREEN_WIDTH / 1280;
			dmgRect.h = sf->h * SCREEN_HEIGHT / 720;
			dmgRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
			dmgRect.y -= 5;
			SDL_RenderCopy(renderer, tt, NULL, &dmgRect);
			SDL_DestroyTexture(tt); tt = NULL;
			SDL_FreeSurface(sf); sf = NULL;
		}

		sf = TTF_RenderText_Solid(textFont, int2str(newHp).c_str(), textColor);
		tt = SDL_CreateTextureFromSurface(renderer, sf);

		hpRect = { 0, 0, sf->w * SCREEN_WIDTH / 1280 ,sf->h * SCREEN_HEIGHT / 720 };
		hpRect.x = hpIconStat.getX() + hpIconStat.getW() + 10;
		hpRect.y = hpIconStat.getY() + (hpIconStat.getH() - sf->h) / 2;
		SDL_RenderCopy(renderer, tt, NULL, &hpRect);
		SDL_DestroyTexture(tt); tt = NULL;
		SDL_FreeSurface(sf); sf = NULL;

		if (character_level[cur_character] > 0)
		{
			sf = TTF_RenderText_Solid(textFontBig, int2str(newHp + char_growth[cur_character][1]).c_str(), green);
			tt = SDL_CreateTextureFromSurface(renderer, sf);
			hpRect.w = sf->w * SCREEN_WIDTH / 1280;
			hpRect.h = sf->h * SCREEN_HEIGHT / 720;
			hpRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
			hpRect.y -= 5;
			SDL_RenderCopy(renderer, tt, NULL, &hpRect);
			SDL_DestroyTexture(tt); tt = NULL;
			SDL_FreeSurface(sf); sf = NULL;
		}

		/// draw Level Character
		sf = TTF_RenderText_Solid(textFont, ("Lv. " + int2str(character_level[cur_character])).c_str(), textColor);
		tt = SDL_CreateTextureFromSurface(renderer, sf);
		SDL_Rect lvRect = { 0, 0, sf->w * SCREEN_WIDTH / 1280 ,sf->h * SCREEN_HEIGHT / 720 };
		lvRect.x = hpIconStat.getX() + hpIconStat.getW() + 0;
		lvRect.y = hpIconStat.getY() - lvRect.h - 10;
		SDL_RenderCopy(renderer, tt, NULL, &lvRect);
		SDL_DestroyTexture(tt); tt = NULL;
		SDL_FreeSurface(sf); sf = NULL;

		if (character_level[cur_character] > 0)
		{
			sf = TTF_RenderText_Solid(textFontBig, ("Lv. " + int2str(character_level[cur_character] + 1)).c_str(), green);
			tt = SDL_CreateTextureFromSurface(renderer, sf);
			lvRect.w = sf->w * SCREEN_WIDTH / 1280;
			lvRect.h = sf->h * SCREEN_HEIGHT / 720;
			lvRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
			lvRect.y -= 5;
			SDL_RenderCopy(renderer, tt, NULL, &lvRect);
			SDL_DestroyTexture(tt); tt = NULL;
			SDL_FreeSurface(sf); sf = NULL;
		}

		if (character_level[cur_character] > 0)
		{
			SDL_Rect aRect = { 0, 0, 25 * SCREEN_WIDTH / 1280, 23 * SCREEN_HEIGHT / 720 };

			aRect.x = dmgIconStat.getX() + (130 * SCREEN_WIDTH / 1280);
			aRect.y = dmgIconStat.getY() + (hpIconStat.getH() - aRect.h) / 2;
			SDL_RenderCopy(renderer, statArrow, NULL, &aRect);

			aRect.x = hpIconStat.getX() + (130 * SCREEN_WIDTH / 1280);
			aRect.y = hpIconStat.getY() + (hpIconStat.getH() - aRect.h) / 2;
			SDL_RenderCopy(renderer, statArrow, NULL, &aRect);

			aRect.y -= 20 + aRect.h;
			SDL_RenderCopy(renderer, statArrow, NULL, &aRect);
		}


		///Draw Description

		SDL_Rect dRect{};
		dRect.x = infoBox.getX() + 10;
		dRect.y = infoBox.getY() + charSize - 130;

		for (int i = 0; i < description.size(); i++)
		{
			sf = TTF_RenderText_Solid(textFontSmall, description[i].c_str(), textColor);
			tt = SDL_CreateTextureFromSurface(renderer, sf);

			dRect.w = sf->w * SCREEN_WIDTH / 1280;
			dRect.h = sf->h * SCREEN_HEIGHT / 720;

			SDL_RenderCopy(renderer, tt, NULL, &dRect);
			SDL_DestroyTexture(tt); tt = NULL;
			SDL_FreeSurface(sf); sf = NULL;

			dRect.y += 25;
		}

		///draw Cost
		if (character_level[cur_character] > 0)
			cost[cur_character] = getCost(character_level[cur_character]);

		std::string temp = "Unlock";
		if (character_level[cur_character] > 0) temp = "Upgrade";

		sf = TTF_RenderText_Solid(textFont, temp.c_str(), black);
		tt = SDL_CreateTextureFromSurface(renderer, sf);

		lvRect = { 0, 0, sf->w * SCREEN_WIDTH / 1280 ,sf->h * SCREEN_HEIGHT / 720 };
		lvRect.x = costBox.getX() + 40;
		lvRect.y = costBox.getY() + (costBox.getH() - sf->h) / 2;
		SDL_RenderCopy(renderer, tt, NULL, &lvRect);

		lvRect.x += 30 + sf->w;
		lvRect.y = costBox.getY() + (costBox.getH() - 30) / 2;
		lvRect.w = 30 * SCREEN_WIDTH / 1280;
		lvRect.h = 30 * SCREEN_HEIGHT / 720;
		if (character_level[cur_character] > 0)
			SDL_RenderCopy(renderer, coin, NULL, &lvRect);
		else
			SDL_RenderCopy(renderer, gem, NULL, &lvRect);

		SDL_FreeSurface(sf); sf = NULL;
		SDL_DestroyTexture(tt); tt = NULL;
		if (character_level[cur_character] > 0 && numCoin >= cost[cur_character])
			sf = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), black);
		else if (character_level[cur_character] == 0 && numGem >= cost[cur_character])
			sf = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), black);
		else
			sf = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), red);

		tt = SDL_CreateTextureFromSurface(renderer, sf);

		lvRect.w = sf->w * SCREEN_WIDTH / 1280;
		lvRect.h = sf->h * SCREEN_HEIGHT / 720;
		lvRect.x += 40;
		lvRect.y = costBox.getY() + (costBox.getH() - (sf->h * SCREEN_HEIGHT / 720)) / 2;
		SDL_RenderCopy(renderer, tt, NULL, &lvRect);

		frame++;
		while (frame >= fr.second) frame -= fr.second;
		selected.render(renderer, 0);

		SDL_FreeSurface(sf); sf = NULL;
		SDL_DestroyTexture(tt); tt = NULL;
	}
}

void GSSelect::ingame(SDL_Renderer* renderer, int char_hp, int char_dmg, int numCoin, int numGem, bool paused, int level_end)
{
	statsRect.render(renderer, 0);
	hpIcon.render(renderer, 0);
	dmgIcon.render(renderer, 0);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, int2str(char_hp).c_str(), white);

	SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect temp = { 160, 8, textSurface->w, textSurface->h };

	SDL_RenderCopy(renderer, nTexture, NULL, &temp);

	SDL_FreeSurface(textSurface); textSurface = NULL;

	SDL_DestroyTexture(nTexture); nTexture = NULL;

	textSurface = TTF_RenderText_Solid(font, int2str(char_dmg).c_str(), white);

	nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	temp = { 160, 55, textSurface->w, textSurface->h };

	SDL_RenderCopy(renderer, nTexture, NULL, &temp);

	SDL_FreeSurface(textSurface); textSurface = NULL;

	SDL_DestroyTexture(nTexture); nTexture = NULL;

	/// Gem and Coin box

	SDL_Rect nRect = itemBox.getRect();
	nRect.x = SCREEN_WIDTH / 2;
	nRect.y = 5;
	SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &nRect);

	nRect.x += itemBox.getW() + 10;
	SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &nRect);

	nRect.x += 5;
	nRect.y += 5;
	nRect.w = nRect.h = 30;
	SDL_RenderCopy(renderer, gem, NULL, &nRect);

	nRect.x = SCREEN_WIDTH / 2 + 5;
	SDL_RenderCopy(renderer, coin, NULL, &nRect);

	/// Coin text
	SDL_Surface* sf_font = TTF_RenderText_Solid(textFont, int2str(numCoin).c_str(), white);
	int w = sf_font->w, h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = SCREEN_WIDTH / 2 + itemBox.getW() - 10 - w;
	nRect.y = 15;
	nRect.w = w, nRect.h = h;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	/// Gem text
	sf_font = TTF_RenderText_Solid(textFont, int2str(numGem).c_str(), white);
	w = sf_font->w, h = sf_font->h;
	nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
	nRect.x = SCREEN_WIDTH / 2 + 2 * itemBox.getW() - w;
	nRect.w = w, nRect.h = h;
	SDL_RenderCopy(renderer, nTexture, NULL, &nRect);
	SDL_DestroyTexture(nTexture); nTexture = NULL;
	SDL_FreeSurface(sf_font); sf_font = NULL;

	if (paused == true)
	{
		paused_box.render(renderer, 0);
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (inRect(x, y, paused_return[0].getRect()))
			paused_return[1].render(renderer, 0);
		else
			paused_return[0].render(renderer, 0);

		if (inRect(x, y, paused_continue[0].getRect()))
			paused_continue[1].render(renderer, 0);
		else
			paused_continue[0].render(renderer, 0);

	}

	if (level_end == 2) win.render(renderer, 0);
	else if (level_end == 1) lose.render(renderer, 0);
}

void GSSelect::handleMouseInput(int x, int y, int& currentState, int& cur_level, int& cur_character, int* character_level, 
								int& numCoin, int& numGem, int lastLevel, bool& paused, bool& current_music, bool& current_sfx)
{
	if (currentState == STATE::MENU)
	{
		if (curAlpha == 255)
		{
			if (inRect(x, y, exit_button[0].getRect()))
				currentState = STATE::NONE;
			if (inRect(x, y, start_button[0].getRect()))
				currentState = STATE::SELECT;
			if (inRect(x, y, credit_button[0].getRect()))
				currentState = STATE::CREDIT;
			if (inRect(x, y, setting_button[0].getRect()))
				currentState = STATE::SETTING;
			if (inRect(x, y, help_button[0].getRect()))
				currentState = STATE::HELP;
		}
	}
	else if (currentState == STATE::SELECT)
	{
		if (inRect(x, y, back_button[0].getRect())) {
			currentState = STATE::MENU;
		}
		if (flag && inRect(x, y, rectBar[0]))
			flag = 0;
		else if (!flag && inRect(x, y, rectBar[1]))
			flag = 1;

		if (!flag)
		{
			if (character_level[cur_character] == 0)
			{
				cur_character = prev;
				change_character = true;
			}
			if (inRect(x, y, arrow[0].getRect()) && cur_level > 1)
			{
				cur_level--;
				change_level = true;
			}
			else if (inRect(x, y, arrow[1].getRect()) && cur_level < numLevel)
			{
				cur_level++;
				change_level = true;
			}

			if (inRect(x, y, play_button[0].getRect()))
			{
				if (cur_level <= lastLevel)
					currentState = STATE::PLAY;
			}
		}
		else
		{
			int col = 5;
			int row = (numCharacter - 1) / col;
			int dis = 20;
			int ptSize = 150;
			for (int i = 0; i <= row; i++)
				for (int j = 0; j < col; j++)
				{
					int id = i * col + j;
					if (id >= numCharacter) break;
					SDL_Rect nRect = { 0, 0, ptSize, ptSize };
					nRect.x = charBox.getX() + dis + j * (dis + ptSize);
					nRect.y = charBox.getY() + dis + i * (dis + ptSize);
					if (inRect(x, y, nRect))
					{
						if (character_level[id] > 0)
							prev = id;
						if (id != cur_character) {
							change_character = true;
						}
						cur_character = id;
					}
				}
			if (inRect(x, y, costBox.getRect()))
			{
				if (character_level[cur_character] == 0 && numGem >= cost[cur_character])
				{
					numGem -= cost[cur_character];
					character_level[cur_character]++;
				}
				else if (character_level[cur_character] > 0 && numCoin >= cost[cur_character])
				{
					numCoin -= cost[cur_character];
					character_level[cur_character]++;
				}
			}
		}
	}
	else if (currentState == STATE::PLAY)
	{
		if (paused)
		{
			if (inRect(x, y, paused_continue[0].getRect()))
				paused = false;
			if (inRect(x, y, paused_return[0].getRect()))
			{
				paused = false;
				currentState = STATE::SELECT;
			}
		}
	}
	else if (currentState == STATE::CREDIT) {
		if (inRect(x, y, back_button[0].getRect())) {
			currentState = STATE::MENU;
		}
	}
	else if (currentState == STATE::SETTING) {
		if (inRect(x, y, back_button[0].getRect())) {
			currentState = STATE::MENU;
		}
		if (inRect(x, y, music_button[0].getRect()) || 
				inRect(x, y, music_button[1].getRect())) {
			current_music = 1 - current_music;
		}
		
		if (inRect(x, y, sfx_button[0].getRect()) || 
				inRect(x, y, sfx_button[1].getRect())) {
			current_sfx = 1 - current_sfx;
		}
		
	}
	else if (currentState == STATE::HELP) {
		if (inRect(x, y, back_button[0].getRect())) {
			currentState = STATE::MENU;
		}
	}
}

void GSSelect::handleKeyInput(SDL_Event event, bool& paused, int& currentState)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_p:
	{
		paused = 1 - paused;
	}
	break;
	case SDLK_ESCAPE:
	{
		if (currentState == STATE::MENU)
			currentState = STATE::NONE;
		else if (currentState == STATE::SELECT || currentState == STATE::CREDIT || 
				currentState == STATE::SETTING || currentState == STATE::HELP)
			currentState = STATE::MENU;
		else paused = 1 - paused;
	}

	}
}