/**********************************************************************************************/
/*** gpiopinctrl.cpp 	   								    ***/
/*** Turn individual GPIO pin on/off using SysFS					    ***/
/***											    ***/
/*** This program is a client which uses GPIOClass(es) designed by Hussam Al-Hertani 	    ***/
/*** 	https://github.com/halherta/RaspberryPi-GPIOClass-v1				    ***/
/*** 	More info about see: GPIOClass.h						    ***/
/*** Author: MGR (retux) 								    ***/
/***											    ***/
/*** License: GPL									    ***/
/*** This program is provided as it is, so use it at your own risk.		 	    ***/
/*** Using GPIO pins you must be carefull.						    ***/
/*** Important GPIO4 is used as output, meaning 0 is network interface out, 1 for ok.	    ***/
/*** Remember: this program need to be run as root.					    ***/
/**********************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "GPIOClass.h"
#include <signal.h>
#include <errno.h>

using namespace std;

void printHelp(char*);


int main ( int argc, char* argv[] ) 
{
	const string VERSION = "0.1.0";
	std::string GPIO_pin = "";
	std::string State = "";

	// BOF: Procesando parametros
	if ( argc < 2 )
	{
		printHelp(argv[0]);
		exit(1);
	}

	for (int i=1; i<argc; i++)
		{
			if ( strcmp(argv[i], "-h") == 0 )
				{
					printHelp(argv[0]);
					exit (0);
				}
			if ( strcmp(argv[i], "-v") == 0 )
				{
					std::cout << argv[0] << " version: " << VERSION << endl;
					exit (0);
				}
			else if ( (i+1) <= argc && argc == 3 )	
			{
				GPIO_pin = argv[1];
				State = argv[2];	
			}
		}
	// EOF: Procesando parametros

	if ( ( GPIO_pin.length() >= 1 ) && ( State.length() >= 1 ) )
		{
			GPIOClass* gpioN = new GPIOClass(GPIO_pin);
			gpioN->export_gpio();
			gpioN->setdir_gpio("out");
			gpioN->setval_gpio(State);
			delete gpioN;
		
		}
	else
		{
			std::cerr << "Both pin number and state must be provided." << endl;
		}
        return 0;
}



void printHelp (char* progName)
{
	std::cout << progName << " Uses SysFS files to turn on/off a given GPIO pin number." << endl;
	std::cout << "Usage: " << progName << " GPIOPIN <state>" << endl;
	std::cout << endl;
	std::cout << "  put GPIO pin into <state> where <state is 0 or 1." << endl;
	
	std::cout << "Examples: " << progName << " 17 1" << endl;
	std::cout << "   Will turn GPIO pin 17 into 1, previously exporting it and setting direction out." << endl;
	std::cout << endl;
	std::cout << "-v		Displays program version number." << endl;
	std::cout << "-h		Displays this help." << endl;	
}


