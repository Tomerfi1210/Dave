#include "Sound.h"
//=============================================================================
Sound::Sound()
	:m_mute(false)
{
	m_buffer[0].loadFromFile("Sounds\\gameOver.wav");
	m_buffer[1].loadFromFile("Sounds\\menuButton.wav");
	m_buffer[2].loadFromFile("Sounds\\click.wav");
	m_buffer[3].loadFromFile("Sounds\\lose.wav");
	m_buffer[4].loadFromFile("Sounds\\win.wav");
	
	for (int i = 0; i < N; i++) {
		m_audios[i].setBuffer(m_buffer[i]);
		m_audios[i].setVolume(30);
	}
	
}
//=============================================================================

Sound::~Sound()
{
}
//=============================================================================
void Sound::playMenu()
{
		m_audios[1].play();
}
//=============================================================================
void Sound::playClick()
{
		m_audios[2].play();
}
//=============================================================================
void Sound::playLose()
{
		m_audios[3].play();
}
//=============================================================================
void Sound::playWin()
{
		m_audios[4].play();
}
//=============================================================================
void Sound::playOver()
{
		m_audios[0].play();
}
//=============================================================================
void Sound::setSound()
{
	m_mute = !m_mute;
}
//=============================================================================
bool Sound::mute()
{
	return m_mute;
}

