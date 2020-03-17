#pragma once
//========================================include==============================
#include <SFML/Audio.hpp>
const int N = 5;
class Sound
{
	//---------------------------public------------------------------
public:
	Sound();
	~Sound();
	//play the sound of buttons in the menu
	void playMenu();
	//the sound of enter in the menu
	void playClick();
	//plays when the payer wins
	void playWin();
	//playes when the player loses
	void playLose();
	//plays when the game is over
	void playOver();
	//it sets the sounds if mute or not
	void setSound();
	//returns if its mute
	bool mute();
	//------------------------private-------------------------------
private:
	sf::SoundBuffer m_buffer[N];
	sf::Sound m_audios[N];
	bool m_mute;
};

