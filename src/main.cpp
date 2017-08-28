#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"
#include "rapidjson/document.h"
#include "JSONTools.h"
#include "Util.h"

#include <iostream>
#include <string>
#include <random>
#include <cmath>

#include "CCBot.h"


int main(int argc, char* argv[]) 
{
    sc2::Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv)) 
    {
        std::cout << "Unable to find or parse settings." << std::endl;
        return 1;
    }
    
    rapidjson::Document doc;
	rapidjson::Document doc2;
    std::string config = JSONTools::ReadFile("BotConfig.txt");
    if (config.length() == 0)
    {
        std::cerr << "Config file could not be found, and is required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";
        exit(-1);
    }
	std::string config2 = JSONTools::ReadFile("BotConfig2.txt");
	if (config2.length() == 0)
	{
		std::cerr << "2nd Config file could not be found, and is required for battling bots\n";
	}

    bool parsingFailed = doc.Parse(config.c_str()).HasParseError();
    if (parsingFailed)
    {
        std::cerr << "Config file could not be parsed, and is required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";
        exit(-1);
    }
	if (config2.length() > 0) {
		parsingFailed = doc2.Parse(config2.c_str()).HasParseError();
		if (parsingFailed)
		{
			std::cerr << "Config file 2 could not be parsed, and is required for starting the bot\n";
			std::cerr << "Please read the instructions and try again\n";
			exit(-1);
		}
	}

    std::string botRaceString;
	std::string bot2RaceString;
    std::string enemyRaceString;
    sc2::Difficulty enemyDifficulty;
    std::string mapString;
    int stepSize = 1;

    if (doc.HasMember("Game Info") && doc["Game Info"].IsObject())
    {
        const rapidjson::Value & info = doc["Game Info"];
        JSONTools::ReadString("BotRace", info, botRaceString);
        JSONTools::ReadString("EnemyRace", info, enemyRaceString);
        JSONTools::ReadInt("EnemyDifficulty", info, enemyDifficulty);
        JSONTools::ReadString("MapFile", info, mapString);
        JSONTools::ReadInt("StepSize", info, stepSize);
		if (config2.length() > 0) {
			JSONTools::ReadString("BotRace", doc2["Game Info"], bot2RaceString);
		}
    }
    else
    {
        std::cerr << "Config file has no 'Game Info' object, required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";
        exit(-1);
    }

    // Add the custom bot, it will control the players.
    CCBot bot;
	CCBot bot2;

	sc2::PlayerSetup player1 = CreateParticipant(Util::GetRaceFromString(botRaceString), &bot);
	sc2::PlayerSetup player2;
	if (config2.length() > 0) {
		bot2.SetConfigFileLocation("BotConfig2.txt");
		player2 = CreateParticipant(Util::GetRaceFromString(bot2RaceString), &bot2);
	}
	else
	{
		player2 = CreateComputer(Util::GetRaceFromString(enemyRaceString), enemyDifficulty);
	}

    
    // WARNING: Bot logic has not been thorougly tested on step sizes > 1
    //          Setting this = N means the bot's onFrame gets called once every N frames
    //          The bot may crash or do unexpected things if its logic is not called every frame
    coordinator.SetStepSize(stepSize);
    coordinator.SetRealtime(false);

    coordinator.SetParticipants({
        player1,
        player2
    });

    // Start the game.
    coordinator.LaunchStarcraft();
    coordinator.StartGame(mapString);

    // Step forward the game simulation.
    while (true) 
    {
        coordinator.Update();
    }

    return 0;
}
