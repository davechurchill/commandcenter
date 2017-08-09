# CommandCenter: StarCraft 2 AI Bot

CommandCenter is a StarCraft II playing bot written in C++ using Blizzard's [StarCraft II AI API](https://github.com/Blizzard/s2client-api). It is written by [David Churchill](http://www.cs.mun.ca/~dchurchill/), Assistant Professor of [Computer Science](https://www.cs.mun.ca/) at Memorial University, and organizer of the [AIIDE StarCraft AI Competition](http://www.cs.mun.ca/~dchurchill/starcraftaicomp/).

CommandCenter is based on the architecture of [UAlbertaBot](https://github.com/davechurchill/ualbertabot/wiki), and is intended to be used as a robust, easy to use architecture for you to quickly modify, play with, and build your own bot. The bot itself does not contain much in the way of hard-coded strategy or tactics, however it provides a good starting point for you to implement your own strategies for any race. 

CommandCenter currently provides the following features:
* Plays all 3 races with generalized micro controllers for combat units
* Performs online map analysis, extracting information such as base locations and expansions
* Keeps track of all previously seen enemy units and their last known locations on the map
* Has a WorkerManager which manages resource gathering and worker allocation / buiding
* Is able to carry out predefined build-orders written in a configuration file
* Allows you to easily create your own build-orders and modify them on the fly in-game
* Contains a building placement algorithm, finding the closest buildable location to a given position for a given building 
* Scouts the map with a worker unit, discovering where the enemy base is located
* Once a specific condition has been reached (having 12 combat units, by default), it will commence an attack, sending waves of units at the enemy base
* Squads can be formed, consisting of multiple units following a specific order such as attack or defend a given location

CommandCenter should eventually have all of the functionality of UAlbertaBot, however much of its features are not currently completed. Here is an up-to-date list of features currently missing from CommandCenter that will be implemented soon:
* Only units and basic buildings can be constructed via the ProductionManager. No add-ons, research, or upgrades yet.
* There is no automatic build-order planning system
* There is no combat simulation package for predicting combat battle victory
* The bot only plays 1v1, and will have undefined behavior / crash if played against multiple enemies or on teams

# Download and Run CommandCenter

If you just want to download and run the bot to see it play against the built-in SC2 AI, you can download a pre-compiled version in the release section here: https://github.com/davechurchill/commandcenter/tree/master/release

You must have an up-to-date retail version of StarCraft II installed to run the bot. You must also download and install some maps to use with the bot, which you can find here: https://github.com/Blizzard/s2client-proto#downloads. Please note that to download those maps, you must accept the eula by typing in the password provided.

The bot comes with a configuration file named [BotConfig.txt](https://github.com/davechurchill/commandcenter/blob/master/bin/BotConfig.txt) in which you can modify build orders, print various debug information to the screen, and set some bot parameters. You can define multiple builds orders in the 'Strategies' section of the file, and choose which named strategy to implement when the bot plays a specific race. Unit names in the build-order are case sensitive, and must be exactly how they appear in-game with no spaces. Some of the options in the configuration file are currently not implemented, such as the KiteWithRangedUnits option.

Please note that this config file is in JSON format, and the bot will not run unless it is well-formatted JSON. The configuration file must be in the same directory as CommandCenter.exe in order for the bot to run correctly.

By default when you run CommandCenter.exe, it will play as Random race vs. a Random race built-in SC2 Easy AI. You can modify which races are played in the configuration file via the "BotRace" and "EnemyRace" options. You can also modify which map to be played by specifying the "MapFile" option. Please note that the MapFile option is relative to your StarCraft II maps directory, which by default is located in your StarCraft_Install_Directory/maps/, and the bot will not run without specifying a valid map file.

If the bot crashes or does other nasty things, please bear with me while I make it more stable :)

# Developer Install / Compile Instructions (Windows)

* Download and install [Visual Studio 2017](https://www.visualstudio.com/downloads/)
* Download and install the [StarCraft II AI API](https://github.com/Blizzard/s2client-api). The easiest way to do this is to download the Precompiled Libraries at the bottom of the page, and simply extract them to a folder on your PC
* Clone this git repository to a folder on your PC
* Open "CommandCenter/vs/CommandCenter.sln" in VS2017
* Set the VS Project include and lib folders to point to the SC2API directories
  * Right click the CommandCenter project in VS2017
  * Select "Properties"
  * Select "VC++ Directories" on the left
  * Select the "Include Directories" option in the table on the right
  * Click the dropdown arrow on the right and click Edit...
  * Modify the existing directory entry to point to your SC2API/include directory
  * Select the "Library Directories" option in the table on the right
  * Click the dropdown arrow on the right and click Edit...
  * Modify the existing directory entry to point to your SC2API/lib directory
* From the "Build" menu, click "Build Solution"
* The binary "CommandCenter.exe" should appear in the CommandCenter/bin/ directory
* Run the CommandCenter bot by either:
  * Double clicking the executable in the CommandCenter/bin/ directory
  * Running the program from the console
  * Click "Local Windows Debugger" in VS to launch the program from within VS
* The CommandCenter/bin/BotConfig.txt file must be in the same directory as the .exe to run properly

# Developer Install / Compile Instructions (Linux)

I have not yet had time to build / test CommandCenter on Linux, or write a Makefile for it, but it should work out of the box. If you would like to test the bot in Linux and/or write a makefile for the project, please feel free submit a pull request. 

# Bot Development

If you are familiar with the architecture of UAlbertaBot, the logic of CommandCenter is quite similar. The biggest difference is that information relating to the map, baselocation, etc are no longer globally accessible. This data now lives inside the main CCBot class, and must be accessed via a reference to the instance of that class. Because of this, most classes in CommandCenter carry with them a reference to the bot's main CCBot object, from which all game related information, observations, and queries can be made.

An in-depth development guide will be coming soon, but please refer to the [UAlbertaBot wiki](https://github.com/davechurchill/ualbertabot/wiki) for now since the architecture is so similar (minus the build order planner and combat simulator).
