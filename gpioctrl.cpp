/**********************************************************************************************/
/*** gpioctrl.cpp 	   								    ***/
/*** This programs adds generic features to gpiopinctrl which was quite restricted	    ***/
/*** Keeps using kernel API (/sysfs/class/gpio) to control GPIO				    ***/
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
int ExportPin(string);
int UnExportPin(string);
int SetDirection(string, string);
int WriteOnPin(string, string);

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
			if ( strcmp(argv[i], "-x" ) ==0 || strcmp(argv[i], "--export") == 0 || strcmp(argv[i], "-w") == 0  || strcmp(argv[i], "--write") == 0 || strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--unexport") == 0 || strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--direction") == 0  )
				{
					if ( (i+1) <= argc )
						{
							GPIO_pin = argv[i+1];	
						}
					if ( strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--export") == 0 )
						{
							ExportPin(GPIO_pin);
						}
					if ( strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--unexport") == 0 )
						{
							UnExportPin(GPIO_pin);
						}
					if ( strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--direction") == 0 )
						{
							if ( (i+2) <= argc )
								{
									if ( strcmp(argv[i+2], "in") == 0 || strcmp(argv[i+2], "out") ==0 )
										{
											if ( SetDirection(GPIO_pin, argv[i+2]) < 0 )
												{
													std::cerr << "Error when setting direction! " << endl;
													exit (1);
												}
											else
												{
													std::cout << "OK setted pin " << GPIO_pin << " for " << argv[i+2] << endl;
													exit (0);
												}
										}
									else 
										{
											std::cerr << "Error: wether in or out must be provided to set pin direction." << endl;
											exit (1);
										}
								}
						}


					
 					if ( strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--write") == 0 )
						{
							if ( (i+2) <= argc )
								{
									WriteOnPin( GPIO_pin, argv[i+2] );
								}	
							else
								{
									std::cerr << "Error, <state> (0 or 1) must be provided after -w option" << endl;
								}
						}
					
				}
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
	std::cout << "-x <GPIOPIN>	--export <GPIOPIN> exports a given GPIOPIN." << endl;
	std::cout << "-u <GPIOPIN> | all> --UnExportPin <GPIOPIN> UnExportPins a given GPIOPIN." << endl;
	std::cout << "-d <in | out> --direction <in | out> Set direction for input or output." << endl;
	std::cout << "-w <GPIOPIN> <state>	Puts a given GPIOPIN number either to 0 or 1 state." << endl;
}

int ExportPin(string pinno)
{	
	int res = -1;
	GPIOClass* gpioN = new GPIOClass(pinno);
	res = gpioN->export_gpio();
	delete gpioN;
	return res;
}


int UnExportPin(string pinno)
{	
	int res = -1;
	GPIOClass* gpioN = new GPIOClass(pinno);
	res = gpioN->unexport_gpio();
	delete gpioN;
	return res;
}

int SetDirection(string pinno, string direction)
{
	int res = -1;
	GPIOClass* gpioN = new GPIOClass(pinno);
	res = gpioN->setdir_gpio(direction);
	delete gpioN;
	return res;

}

int WriteOnPin(string pinno, string state)
{
	int res = -1;
	GPIOClass* gpioN = new GPIOClass(pinno);
	res = gpioN->setval_gpio(state);
	delete gpioN;
	return res;
}
