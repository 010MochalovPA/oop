#include "CCarApp.h"

CCarApp::CCarApp(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ 
		  { "Info", [this](const int args) { return Info(args); } },
		  { "EngineOn", [this](const int args) { return EngineOn(args); } },
		  { "EngineOff", [this](const int args) { return EngineOff(args); } },
		  { "SetGear", [this](const int args) { return SetGear(args); } },
		  { "SetSpeed", [this](const int args) { return SetSpeed(args); } }
		})
{
}

bool CCarApp::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream isstream(commandLine);

	std::string action;
	isstream >> action;

	int args = isstream >> args ? args : 0;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}
	

bool CCarApp::EngineOn(const int /*args*/)
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine turn on was successful" << std::endl;
		return true;
	}
	
	m_output << "Engine turn on was falled" << std::endl;
	return false;
}

bool CCarApp::EngineOff(const int /*args*/)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine turn off was successful" << std::endl;
		return true;
	}

	m_output << "Engine turn off was falled" << std::endl;
	return false;
}

bool CCarApp::Info(const int /*args*/)
{
	m_output << "         ⢀⣠⠤⠖⠒⠛⠛⠋⠉⠉⠉⠉⠉⠉⣹⣻⠭⠿⢿⡷⠦⣤⡀    " << std::endl;
	m_output << "      ⢀⣤⠖⠋            ⣼⣳⢯  ⠈⢷⠄⠸⣟⣆   " << std::endl;
	m_output << "   ⢀⣰⠶⠿⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠒⢒⣶⠞⢡⡏⢸⣾⣉⣉⣽⣆⣀⣹⠾⣧  " << std::endl;
	m_output << " ⢀⠞⡏⠁          ⢀⡤⡖⠋⢹⢹⠐⠛⠋⠉⠉⠉⠉⢀⣼⡆ ⠰⠞⡇ " << std::endl;
	m_output << "⢀⡾⠾⠷⠲⣶⣶⣶⣶⣶⣶⣶⠶⠒⠾⠷⠛⠓⠋⠉⠉⣳⣄⣤⡀    ⠁⡇   ⢷⡀" << std::endl;
	m_output << "⢸⠒⠒⠒           ⠐⠒⠚⠛⠉⠉⢩⣿⣿⣷    ⠘⡇  ⣴⣿⡇" << std::endl;
	m_output << "⢸⠺⡗⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄ ⠿⡏⠽⠟  ⣿⣿⣿⣿⡆⠴⠶⠶⠖⠓⠂ ⣿⣿⡇" << std::endl;
	m_output << "⠸⣧⣤⣤⣭⣭⣭⣭⣭⣭⣭⣭⣭⣤⣤⣤⣤⣤⣄⣠⣤⣿⣻⣿⣿⣧⣤⣤⣤⣤⣤⣤⣬⣿⣿⠇" << std::endl;
	m_output << "⠈⠻⣿⣿⡿⠟⠁       ⠘⠿⠿⠿⠙⢿⣿⣿⡿⠏      ⠻⣿⣿⠟  " << std::endl;
	m_output << " State Engine is: " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl;
	m_output << " Speed is: "<< m_car.GetSpeed() << std::endl;
	m_output << " Gear is: " << ConvertGearToInt(m_car.GetGear()) << std::endl;
	m_output << " direction is: " << ConvertDirectionToString(m_car.GetDirection()) << std::endl;

	return true;
}

int CCarApp::ConvertGearToInt(const CCar::Gear& gear)
{
	switch (gear)
	{
		case CCar::Gear::REVERSE: return -1;
		case CCar::Gear::NEUTRAL: return 0;
		case CCar::Gear::FIRST:   return 1;
		case CCar::Gear::SECOND:  return 2;
		case CCar::Gear::THIRD:   return 3;
		case CCar::Gear::FOURTH:  return 4;
		case CCar::Gear::FIFTH:   return 5;
	}
}

CCar::Gear CCarApp::ConvertIntToGear(const int gear)
{
	switch (gear)
	{
		case -1: return CCar::Gear::REVERSE;
		case 0:  return CCar::Gear::NEUTRAL;
		case 1:  return CCar::Gear::FIRST;
		case 2:  return CCar::Gear::SECOND;
		case 3:  return CCar::Gear::THIRD;
		case 4:  return CCar::Gear::FOURTH;
		case 5:  return CCar::Gear::FIFTH;
	}
}

std::string CCarApp::ConvertDirectionToString(const CCar::Direction& d)
{
	switch (d)
	{
		case CCar::Direction::FORWARD: return "forward";
		case CCar::Direction::BACK:    return "backward";
		case CCar::Direction::STAY:    return "standing still";
	}
}

bool CCarApp::SetGear(const int arg)
{
	const CCar::Gear gear = ConvertIntToGear(arg); 
	if (m_car.SetGear(gear))
	{
		m_output << "Current gear is " << arg << std::endl;
		return true;
	}
	m_output << "Set speed was falled!" << std::endl;
	return true;
}

bool CCarApp::SetSpeed(const int args)
{
	if (m_car.SetSpeed(args))
	{
		m_output << "Current speed is " << args << std::endl;
		return true;
	}
	m_output << "Set speed was falled!" << args << std::endl;
	return true;
}










