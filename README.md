OOP Semester 2 Final Project
Dangerous Dave 			
Merit Maita 318338373
Tomer Fisher 205364151
Shahar Aviv 203489307









•	Game Explanation:
A version of the nostalgic game. Dangerous Dave goes out to seek treasure through secret rooms and tunnels. At each stage, you must collect as many diamonds as you can to accumulate more disqualifications. As well as finding the Holy Grail that will allow the door to be opened to the next stage. At your disposal, some of the stages will be equipped with a Jetpack and a gun to help you deal with all the dangers and enemies.

1.	Main.cpp 
The main file that runs the start of the GameManager, pushes a menu state.

2.	Resource Manager
The resources class is in charge of loading and holding all outer files, 
Such as pictures, music’s and fonts.
It is a static Singleton class.

3.	Logger
A singleton static class, the class holds the logger file. The logger file will hold times of major things that happened throughout the program. such as Exceptions, collisions and more.
If the program has ever failed, the logger file will allow us to know the reason.

4.	Bullet, Enemy, PowerUp factories
These classes are each in charge of creating objects.
The class holds a static map which holds a key matching to the proper objects and a pointer to a function which creates the object. Each object is in charge of registering itself to the factory.

5.	GameManager:
The gameManager runs the main game loop.
Generically it calls a set of functions for managing the game.
6.	Menu:
The class represents the main menu of the game.
It holds a vector of pointers that inherit from command,
start, restart, exit, pause.
7.	Animation:
The class represents all objects that move by animation.




8.	MoveAble:
Abstract class which represents the moveable objects.
9.	Enemy:
Abstract class represents a Enemy object
10.	HorizontalEnemy:
Inheritance from Enemy
11.	CircleEnemy
Inheritance from Enemy
12.	Bulleta and Dave
Inheritance from ChangeMove (for Strategy) and Moveable from top

13.	UnMovAble
Abstract class inheritance from GameObject represents objects that don’t move
14.	Water
15.	Enemy
16.	Fire
17.	Door
18.	Wall
19.	Electricity
	
	26. PowerUp
     Abstract class that inherits from GameObject.
	27. Jetpack
	28. Diamond
	29. Gun


Design Patterns: 
20.	ChangeMove Strategy:
Abstract class that represents the Dave’s and bullets movements.
21.	Factory Templets:
For the production of all objects in the game
22.	Singelton:
For the resources class of the game
23.	Command:
Abstract class that represents all buttons in games, has an execute function
24.	Exit
Inherits from command, exits the game….
Help:
Inherits from command, opens a help screen
Start Game
Starting the game
Pause
To pause the game
Restart
Restarting the game



•	Bugs:
Needs to add sfml-audio-d.lib to Properties 
