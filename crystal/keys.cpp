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
			
			case 'A':
			case 'a': if(actualInterface == "directories"){
				  	showSettings();
				  	actualInterface = "settings";
				  }
			break;
			
			case ' ': if(actualInterface == "settings") changeSettings();
			break;

			case 'S':
			case 's': if(actualInterface == "settings"){
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

			case 'X':
			case 'x': system("stty cooked | clear");
				  exit(0);
			break;
		}
	}
}
