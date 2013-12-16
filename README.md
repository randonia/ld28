LD28
====

This is my code base for Ludum Dare 28. I'll try my best to publish here as 
frequently as possible.

This project is (stupidly) in C++ using SFML. The code base is set up to use 
Microsoft Visual Studio Express 2012 for Windows Desktop.

Ryan Andonian - ryanandonian@gmail.com - @Zambini845 - www.randonia.com

This game requires Visual C++ Redistributable for Visual Studio 2012
http://www.microsoft.com/en-us/download/details.aspx?id=30679

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++ End Tech Description++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++ Begin Game Readme ++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ----------------------------------------------------------------   
=======================================================================
                       Don't Deploy Your Chute
=======================================================================
      A game by Ryan Andonian - @zambini845 - http://randonia.com
    ----------------------------------------------------------------   

Summary:
	Don't Deploy Your Chute is a game about falling. But don't worry, 
	you have a parachute! But just one, so don't go wasting it. The 
	objective of Don't Deploy Your Chute is to get as many points as
	possible without dieing. Once you feel comfortable with the 
	amount of points you have, you can land. Once you land, you end 
	your run and save your points. If you die, you lose all of your 
	points.

How to run the game:
	This game was built using Microsoft Visual Studio Desktop Express,
	but it can be compiled into any system. It is written in C++ and
	uses SFML-2.1 (http://www.sfml-dev.org/).

Windows:
	1) Contained in this zip file are two folders. Debug and Release.
	Unless you have problems running the game, choose Release. 
		Run "DontDeployYourChute.exe"
    
    If you encounter an error that says "Unable start because 
    MSVCR110.dll is missing from your computer." you will have to 
    download and install Visual C++ Redistributable for Visual Studio 2012 
    http://www.microsoft.com/en-us/download/details.aspx?id=30679


Mac/Linux:
	You will have to compile this yourself. I apologize for the trouble,
	but I don't have a Mac and I don't have the time to build one on 
	Linux.


How to Play:
	The goal is to get the highest score. The faster you go, the more points 
	you get. You can also get points by going through the hole in the ground
	at the end of the level (which will start you on the next level) and by
	picking up the bonus objects.

	If you die, your score is lost. If you want to save your score, you must 
	land at the end of the level. You land by deploying your parachute. Keep
	in mind the parachute takes some time to deploy, so you have to plan ahead.
	Also, the parachute will fail 5 seconds after you deploy it, killing you.
	(Hint: Deploy the parachute around when you stop seeing bonuses and spike 
	obstacles)

In-Game Controls:
	[Arrow Key Left/Right] 	- Move Left/Move Right
	[Arrow Key Up/Down]		- Reduce Speed/Increase Speed
	[Space]					- Deploy parachute
	[P]						- Pause Game
	[F]						- Toggle FPS
	[Escape]				- Close game

Other controls will be displayed on screen for menu navigation.