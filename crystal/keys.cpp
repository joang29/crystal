#include "configuration.h"
#include "fileManager.h"
#include<iostream>
#include<unordered_map>

void keys(){
	std::unordered_map<std::string,unsigned int> keys = loadConfig("keys");
	
	int move_down = 'a';

	while(true){
		int keyPressed = getchar();
			
		if(keyPressed == keys.at("move_down")){ changeFileChosen(false); continue;}

		if(keyPressed == keys.at("move_up")){ changeFileChosen(true); continue;}
			
		if(keyPressed == keys.at("move_right")){ moveAroundFiles("forward"); continue;}

		if(keyPressed == keys.at("move_left")){ moveAroundFiles("backward"); continue;}

		if(keyPressed == keys.at("search")){ searchBar(); continue;}
		
		if(keyPressed == keys.at("rename_file")){ renameFile(); continue;}
			
		if(keyPressed == keys.at("move_file")){ moveFile(); continue;}

		if(keyPressed == keys.at("delete_file")){ deleteFile(); continue;}
		
		if(keyPressed == keys.at("copy_file")){ copyFile(); continue;}
			
		if(keyPressed == keys.at("paste_file")){ pasteFile(); continue;}
			
		if(keyPressed == keys.at("create_dir")){ makeDir(); continue;}

		if(keyPressed == keys.at("create_file")){ createFile(); continue;}
			
		if(keyPressed == keys.at("select_file")){ selectFiles(); continue;}
		
		if(keyPressed == keys.at("cancel_select_file")){ cancelSelectFiles(); continue;}
		
		if(keyPressed == 63){help(); continue;}

		if(keyPressed == keys.at("close")){			
			 system("stty cooked | clear");
			 exit(0);
		}
	}
}
