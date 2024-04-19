#pragma once
#include "GameStateBase.h"
#include "Define.h"
#include "GameObject.h"
#include "MouseButton.h"

class GSSelect : public GameStateBase, GameObject {
public:
	GSSelect();
	~GSSelect();

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

	void loadTexture(SDL_Renderer* renderer);
    void startIntro(SDL_Renderer* renderer);
	void startScreen(SDL_Renderer* renderer);
    void screenCredit(SDL_Renderer* renderer);
    void screenSetting(SDL_Renderer* renderer, bool& current_music, bool& current_sfx);
    void screenHelp(SDL_Renderer* renderer);
	void ingame(SDL_Renderer* renderer, int char_hp, int char_dmg, int numCoin, int numGem, bool paused, int level_end);
	void levelSelection(SDL_Renderer* renderer, int cur_level, int cur_character, int* character_level, 
                          int numCoin, int numGem, int lastLevel, int baseHp, int baseDmg, int** char_growth);
	void handleMouseInput(int x, int y, int& currentState, int& cur_level, int& cur_character, 
                        int* character_level, int& numCoin, int& numGem, int lastLevel, 
                        bool& paused, bool& current_music, bool& current_sfx);
	void handleKeyInput(SDL_Event event, bool& paused, int& currentState);
    int getFlag() const { return flag; }
protected:
    std::list<std::shared_ptr<MouseButton>>	m_listButton;
    std::shared_ptr<MouseButton> button;
    GameObject intro_background;
    GameObject menu_background;
    GameObject credit_background;
    GameObject Guardian;
    GameObject Adventure;
    GameObject back_button[2];
    GameObject start_button[2];
    GameObject exit_button[2];
    GameObject credit_button[2];
    GameObject setting_button[2];
    GameObject music_button[2];
    GameObject sfx_button[2];
    GameObject help_button[2];
    GameObject hpIcon, dmgIcon;
    GameObject hpIconStat, dmgIconStat;
    GameObject statsRect;
    GameObject option_box, bar;
    GameObject play_button[2];
    GameObject arrow[2];
    GameObject level_name;
    GameObject itemBox;
    GameObject charBox, infoBox;
    GameObject costBox;
    GameObject selected;
    GameObject paused_box;
    GameObject paused_return[2];
    GameObject paused_continue[2];
    GameObject win, lose;
    
    SDL_Texture* level_background;
    SDL_Texture* character_texture;
    SDL_Texture* gem;
    SDL_Texture* coin;
    SDL_Texture* portrait[numCharacter];
    SDL_Texture* lock;
    SDL_Texture* star;
    SDL_Texture* nostar;
    SDL_Texture* statArrow;
    TTF_Font* font;
    TTF_Font* textFont;
    TTF_Font* textFontBig;
    TTF_Font* textFontSmall;
    SDL_Rect rectBar[2];
    int curAlpha;
    int itemCount[3];
    bool flag = 0;
    bool change_level;
    bool arrow_flag, selected_flag;
    std::pair<int, int> arrow_range, selected_range;
    std::pair<int, int> fr;
    bool change_character;
    int frame = 0;
    int cw, ch;
    int ptSize;
    int prev;
    std::vector<std::string> description, instruction;
    long long* cost;
};