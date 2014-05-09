// signalInterrupt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <csignal>
#include <iostream>
#include <string>

volatile std::sig_atomic_t interrupted; //set by sigint; read by main while loop

//signal handler sets a global flag
extern "C" void sigint(int sig)
{
	interrupted = 1;
}

int _tmain(int argc, _TCHAR* argv[])
{

	if (std::signal(SIGINT, sigint) == SIG_ERR)
	{
		std::cerr << "\nCannot set signal handler.\n";
	}
	else
	{
		unsigned long count = 0; //count lines
		while (! interrupted)
		{
			std::cout << "> "; //user prompt
			std::string s;

			if (! std::getline(std::cin,s)) //EOF does not terminate the loop, only SIGINT (CTRL-C)
				//or text SIGINT for raise call
			{
				count++;
			}
			else
			{

				if (s == "SIGINT") 
					{
						if (raise(SIGINT) != 0)
							std::cout << "\nThe SIGINT signal could not be sent (raised).\n";
					}
			}
			std::cin.clear();
		}
		std::cout << "\nI counted " << count << " line(s).\n";
	}

	//pause the output screen
	int x;
	std::cin >> x;
	return 0;
}

