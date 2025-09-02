#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

#include <TBS/System/Simulation.h>
#include <Compatability/SW/Units/HunterFactory.h>
#include <Compatability/SW/Units/SwordsmanFactory.h>
#include <Compatability/SW/Commands/MarchCommandFactory.h>
#include <Compatability/SW/System/EventLogger.h>
#include <Compatability/SW/Common.h>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2) {
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file) {
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	EventLog eventLog;
	acid7beast::tbs::EventLoggerWrapper<EventLog> eventLogWrapper { eventLog };
	acid7beast::tbs::Simulation simulation { eventLogWrapper };

	io::CommandParser parser;
	parser
		.add<io::CreateMap>(
			[&simulation](auto command) {
				printDebug(std::cout, command);
				simulation.CreateWorld(acid7beast::tbs::GetMapSize(command));
			})
		.add<io::SpawnSwordsman>(
			[&simulation](auto command) {
				printDebug(std::cout, command);
				simulation.SpawnUnit(acid7beast::tbs::UnitFactory<io::SpawnSwordsman> { std::move(command) });
			})
		.add<io::SpawnHunter>(
			[&simulation](auto command) {
				printDebug(std::cout, command);
				simulation.SpawnUnit(acid7beast::tbs::UnitFactory<io::SpawnHunter> { std::move(command) });
			})
		.add<io::March>(
			[&simulation](auto command) {
				printDebug(std::cout, command);
				const uint32_t unitId = command.unitId;
				simulation.EnqueueCommand(unitId, acid7beast::tbs::CommandFactory<io::March> { std::move(command) });
			});

	parser.parse(file);
	simulation.Run();

	return 0;
}
