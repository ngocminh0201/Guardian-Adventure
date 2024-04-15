#include"Sound.h"
#include <SDL_ttf.h>

Sound::Sound()
{
    Init();
    for (int i = 0; i < numLevel; i++)
        bgm_level[i] = NULL;

    for (int i = 0; i < numCharacter; i++)
        char_attack[i] = NULL;

    for (int i = 0; i < numStatus; i++)
        bossAudio[i] = NULL;

    startScreen = NULL;
    levelSelection = NULL;
    collect_item = NULL;
    change_map = NULL;
    select_character = NULL;
    unlock = NULL;
    upgrade = NULL;
    click = NULL;
    play_button = NULL;
    win = NULL;
    lose = NULL;
    mob_die = NULL;
    heal = NULL;
    explosion = NULL;
    walk = NULL;
    fly = NULL;
    jump = NULL;

    nextMove = 0;
}

Sound::~Sound()
{
    CleanUp();
    for (int i = 0; i < numLevel; i++)
        Mix_FreeMusic(bgm_level[i]);

    for (int i = 0; i < numCharacter; i++)
        Mix_FreeChunk(char_attack[i]);

    for (int i = 0; i < numStatus; i++)
        Mix_FreeChunk(bossAudio[i]);
    Mix_FreeMusic(startScreen);
    //printf("startScreen\n");

    Mix_FreeMusic(levelSelection);
    //printf("levelSelection\n");

    Mix_FreeChunk(collect_item);
   // printf("collect_item\n");

    Mix_FreeChunk(change_map);
    //printf("cchange_map\n");
    Mix_FreeChunk(select_character);
    //printf("select_character\n");
    Mix_FreeChunk(upgrade);
    //printf("upgrade\n");
    Mix_FreeChunk(unlock);
   // printf("unlock\n");
    Mix_FreeChunk(click);
   // printf("click\n");
    Mix_FreeChunk(play_button);
   // printf("play_button\n");
    Mix_FreeChunk(win);
   // printf("win\n");
   // std::cout << lose << '\n';
    Mix_FreeChunk(lose);
   // printf("lose\n");
    //std::cout << mob_die << '\n';
    Mix_FreeChunk(mob_die);
    //printf("mob_die\n");

    Mix_FreeChunk(heal);
    //printf("heal\n");
    Mix_FreeChunk(explosion);
    Mix_FreeChunk(fly);
    Mix_FreeChunk(walk);
    Mix_FreeChunk(jump);

}

bool Sound::Init()
{
    bool ret = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //SDL_INIT_AUDIO for Init SDL audio
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        ret = false;
        
    }
    //Initialize SDL_mixer
      // first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems. The second argument determines the sample format, which again here we're using the default. The third argument is the number of hardware channels, and here we're using 2 channels for stereo. The last argument is the sample size, which determines the size of the chunks we use when playing sound. 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        ret = false;
    }
    return ret;
}

