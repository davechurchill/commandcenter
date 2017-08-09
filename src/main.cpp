#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"

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

    coordinator.SetRealtime(false);

    // WARNING: Bot logic has not been thorougly tested on step sizes > 1
    //          Setting this = N means the bot's onFrame gets called once every N frames
    //          The bot may crash or do unexpected things if its logic is not called every frame
    coordinator.SetStepSize(1);

    // Add the custom bot, it will control the players.
    CCBot bot;

    sc2::Race botRace = sc2::Race::Random;
    sc2::Race enemyRace = sc2::Race::Random;

    if (argc > 1)
    {
        if (std::string(argv[1]) == "Protoss")      { botRace = sc2::Race::Protoss; }
        else if (std::string(argv[1]) == "Zerg")    { botRace = sc2::Race::Zerg;    }
        else if (std::string(argv[1]) == "Terran")  { botRace = sc2::Race::Terran;  }
        else if (std::string(argv[1]) == "Random")  { botRace = sc2::Race::Random;  }
    }

    if (argc > 2)
    {
        if (std::string(argv[2]) == "Protoss")      { enemyRace = sc2::Race::Protoss; }
        else if (std::string(argv[2]) == "Zerg")    { enemyRace = sc2::Race::Zerg;    }
        else if (std::string(argv[2]) == "Terran")  { enemyRace = sc2::Race::Terran;  }
        else if (std::string(argv[2]) == "Random")  { enemyRace = sc2::Race::Random;  }
    }

    coordinator.SetParticipants({
        CreateParticipant(botRace, &bot),
        CreateComputer(enemyRace)
    });

    // Start the game.
    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);

    // Step forward the game simulation.
    while (true) 
    {
        coordinator.Update();
    }

    return 0;
}
