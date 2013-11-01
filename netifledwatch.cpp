/**********************************************************************************************/
/*** netifwatch.cpp 	   								    ***/
/*** Reads sysfs to parse network interface status an do something interesting(?) with that ***/
/*** piece of info.									    ***/
/*** Info is read for example from: /sys/class/net/eth0/carrier file, where eth0 is de if.  ***/
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
// For daemonizing
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void printHelp(char*);
void daemonstart(string);
void showifstatus(string);
int getifstatus(string);

void sig_handler(int sig);
bool ctrl_c_pressed = false;


int main ( int argc, char* argv[] ) 
{
	const string VERSION = "0.1.0";
	std::string myInterface = "";

	//std::cout << "Debug argc=" << argc << endl;
	// BOF: Procesando parametros
	if ( argc < 2 )
	{
		printHelp(argv[0]);
		exit(1);
	}
	for (int i=1; i<argc; i++)
		{
			if ( (i+1) <= argc )	
			{
				if ( strcmp(argv[i], "-i") == 0 )
					{
						if ( (i+1) <= (argc-1) ) // important, to avoid "segment violation" if user enter less params	
							{
								myInterface = argv[i+1];				
							}
						if ( myInterface.size() < 1 )
							{
								std::cerr << "Error: Invalid Interface Name" << endl;
								exit(1);
							}

						// Additional params (-s show status or -d initializes monitoring
						if ( (i+2) <= (argc-1) )
							{
								if ( strcmp(argv[i+2], "-s" ) == 0 )
									{
										showifstatus (myInterface);
									}
								else if ( strcmp(argv[i+2], "-d" ) == 0 )  
									{
										daemonstart (myInterface);	
									}
							}

					}
				else if ( strcmp(argv[i], "-v") == 0 )
					{
						std::cout << argv[0] << " Version: " << VERSION << endl;
						std::cout << "Author: Retux. e-mail: matiasgutierrezreto@gmail.com" << endl;
						exit(0);
					}
				else if ( strcmp(argv[i], "-h") == 0 )
					{
						 printHelp(argv[i]);
					
					}
			}

		}
	// EOF: Procesando parametros
	  return 0;
}



void printHelp (char* progName)
{
	std::cout << progName << " reads SysFS files to get info about a given network interface." << endl;
	std::cout << "Usage: " << progName << " -i <interface> -d | -s" << endl;
	std::cout << endl;
	std::cout << "Examples: " << progName << "-i eth0 -s" << endl;
	std::cout << "Will show status of interface eth0" << endl;
	std::cout << "Examples: " << progName << "-i eth0 -d" << endl;
	std::cout << "Will start monitoring on interface eth0" << endl;
	std::cout << endl;
	std::cout << "Available options:" << endl << endl;
	std::cout << "-i <ethX>		Queries information about ethX status." << endl;
	std::cout << "-v		Displays program version number." << endl;
	std::cout << "-d		Starts monitoring on interface ethX (daemon mode)." << endl;
	std::cout << "-s		Shows interface ethX status and exits." << endl;
	std::cout << "-h		Displays this help." << endl;	
}

void showifstatus (string ifname)
{
	std::string SysFSPath="/sys/class/net/";
	std::string SysFSIFAttr="/carrier";
	std::string SysFSFile = ""; 
	std::string line;
	int IFStatus;

	SysFSFile.append(SysFSPath);
	SysFSFile.append(ifname);
	SysFSFile.append(SysFSIFAttr);
	//std::cout << "Debug SysFSFile=" << SysFSFile << endl;
	ifstream myFile (SysFSFile.c_str());
	if (myFile.is_open())
		{
			while ( getline (myFile,line) )
			{
		 	   	std::istringstream iss(line); 
				iss >> IFStatus;
			}
			
		    myFile.close();
	  	}
	  else 
	  	{
			std::cerr << "Unable to open file: " << SysFSFile << endl;
			exit (1);
		} 
	// EOF: Read SysFS file
	std::cout << "IFStatus=" << IFStatus << endl;

}

int getifstatus (string ifname)
{
	std::string SysFSPath="/sys/class/net/";
	std::string SysFSIFAttr="/carrier";
	std::string SysFSFile = ""; 
	std::string line;
	int IFStatus;

	SysFSFile.append(SysFSPath);
	SysFSFile.append(ifname);
	SysFSFile.append(SysFSIFAttr);
	//std::cout << "Debug SysFSFile=" << SysFSFile << endl;
	ifstream myFile (SysFSFile.c_str());
	if (myFile.is_open())
		{
			while ( getline (myFile,line) )
			{
		 	   	std::istringstream iss(line); 
				iss >> IFStatus;
			}
			
		    myFile.close();
	  	}
	  else 
	  	{
			std::cerr << "Unable to open file: " << SysFSFile << endl;
			exit (1);
		} 
	// EOF: Read SysFS file
	return IFStatus;
}




void daemonstart (string ifname)
{
	// BOF: daemon test
	pid_t pid, sid;
	
	// Fork parent process
	pid = fork();

	if ( pid < 0 )
		{
			exit(EXIT_FAILURE);
		}
	if ( pid > 0 )
		{
			// we got the pid, close parent process
			exit(EXIT_SUCCESS);
		}

	// Change umask
	umask(0);
	//Create a new Signature Id for our child
	sid = setsid();
	if (sid < 0)
		{
			exit(EXIT_FAILURE); 
		}

	 //Change Directory
	//If we cant find the directory we exit with failure.
	if ((chdir("/")) < 0)
		{
			exit(EXIT_FAILURE); 
		}

	//Close Standard File Descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// EOF: daemon tezt


	// Old function:
	const string PINOUTUSED = "4";		// GPIO pin used as output to led

	// Signal handling stuff
	struct sigaction sig_struct;
        sig_struct.sa_handler = sig_handler;
        sig_struct.sa_flags = 0;
        sigemptyset(&sig_struct.sa_mask);

        if (sigaction(SIGINT, &sig_struct, NULL) == -1)
		{
                	cout << "Problem with sigaction" << endl;
	                exit(1);
	        }



	GPIOClass* gpio4 = new GPIOClass(PINOUTUSED);
	// "Exports" PINOUTUSED for using
	gpio4->export_gpio();
	// Set PINOUTUSED direction
	gpio4->setdir_gpio("out");

	//gpio4->setval_gpio("1");
	//sleep(2);
	//gpio4->setval_gpio("0");

	while (true)
		{
			if ( getifstatus (ifname) == 1 )
				{
					gpio4->setval_gpio("1");
				}
			else
				{
					gpio4->setval_gpio("0");
				}

			// SIGNAL handling stuff
			if(ctrl_c_pressed)
				{
					std::cout << "SIGINT received." << endl;
					std::cout << "unexporting pins." << endl;
					gpio4->setval_gpio("0");
					gpio4->unexport_gpio();
					std::cout << "deallocating GPIO Objects." << endl;
					delete gpio4;
					gpio4 = NULL;
					break;		// descomentar cuando este el loop
				}
			usleep (500000); 	// half a second nap
		} // EOF: main loop


	//cout << "Debug iniciando interface " << ifname << endl;
}


void sig_handler(int sig)
{
        write(0,"\nCtrl^C pressed in sig handler\n",32);
        ctrl_c_pressed = true;
}

