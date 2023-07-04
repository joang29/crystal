#include "functions.h"

std::string actualInterface = "directories";

void keys(){
	while(true){
		char keyPressed = getchar();

		switch(keyPressed){
			case 'J':
			case 'j':
			case 'S':
			case 's': actualInterface == "directories" ? changeFileChosen(false) : moveAroundSettings(false);
			break;

			case 'K':
			case 'k':
			case 'W':
			case 'w': actualInterface == "directories" ? changeFileChosen(true) : moveAroundSettings(true);
			break;
			
			case 'L':
			case 'l':
			case 'D':
			case 'd': if(actualInterface == "directories") moveAroundFiles("forward");
			break;

			case 'H':
			case 'h':
			case 'A':
			case 'a': if(actualInterface == "directories") moveAroundFiles("backward");
			break;
			
			case 'Q':
			case 'q': if(actualInterface == "directories"){
				  	showSettings();
				  	actualInterface = "settings";
				  }
			break;
			
			case ' ': if(actualInterface == "settings") changeSettings();
			break;

			case 'E':
			case 'e': if(actualInterface == "settings"){
				  	showFiles(getenv("HOME"));
				  	actualInterface = "directories";
			          }
			break;
		

			case 'X':
			case 'x': system("stty cooked | clear");
				  exit(0);
			break;
		}
	}
}