void Sound::PlaySound()
{
    //If there is no music playing
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(m_Music, -1); // The first argument is the music we want to play and the last argument is the number of times to repeat it. -1 for loop it util stop
    }
    //If music is being played
    else
    {
        //If the music is paused
        if (Mix_PausedMusic() == 1)
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void Sound::PauseSound()
{
    //Pause the music
    Mix_PauseMusic();
}

void Sound::ResumeSound()
{
    //Resume the music
    Mix_ResumeMusic();
}

void Sound::stopAudio()
{
    //Stop the music
    Mix_HaltMusic();
}

void Sound::LoadSound(std::string pathMusic)
{
    //Load music
    m_Music = Mix_LoadMUS(pathMusic.c_str());
    if (m_Music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        
    }
}


unsigned int Sound::LoadSfx(const char * path)
{
	unsigned int ret = 0;
	Mix_Chunk * chunk = Mix_LoadWAV(path);
	if (chunk == nullptr)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else
	{
		sfxs.push_back(std::move(chunk));
		ret = sfxs.size() - 1;
	}
	return ret;
}

void Sound::PlaySfx(unsigned int sfx, int repeat)
{
	if (sfx < sfxs.size())
	{
		Mix_PlayChannel(-1, sfxs[sfx], repeat);
	}
}

void Sound::CleanUp()
{
    //Free Music
	for (auto it = sfxs.begin(); it != sfxs.end(); it++)
	{
		Mix_FreeChunk(*it);
	}
	sfxs.clear();
    Mix_FreeMusic(m_Music);
    m_Music = NULL;
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void Sound::loadAudioFiles()
{
    startScreen = Mix_LoadMUS("audio/startScreen.wav");
    levelSelection = Mix_LoadMUS("audio/levelSelection.wav");
    for (int i = 0; i < numLevel; i++)
    {
        std::string path = "audio/bgm_" + int2str(i + 1) + ".wav";
        bgm_level[i] = Mix_LoadMUS(path.c_str());
    }
    collect_item = Mix_LoadWAV("audio/collect_item.wav");
    change_map = Mix_LoadWAV("audio/change_map.wav");
    select_character = Mix_LoadWAV("audio/select_character.wav");
    unlock = Mix_LoadWAV("audio/unlock.wav");
    upgrade = Mix_LoadWAV("audio/upgrade.wav");
    click = Mix_LoadWAV("audio/click.wav");
    play_button = Mix_LoadWAV("audio/play.wav");
    win = Mix_LoadWAV("audio/win.wav");
    lose = Mix_LoadWAV("audio/lose.wav");
    mob_die = Mix_LoadWAV("audio/mob_die.wav");
    heal = Mix_LoadWAV("audio/heal.wav");
    explosion = Mix_LoadWAV("audio/explosion.wav");
    walk = Mix_LoadWAV("audio/walk.wav");
    fly = Mix_LoadWAV("audio/fly.wav");
    jump = Mix_LoadWAV("audio/jump.wav");

    for (int i = 0; i < numCharacter; i++)
    {
        std::string path = "audio/attack_" + int2str(i) + ".wav";
        char_attack[i] = Mix_LoadWAV(path.c_str());
    }

    for (int i = 0; i < numStatus; i++)
    {
        std::string path = "audio/boss_" + int2str(i) + ".wav";
        bossAudio[i] = Mix_LoadWAV(path.c_str());
    }
}

void Sound::playBackgroundMusic(int isRunning, int level)
{
    if (Mix_PlayingMusic() == false)
    {
        if (isRunning == 1)
            Mix_PlayMusic(startScreen, -1);
        else if (isRunning == 2)
            Mix_PlayMusic(levelSelection, -1);
        else if (isRunning == 3)
            Mix_PlayMusic(bgm_level[level - 1], -1);
    }

    if (Mix_PlayingMusic() == false)
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void Sound::collectItem()
{
    Mix_PlayChannel(-1, collect_item, 0);
}

void Sound::changeMap()
{
    Mix_PlayChannel(-1, change_map, 0);
}

void Sound::selectCharacter()
{
    Mix_PlayChannel(-1, select_character, 0);
}

void Sound::unlockCharacter()
{
    Mix_PlayChannel(-1, unlock, 0);
}

void Sound::upgradeCharacter()
{
    Mix_PlayChannel(-1, upgrade, 0);
}

void Sound::mouse_click()
{
    Mix_PlayChannel(-1, click, 0);
}

void Sound::playButton()
{
    Mix_PlayChannel(-1, play_button, 0);
}

void Sound::winGame()
{
    Mix_PlayChannel(-1, win, 0);
}

void Sound::loseGame()
{
    Mix_PlayChannel(-1, lose, 0);
}

void Sound::mobDie()
{
    Mix_PlayChannel(-1, mob_die, 0);
}

void Sound::character_heal()
{
    Mix_PlayChannel(-1, heal, 0);
}

void Sound::bomb_explosion()
{
    Mix_PlayChannel(-1, explosion, 0);
}

void Sound::character_attack(int cur_character)
{
    Mix_PlayChannel(-1, char_attack[cur_character], 0);
}

void Sound::character_move(int type)
{
    if (nextMove == 0) {
        if (type) Mix_PlayChannel(-1, fly, 0);
        else Mix_PlayChannel(-1, walk, 0);
    }
    nextMove++;
    nextMove %= 13;
}

void Sound::character_jump()
{
    Mix_PlayChannel(-1, jump, 0);
}

void Sound::play_boss_audio(int status)
{
    if (bossAudio[status] == NULL) return;
    Mix_PlayChannel(-1, bossAudio[status], 0);
}