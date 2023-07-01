#include <cstdio>
#include<string>
#include<iostream>
#include<unistd.h>
#include<experimental/filesystem>
#include<sys/stat.h>
#include<string.h>
#include<fstream>
#include<sys/ioctl.h>
#include<math.h>

#include "functions.h"

int numberOfFileChosen = 1;
int stopOutput = 10;
std::string actualDirectory;
std::string fileChosen;

void showFiles(std::string);
void showPreviews(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);

void showFiles(std::string directory){
	system("clear");

	int i = 0;
	std::array<bool,4> settings = returnSettings();

	std::cout<<"\033[1;94m  "<<directory<<"\033[0m\n\n";
	std::string selectedFilename;

	for(const auto & entry : std::experimental::filesystem::directory_iterator(directory)){	
		i++;
		
		if(!settings[0] && (entry.path().filename().string())[0] == '.'){
			i--;
			continue;
		}
		if(i>stopOutput || stopOutput-10>i) continue;
		
		std::string filename = entry.path().filename().string();
	
		if(filename.length() > 30) filename = filename.substr(0,30) + "...";

		if(numberOfFileChosen == i){
			std::cout<<"\033[1;95m\r > "<<filename<<"\033[0m"<<std::endl;
			
			fileChosen = entry.path();
			selectedFilename = entry.path().filename().string();
		}

		else std::cout<<"\r   "<<filename<<std::endl;
	}
	actualDirectory = directory;
	
	if(i==0){
	 	std::cout<<"\033["<<3<<";0f";
		std::cout<<"\033[1;31m\r  empty \033[0m";
		return;
	}
	if(numberOfFileChosen>i){
		numberOfFileChosen=i; 
		return;
	}
	std::cout<<"\033["<<15<<";0f";

	struct stat s;
	stat(fileChosen.c_str(), &s);	

	FILE *outputFile;
	char permissions[11];

	outputFile = popen(("ls -l " + actualDirectory + " | grep '" + selectedFilename + "'").c_str(), "r");
	fgets(permissions, sizeof(permissions), outputFile);
	
	std::cout<<"\r   \033[1;92m"<<permissions<<"\033[0m";
	std::cout<<"\033[1;36m\r\t\t\t\t\t"<<numberOfFileChosen<<"/"<<i<<"\033[0m";
	
	if(s.st_mode & S_IFLNK){
		char output[100];	

		double fileSize = s.st_size;
		
		std::array<std::string, 4> sizes = {"B", "K", "M", "G"};
		int size = 0;

		while(fileSize >= 1024){
			fileSize /= 1024;
			size++;
			if(size>4) break;
		}
	
		std::cout<<"\r\t\t      \033[1;92m"<<round(fileSize * 100) / 100<<sizes[size]<<"\033[033m";

		outputFile = popen(("file '" + fileChosen + "'").c_str(), "r");
		fgets(output, sizeof(output), outputFile);
		
		if(strstr(output, "text") && settings[1]) showPreviews("textFiles");
		else if(strstr(output, "image") && settings[3]) showPreviews("images");

	}else if(s.st_mode & S_IFDIR && settings[2]) showPreviews("directory");
}
void showPreviews(std::string preview){
	int i = 0;
		
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
		
		system(("kitty icat --place 60x60@48x2 " + fileChosen).c_str());
	}
}

void changeFileChosen(bool up){
	if(up == false){
		numberOfFileChosen++;
		if(numberOfFileChosen >= stopOutput-1) stopOutput++;
	
	}else if(numberOfFileChosen != 1){	
		numberOfFileChosen--;
		if(numberOfFileChosen <= stopOutput-9) stopOutput--;
	}
	showFiles(actualDirectory);
}

void moveAroundFiles(std::string forwardOrBackward){
	numberOfFileChosen = 1;
	stopOutput = 10;
	if(forwardOrBackward == "forward"){
		struct stat s;
		stat(fileChosen.c_str(), &s);
		if(s.st_mode & S_IFDIR) showFiles(fileChosen);
		else{
		 system(("xdg-open " + fileChosen + "&").c_str());
		}
	}else if(forwardOrBackward == "backward"){
		std::experimental::filesystem::path file = actualDirectory;
		showFiles(file.parent_path());
	}
}
