#include "functions.h"
#include "keys.h"

std::string actualInterface = "directories";

void keys(){
	
	while(true){
		char keyPressed = getchar();

		switch(keyPressed){
			case MOVE_DOWN: changeFileChosen(false);
			break;

			case MOVE_UP: changeFileChosen(true);
			break;
			
			case MOVE_RIGHT: moveAroundFiles("forward");
			break;

			case MOVE_LEFT: moveAroundFiles("backward");
			break;

			case SEARCH: searchBar();
			break;
		
			case RENAME_FILE: renameFile();
			break;
			
			case MOVE_FILE: moveFile();
			break;

			case DELETE_FILE: deleteFile();
			break;
		
			case COPY_FILE: copyFile();
			break;
			
			case PASTE_FILE: pasteFile();
			break;
			
			case CREATE_DIR: makeDir();
			break;

			case CREATE_FILE: createFile();
			break;
			
			case SELECT_FILE: selectFiles();
			break;
			
			case CANCEL_SELECT_FILE: cancelSelectFiles();
			break;

			case 'q': system("stty cooked | clear");
				  exit(0);
			break;
		}
	}
}
