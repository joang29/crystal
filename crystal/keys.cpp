#include "functions.h"

std::string actualInterface = "directories";

void keys(){
	while(true){
		char keyPressed = getchar();

		switch(keyPressed){
			case 'J':
			case 'j': actualInterface == "directories" ? changeFileChosen(false) : moveAroundSettings(false);
			break;

			case 'K':
			case 'k': actualInterface == "directories" ? changeFileChosen(true) : moveAroundSettings(true);
			break;
			
			case 'L':
			case 'l': if(actualInterface == "directories") moveAroundFiles("forward");
			break;

			case 'H':
			case 'h': if(actualInterface == "directories") moveAroundFiles("backward");
			break;
			
			case 'Y':
			case 'y': if(actualInterface == "directories"){
				  	showSettings();
				  	actualInterface = "settings";
				  }
			break;
			
			case ' ': if(actualInterface == "settings") changeSettings();
			break;

			case 'U':
			case 'u': if(actualInterface == "settings"){
				  	showFiles(getenv("HOME"));
				  	actualInterface = "directories";
			          }
			break;
		
			case 'D':
			case 'd': if(actualInterface == "directories") searchBar();
			break;
			
			case 'F':
			case 'f': if(actualInterface == "directories") renameFile();
			break;
			
			case 'Z':
			case 'z': if(actualInterface == "directories") deleteFile();
			break;
			
			case 'C':
			case 'c': if(actualInterface == "directories") copyFile();
			break;
			
			case 'V':
			case 'v': if(actualInterface == "directories") pasteFile();
			break;
			
			case 'X':
			case 'x': if(actualInterface == "directories") makeDir();
			break;

			case 'A':
			case 'a': if(actualInterface == "directories") createFile();
			break;

			case 'Q':
			case 'q': system("stty cooked | clear");
				  exit(0);
			break;
		}
	}
}
