/**********************************************************************************************/
/*** IFStatus.cpp 	   								    ***/
/*** Reads sysfs to parse network interface status an do something interesting(?) with that ***/
/*** piece of info.									    ***/
/*** Info is read for example from: /sys/class/net/eth0/carrier file, where eth0 is de if.  ***/
/*** Author: MGR (retux) 								    ***/
/*** License: GPL									    ***/
/**********************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

void printUsage(char*);
void printHelp(char*);


int main ( int argc, char* argv[] ) 
{
	//char* myInterface;
	std::string myInterface = "";
	std::string SysFSPath="/sys/class/net/";
	std::string SysFSIFAttr="/carrier";
	std::string SysFSFile = ""; 
	std::string line;
	int IFStatus;
	const string VERSION = "0.1.0";

	//std::cout << "Debug argc=" << argc << endl;
	// BOF: Procesando parametros
	if ( argc < 2 )
	{
		printUsage(argv[0]);
		/*
		std::cout << "Usage: " << argv[0] << " -i <interface>" << endl;
		std::cout << "Example: " << argv[0] << "-i eth0" << endl;
		*/
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
	// BOF: Read SysFS file
	if ( myInterface.size() < 1 )
		{
			std::cerr << "Error: Invalid Interface Name" << endl;
			exit(1);
		}

	SysFSFile.append(SysFSPath);
	SysFSFile.append(myInterface);
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
			std:cerr << "Unable to open file: " << SysFSFile << endl;
			exit (1);
		} 
	// EOF: Read SysFS file
	std::cout << "IFStatus=" << IFStatus << endl;

  return 0;
}


void printUsage (char* progName)
{
	std::cout << "Usage: " << progName << " -i <interface>" << endl;
	std::cout << "Example: " << progName << "-i eth0" << endl;
}

void printHelp (char* progName)
{
	std::cout << progName << " reads SysFS files to get info about a given network interface." << endl;
	std::cout << "Usage: " << progName << " -i <interface>" << endl;
	std::cout << "Example: " << progName << "-i eth0" << endl;
	std::cout << "Available options:" << endl << endl;
	std::cout << "-i <ethX>		Queries information about ethX status." << endl;
	std::cout << "-v		Displays program version number." << endl;
	std::cout << "-h		Displays this help." << endl;	
}
