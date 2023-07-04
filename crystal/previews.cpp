#include<iostream>
#include<string.h>
#include<experimental/filesystem>
#include<fstream>
#include "functions.h"

void showPreviews(std::string, std::string);
std::string determineTerminal();

void showPreviews(std::string preview, std::string fileChosen){
	int i = 0;
	
	std::string terminal = determineTerminal();

	if(preview == "directory"){
		std::array<bool,4> settings = returnSettings();

		std::cout<<"\033["<<2<<";0f";
		std::cout<<"\r\t\t\t\t\t\t\033[1;93mDirectory preview:\033[0m"<<std::endl;

		for(const auto & entry : std::experimental::filesystem::directory_iterator(fileChosen)){
			if(!settings[0] && (entry.path().filename().string())[0] == '.') continue;
			
			std::cout<<"\033["<<3+i<<";0f";
	
			std::cout<<"\r\t\t\t\t\t\t"<<entry.path().filename().string()<<std::endl;
			i++;
			if(i>10) break;
		}
		if(i==0){
			std::cout<<"\033["<<3<<";0f";
			std::cout<<"\r\t\t\t\t\t\t\033[1;31mempty\033[0m"<<std::endl;
		}
	}else if(preview == "textFiles"){
		std::cout<<"\033["<<2<<";0f";
		std::cout<<"\r\t\t\t\t\t\t\033[1;93mFile preview:\033[0m"<<std::endl;

		std::ifstream file(fileChosen);
		while(file.eof()==0){
			std::string line;
			getline(file, line);
			
			std::cout<<"\033["<<3+i<<";0f";		
			
			std::cout<<"\r\t\t\t\t\t\t"<<line<<std::endl;
			i++;
			if(i>10) break;
		}
	}else if(preview == "images"){
		std::cout<<"\033["<<2<<";0f";
		std::cout<<"\r\t\t\t\t\t\t\033[1;93mImage preview:\033[0m"<<std::endl;
		std::cout<<"\r\t\t\t\t\t\t\033[1;31mProcessing...\033[0m"<<std::endl;
				
		if(terminal == "kitty") system(("kitty icat --place 60x60@48x2 '" + fileChosen + "'").c_str());
		else{
			system("tput cup 20 0");
			system(("echo -e '0;1;288;28;350;200;;;;;" + fileChosen + "\n4;\n3;' | /usr/lib/w3m/w3mimgdisplay").c_str());	
		}
	}
}

std::string determineTerminal(){
	FILE *outputFile;
	char output[6];

	outputFile = popen("ps -o 'cmd=' -p $(ps -o 'ppid=')", "r");
	fgets(output, 6, outputFile);
	return output;
}
