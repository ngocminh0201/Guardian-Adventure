#pragma once
#include "SDL_mixer.h"
#include "Define.h"
#include <string>
#include <vector>
class Sound
{
public:
	Sound();
	~Sound();
	bool Init();
	void PlaySound();
	void PauseSound();
	void ResumeSound();
	
	void LoadSound(std::string pathMusic);
	unsigned int LoadSfx(const char * path);
	void PlaySfx(unsigned int sfx, int repeat = 0);
	void CleanUp();

    void loadAudioFiles();
    void playBackgroundMusic(int currentState, int level);
    void stopAudio();
    void stopSfx();
    void collectItem();
    void changeMap();
    void selectCharacter();
    void unlockCharacter();
    void upgradeCharacter();
    void mouse_click();
    void playButton();
    void winGame();
    void loseGame();
    void mobDie();
    void mobHurt();
    void character_heal();
    void bomb_explosion();
    void character_attack(int cur_character);
    void character_move(int type);
    void character_jump();
    void character_hurt();
    void setMove() { nextMove = 0; }
    void play_boss_audio(int status);

    void setMusic(bool music) { this->music = music; }
    void setSfx(bool sfx) { this->sfx = sfx; }

private:
	std::string m_PathMusic;
	Mix_Music* m_Music = NULL;
	std::vector<Mix_Chunk*>	sfxs;
    bool music, sfx;
    Mix_Music* bgm_level[numLevel];
    Mix_Music* startScreen;
    Mix_Music* levelSelection;
    Mix_Chunk* collect_item;
    Mix_Chunk* change_map;
    Mix_Chunk* select_character;
    Mix_Chunk* unlock;
    Mix_Chunk* upgrade;
    Mix_Chunk* click;
    Mix_Chunk* play_button;
    Mix_Chunk* win;
    Mix_Chunk* lose;
    Mix_Chunk* mob_die;
    Mix_Chunk* mob_hurt;
    Mix_Chunk* explosion;
    Mix_Chunk* heal;
    Mix_Chunk* char_attack[numCharacter];
    Mix_Chunk* walk;
    Mix_Chunk* fly;
    int nextMove;
    Mix_Chunk* jump;
    Mix_Chunk* _character_hurt;
    Mix_Chunk* bossAudio[numStatus];
};
