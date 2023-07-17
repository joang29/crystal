#include<iostream>
#include<experimental/filesystem>
#include<sys/stat.h>
#include<fstream>
#include<math.h>
#include<string.h>
#include<regex>

#include "functions.h"

void showFiles(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);
void searchBar();
void renameFile();
void commandLine(std::string, std::string *);

int numberOfFileChosen = 1;
int stopOutput = 10;
std::string actualDirectory;
std::string fileChosen;
std::string inputSearch = "";

void showFiles(std::string directory){
	system("clear");
	
	int i = 0;
	std::array<bool,4> settings = returnSettings();

	std::cout<<"\033[1;94m  "<<directory<<"\033[0m\n\n";
	std::string selectedFilename;

	for(const auto & entry : std::experimental::filesystem::directory_iterator(directory)){	
		i++;

		if(!settings[0] && (entry.path().filename().string())[0] == '.' || 
		   !inputSearch.empty() && entry.path().filename().string().find(inputSearch) == std::string::npos){
			i--;
			continue;
		}
		if(i>stopOutput || stopOutput-10>i) continue;
		
		std::string filename = entry.path().filename().string();
	
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
		inputSearch == "" ? std::cout<<"\033[1;31m\r  empty \033[0m" : std::cout<<"\033[1;31m\r  Nothing found \033[0m";
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
		
		if(strstr(output, "text") && settings[1]) showPreviews("textFiles", fileChosen);
		else if(strstr(output, "image") && settings[3]) showPreviews("images", fileChosen);

	}else if(s.st_mode & S_IFDIR && settings[2]) showPreviews("directory", fileChosen);
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
	inputSearch = "";
	
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

void searchBar(){
	numberOfFileChosen = 1;
	
	commandLine("search", &inputSearch);

	showFiles(actualDirectory);

	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\r\033[38;5;15m   :search \033[0m\033[38;5;5m"<<inputSearch<<"\033[0m";
}

void renameFile(){
	std::string newName;
	
	commandLine("rename", &newName);

	std::experimental::filesystem::rename(fileChosen, actualDirectory + "/" + newName);
	
	showFiles(actualDirectory);

	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\r\033[38;5;15m   :rename \033[0m\033[38;5;5m"<<inputSearch<<"\033[0m";
}

void deleteFile(){
	std::string Delete;
	
	std::regex removePath("[" + actualDirectory + "]");
	std::string filename = std::regex_replace(fileChosen, removePath, "");
	
	commandLine("Delete '" + filename + "' [Y/n]", &Delete);
	
	if(Delete=="n" || Delete=="N") return;
	
	std::experimental::filesystem::remove(fileChosen);
	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\033[2K";
	std::cout<<"\r   '"<<filename<<"' removed";
}

void commandLine(std::string command, std::string *result){
	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\033[2K";
	std::cout<<"\r\033[38;5;15m   :"<<command<<" \033[0m\033[38;5;5m";	

	system("stty cooked");

	std::cin>>*result;
	
	system("stty raw");
}
