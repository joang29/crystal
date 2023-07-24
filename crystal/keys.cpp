#include "functions.h"

std::string actualInterface = "directories";

void keys(){
	
	while(true){
		char keyPressed = getchar();

		switch(keyPressed){
			case 'j': actualInterface == "directories" ? changeFileChosen(false) : moveAroundSettings(false);
			break;

			case 'k': actualInterface == "directories" ? changeFileChosen(true) : moveAroundSettings(true);
			break;
			
			case 'l': if(actualInterface == "directories") moveAroundFiles("forward");
			break;

			case 'h': if(actualInterface == "directories") moveAroundFiles("backward");
			break;
		
			case 'y': if(actualInterface == "directories"){
				  	showSettings();
				  	actualInterface = "settings";
				  }
			break;
			
			case ' ': if(actualInterface == "settings") changeSettings();
			break;

			case 'Y': if(actualInterface == "settings"){
				  	showFiles(getenv("HOME"));
				  	actualInterface = "directories";
			          }
			break;
		
			case 'd': if(actualInterface == "directories") searchBar();
			break;
		
			case 'f': if(actualInterface == "directories") renameFile();
			break;
			
			case 'x': if(actualInterface == "directories") moveFile();
			break;

			case 'X': if(actualInterface == "directories") deleteFile();
			break;
		
			case 'c': if(actualInterface == "directories") copyFile();
			break;
			
			case 'C': if(actualInterface == "directories") pasteFile();
			break;
			
			case 'S': if(actualInterface == "directories") makeDir();
			break;

			case 's': if(actualInterface == "directories") createFile();
			break;
			
			case 'z': if(actualInterface == "directories") selectFiles();
			break;
			
			case 'Z': if(actualInterface == "directories") cancelSelectFiles();
			break;

			case 'q': system("stty cooked | clear");
				  exit(0);
			break;
		}
	}
}
