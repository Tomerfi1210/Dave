#pragma once


const int MENU_WIDTH = 1024;
const int MENU_HEIGHT = 800;
const int END_WIDTH = 1400;
const int END_HEIGHT = 800;
const int LIVES = 3;

enum Direction_t
{
	Right = 1,
	Left = -1,
	Max_d
};

namespace Textures {
	enum Chars_t
	{
		Dave_c = '/',//0
		Gun_c = '-', //1
		Line_Guard_c = '%', //1
		Circle_Guard_c = '!', //1
		Rock_c = '@', //2
		Wall_c = '#', //3
		Door_c = 'D', //4
		Default_Bullet_c = '*', //5
		Lighting_c = '$',
		Speed_c = '&',
		Gift_c = '+',
		Jet_Pack_c = 'j',
		Fire_c = 'f',
		Water_c = 'w',
		Electricity_c = 'e',
		Enemy_Bullet_c = 'q',
		Max_c
	};
}

enum Object_t
{
	Dave_Regular_type,//0
	Dave_jump_Right,//1
	LineGuard_type, //1
	CircleGuard_type, //2
	Rock_type, //3
	Wall_type, //4
	Door_type, //5
	Gun_type, //6
	Bullet_type, //7
	Gifts_type, //8
	Back_gift_type, //9
	Dave_jump_Left, //11
	Dave_JetPack_type,
	JetPack_type,
	Fire_type,//14
	Water_type,//15
	Electricity_type,//16
	Explode_type,
	Enemy_Bullet_type,//18
	Max
};


enum Photo_t
{
	StartingMenu_b,
	StartButton_b,
	ExitButton_b,
	ResumeButton_b,
	HelpButton_b,
	Play_b,
	Pause_b,
	Restart_b,
	Win_b,
	Max_b
};


enum butType_t {
	START_T, 
	EXIT_T,

	CONTINUE_T = 10,
	SOUND_ON_T,
	EXIT_GAME_T,

	RESTART_T = 20,
	LEAVE_T
};