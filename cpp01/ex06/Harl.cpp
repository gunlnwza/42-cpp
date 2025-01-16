#include <iostream>
#include "Harl.hpp"

#define DEBUG_MESSAGE \
"I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger." \
" I really do!"

#define INFO_MESSAGE \
"I cannot believe adding extra bacon costs more money." \
" You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"

#define WARNING_MESSAGE \
"I think I deserve to have some extra bacon for free." \
" I've been coming for years whereas you started working here since last month."

#define ERROR_MESSAGE \
"This is unacceptable! I want to speak to the manager now."

#define DEFAULT_MESSAGE \
"Wait. I confused myself!"

void Harl::complain(int level)
{
	switch (level)
	{
		case DEBUG:
			std::cout << "[ DEBUG ]" << std::endl;
			this->debug();
			std::cout << std::endl;
		case INFO:
			std::cout << "[ INFO ]" << std::endl;
			this->info();
			std::cout << std::endl;
		case WARNING:
			std::cout << "[ WARNING ]" << std::endl;
			this->warning();
			std::cout << std::endl;
		case ERROR:
			std::cout << "[ ERROR ]" << std::endl;
			this->error();
			std::cout << std::endl;
			break ;
		default:
			std::cout << DEFAULT_MESSAGE << std::endl;
	}
}

void Harl::debug(void)
{
	std::cout << DEBUG_MESSAGE << std::endl;
}

void Harl::info(void)
{
	std::cout << INFO_MESSAGE << std::endl;
}

void Harl::warning(void)
{
	std::cout << WARNING_MESSAGE << std::endl;
}

void Harl::error(void)
{
	std::cout << ERROR_MESSAGE << std::endl;
}
