#include<iostream>
#include <stdexcept>
#include <string>
#include<sys/stat.h>
#include<fstream>
#include<array>
#include<math.h>
#include<string.h>
#include <unordered_map>
#include<unistd.h>

#include "previews.h"
#include "configuration.h"
#include "icons.h"

void showFiles(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);
void createNewTab();
void closeTab();
void moveAroundTabs(std::string);
void searchBar();
void renameFile();
void copyFile();
void pasteFile();
void commandLine(std::string, std::string *);

int numberOfFileChosen = 1, stopOutput = 10, numberOfFiles = 0, actualTab = 1, numberOfTabs = 0;
std::string actualDirectory, selectedFilename, inputSearch = "";
std::experimental::filesystem::path fileChosen;
std::vector<std::experimental::filesystem::directory_entry> filesSelected,  copiedFile, filesToMove;
bool selectingFiles = true;
std::array<std::experimental::filesystem::path, 2> rangeSelect;
std::vector<std::string> tabs;

std::unordered_map<std::string, unsigned int> config = loadConfig("general");
std::unordered_map<std::string, unsigned int> colorscheme = loadConfig("colorscheme");

void showTabs(){
	std::cout<<"\033[0;0f   | ";

	for(int i = 0; i<tabs.size(); i++){
		if(actualTab-1==i){
			std::cout<<"\033[38;5;"<<colorscheme.at("actual_tab")<<"m"<<std::experimental::filesystem::path(tabs.at(i)).filename().string()<<"\033[0m | "; 
			continue;
		}

		std::cout<<"\033[38;5;"<<colorscheme.at("tabs")<<"m"<<std::experimental::filesystem::path(tabs.at(i)).filename().string()<<"\033[0m | ";
	}
}

void showFiles(std::string directory){
	system("clear");

	int i = 0;
	bool validEntry = false;
	std::cout<<"\r\033[2;0f\033[38;5;"<<colorscheme.at("directory_name")<<"m  "<<directory<<"\033[0m\n\n";

	try{
		for(const auto & entry : std::experimental::filesystem::directory_iterator(directory)){	
			i++;
		
			if(config.at("hidden_files")==1 && (entry.path().filename().string())[0] == '.' || 
				!inputSearch.empty() && entry.path().filename().string().find(inputSearch) == std::string::npos){
				i--;
				continue;
			}
			if(i>stopOutput || stopOutput-10>i) continue;
	
			std::string filename = entry.path().filename().string();
				
			if(filename.length()>40) filename.resize(40);

			if(selectingFiles){	
				if(entry.path() == rangeSelect[0] || entry.path() == rangeSelect[1]){
						validEntry = !validEntry;
						if(!validEntry) filesSelected.push_back(entry);
				}
				if(validEntry) filesSelected.push_back(entry);
			}
			if(numberOfFileChosen == i || validEntry){ 
				try{
					std::cout<<"\r   \033[48;5;"<<colorscheme.at("selected_file_background")<<"m                                           \033[0m";
					std::cout<<"\r \033[48;5;"<<colorscheme.at("selected_file_background")<<"m\033[38;5;"<<colorscheme.at("selected_file")<<"m  "<<returnIcon(entry.path())<<filename<<"\033[0m"<<std::endl;
				}catch(std::out_of_range){
					std::cout<<"\033[0m\r\033[38;5;"<<colorscheme.at("selected_file")<<"m > "<<returnIcon(entry.path())<<filename<<"\033[0m"<<std::endl;
				}
				fileChosen = entry.path();
				selectedFilename = entry.path().filename().string();
			}
			else std::cout<<"\r \033[38;5;"<<colorscheme.at("unselected_files")<<"m  "<<returnIcon(entry.path())<<filename<<"\033[0m"<<std::endl;
	}
	}catch(std::experimental::filesystem::__cxx11::filesystem_error){std::cout<<"\033[38;5;"<<colorscheme.at("error")<<"m\r  Not user accessible \033[0m"; actualDirectory=directory; return;}
	actualDirectory = directory;
	tabs.at(actualTab-1) = actualDirectory;

	if(i==0){
		std::cout<<"\033["<<3<<";0f";
		inputSearch == "" ? std::cout<<"\033[38;5;"<<colorscheme.at("error")<<"m\r  empty \033[0m" : std::cout<<"\033[1;31m\r  Nothing found \033[0m";
		return;
	}
	if(numberOfFileChosen>i){
		numberOfFileChosen=i; 
		return;
	}
	showTabs();

	std::cout<<"\033[16;0f";

	numberOfFiles = i;

	struct stat s;
	stat(fileChosen.c_str(), &s);	

	FILE *outputFile;
	char permissions[11];
	
	std::string option = config.at("hidden_files")==1 ? "-l" : "-la";
	outputFile = popen(("ls " + option + " '" + actualDirectory + "' | grep '" + selectedFilename + "'").c_str(), "r");
				
	fgets(permissions, sizeof(permissions), outputFile);	
		
	std::cout<<"\r   \033[38;5;"<<colorscheme.at("file_permissions")<<"m"<<permissions<<"\033[0m";
	std::cout<<"\033[38;5;"<<colorscheme.at("file_number")<<"m\r\t\t\t\t\t   "<<numberOfFileChosen<<"/"<<i<<"\033[0m";
	
	time_t time = s.st_mtime;
	struct tm *date = localtime(&time);
	
	std::string minutes = date->tm_min<=9 ? std::to_string(0) + std::to_string(date->tm_min) : std::to_string(date->tm_min);

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

		std::cout<<"\r\t\t\033[38;5;"<<colorscheme.at("file_size")<<"m"<<round(fileSize * 100) / 100<<sizes[size]<<"\033[033m";
		std::cout<<"   \033[38;5;"<<colorscheme.at("file_modification_date")<<"m"<<date->tm_mon+1<<"/"<<date->tm_mday<<"/"<<date->tm_year+1900<<" "<<date->tm_hour<<":"<<minutes<<"\033[033m";


		outputFile = popen(("file '" + fileChosen.string() + "'").c_str(), "r");
		fgets(output, sizeof(output), outputFile);

		if(strstr(output, "text") && config.at("preview_files")==1) showPreviews("textFiles", fileChosen);
		else if(strstr(output, "image") && config.at("preview_images")==1) showPreviews("images", fileChosen);

	}else if(s.st_mode & S_IFDIR && config.at("preview_directories")==1){ 
		showPreviews("directory", fileChosen);
		std::cout<<"\033[16;0f\r\t\t\033[38;5;"<<colorscheme.at("file_modification_date")<<"m"<<date->tm_mon+1<<"/"<<date->tm_mday<<"/"<<date->tm_year+1900<<" "<<date->tm_hour<<":"<<minutes<<"\033[033m";
	
	}
}

void changeFileChosen(bool up){
	if(filesSelected.size()>1) return; 
	if(up == false){
		if(numberOfFiles==numberOfFileChosen) return;
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
	
	selectingFiles = true;
	filesSelected.erase(filesSelected.begin(), filesSelected.end());
	rangeSelect.fill("");

	if(forwardOrBackward == "forward"){
		struct stat s;
		stat(fileChosen.c_str(), &s);
		if(s.st_mode & S_IFDIR) showFiles(fileChosen);
		else{
		 system(("xdg-open " + fileChosen.string() + "&").c_str());
		}
	}else if(forwardOrBackward == "backward" && std::experimental::filesystem::path(actualDirectory).has_parent_path()) showFiles(std::experimental::filesystem::path(actualDirectory).parent_path());
}

void createNewTab(){
	char homeDirectory[256];
	getcwd(homeDirectory, 256);
	tabs.push_back(homeDirectory);

	numberOfTabs++;
	actualTab = numberOfTabs;

	showTabs();
	showFiles(homeDirectory);
}

void closeTab(){
	if(numberOfTabs <= 1) return;
	tabs.erase(tabs.begin()+actualTab-1);
	
	if(numberOfTabs == actualTab) actualTab--;
	numberOfTabs--;
	showFiles(tabs.at(actualTab-1));
}

void moveAroundTabs(std::string leftOrRight){
	if(leftOrRight == "left" && actualTab > 1) actualTab--;
	else if(leftOrRight == "right" && actualTab<numberOfTabs) actualTab++;

	numberOfFileChosen=1;
	showFiles(tabs.at(actualTab-1));	
}

void goToTheTop(){
	numberOfFileChosen = 1;
	stopOutput = 10;
	
	showFiles(actualDirectory);
}

void goToTheBottom(){
	if(numberOfFiles==0) return;
	
	numberOfFileChosen = numberOfFiles;
	stopOutput = numberOfFiles;

	showFiles(actualDirectory);
}

void goToTheMiddle(){
	if(numberOfFiles==0) return;

	numberOfFileChosen = numberOfFiles/2; 
	stopOutput = numberOfFiles/2+5;

	showFiles(actualDirectory);
}

void searchBar(){
	numberOfFileChosen = 1;
	
	commandLine("search", &inputSearch);

	showFiles(actualDirectory);

	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\r\033[38;5;"<<colorscheme.at("command_line")<<"m   :search \033[0m\033[38;5;"<<colorscheme.at("command_finished")<<"m"<<inputSearch<<"\033[0m";
}

void renameFile(){
	std::string newName;
	
	commandLine("rename", &newName);

	std::experimental::filesystem::rename(fileChosen, actualDirectory + "/" + newName);
	
	showFiles(actualDirectory);

	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\r\033[38;5;"<<colorscheme.at("command_line")<<"m   :rename \033[0m\033[38;5;"<<colorscheme.at("input_command_line")<<"m"<<inputSearch<<"\033[0m";
}

void deleteFile(){
	std::string Delete;
	std::string fileToRemove = filesSelected.size()>1 ? "selected files" : selectedFilename;
	commandLine("Delete '" + fileToRemove + "' [Y/n]", &Delete);
	
	if(Delete=="n" || Delete=="N") return;
	
	struct stat s;

	if(filesSelected.size()>1){
		std::experimental::filesystem::directory_entry * files = filesSelected.data();
		for(unsigned i = 0; i<filesSelected.size(); i++){
			stat(files[i].path().filename().string().c_str(), &s);

			if(s.st_mode & S_IFDIR) std::experimental::filesystem::remove_all(files[i]);
			else std::experimental::filesystem::remove(files[i]);
		}
		filesSelected.erase(filesSelected.begin(), filesSelected.end());
		selectingFiles = true;
		rangeSelect.fill("");
	}else{

		stat(fileChosen.c_str(), &s);

		if(s.st_mode & S_IFDIR) std::experimental::filesystem::remove_all(fileChosen);
		else std::experimental::filesystem::remove(fileChosen);
	}
	showFiles(actualDirectory);

	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\033[2K";
	std::cout<<"\r\033[38;5;"<<colorscheme.at("command_finished")<<"m   '"<<fileToRemove<<"'\033[0m\033[38;5;"<<colorscheme.at("command_line")<<"m removed\033[0m";
}

void copyFile(){
	std::cout<<"\033[17;0f\033[38;5;"<<colorscheme.at("command_finished")<<"m   Copying... \033[0m(Press 'C' to paste the file)\033[0;0f";
	if(filesSelected.empty()){ copiedFile.push_back(std::experimental::filesystem::directory_entry(fileChosen)); return;}
	
	copiedFile = filesSelected;

	filesSelected.erase(filesSelected.begin(), filesSelected.end());
	selectingFiles = true;
	rangeSelect.fill("");

	showFiles(actualDirectory);
}

void pasteFile(){
	if(copiedFile.empty()){
		std::cout<<"\033[17;0f\033[38;5;"<<colorscheme.at("error")<<"m   No file copied\033[0m";
		return;
	}
	std::experimental::filesystem::directory_entry *files = copiedFile.data();

	for(unsigned i = 0; i<copiedFile.size(); i++){
		struct stat s;
		stat(files[i].path().c_str(), &s);
	
		try{
			if(s.st_mode & S_IFDIR)	std::experimental::filesystem::copy(files[i].path(), actualDirectory + "/" + files[i].path().filename().string(), std::experimental::filesystem::copy_options::recursive);
			else std::experimental::filesystem::copy(files[i], actualDirectory + "/");
		}catch(std::experimental::filesystem::__cxx11::filesystem_error){
			std::cout<<"\033[17;0f\033[38;5;"<<colorscheme.at("error")<<"m   An error occurred while pasting the file\033[0m";
		}
	}
	copiedFile.erase(copiedFile.begin(), copiedFile.end());
	
	showFiles(actualDirectory);
}

void moveFile(){
	if(filesToMove.empty()){
		std::cout<<"\033[17;0f\033[38;5;"<<colorscheme.at("command_line")<<"m  (Press 'x' again to finish moving the file)\033[0m";
		if(filesSelected.size()>1) filesToMove = filesSelected;
		else filesToMove.push_back(std::experimental::filesystem::directory_entry(fileChosen));
	}else{
		std::experimental::filesystem::directory_entry *files = filesToMove.data();
		
		for(unsigned i = 0; i<filesToMove.size(); i++) std::experimental::filesystem::rename(files[i], actualDirectory + "/" + files[i].path().filename().string());

		filesSelected.erase(filesSelected.begin(), filesSelected.end());
		filesToMove.erase(filesToMove.begin(), filesToMove.end());

		showFiles(actualDirectory);
	}
}

void makeDir(){
	std::string dirName;
	commandLine("mkdir", &dirName);
	mkdir((actualDirectory + "/" + dirName).c_str(), 0777);
	
	showFiles(actualDirectory);

	std::cout<<"\033[17;0f\033[38;5;"<<colorscheme.at("command_finished")<<"m"<<dirName<<"\033[0m"<<"\033[38;5;"<<colorscheme.at("command_line")<<"m successfully created\033[0m";
}

void createFile(){
	std::string filename;
	
	commandLine("file", &filename);
	
	std::ofstream file(actualDirectory + "/" + filename);
	file.close();
	
	showFiles(actualDirectory); 
}

void selectFiles(){
	if(!selectingFiles){
		selectingFiles = true;
		filesSelected.erase(filesSelected.begin(), filesSelected.end());
		rangeSelect[1] = fileChosen;
	
		showFiles(actualDirectory);
		
		std::cout<<"\033["<<17<<";0f";
		std::cout<<"\r\033[38;5;"<<colorscheme.at("command_line")<<"m   [c] Copy [x] move [G] compress [X] delete [Z] cancel";

		return;
	}
	selectingFiles=false;
	rangeSelect[0] = fileChosen;
}

void cancelSelectFiles(){
	selectingFiles = true;
	filesSelected.erase(filesSelected.begin(), filesSelected.end());
	rangeSelect.fill("");
	showFiles(actualDirectory);
}

void commandLine(std::string command, std::string *result){
	std::cout<<"\033["<<17<<";0f";
	std::cout<<"\033[2K";
	std::cout<<"\r\033[38;5;"<<colorscheme.at("command_line")<<"m   :"<<command<<" \033[0m\033[38;5;"<<colorscheme.at("input_command_line")<<"m";	

	system("stty cooked");

	std::cin>>*result;
	
	system("stty raw");
}

void decompressFile(){
		if(fileChosen.extension().string() == ".tbz" || fileChosen.extension().string() == ".bz2" || 
		   fileChosen.extension().string() == ".gz" || fileChosen.extension().string() == ".tar"){
			system(("tar -xf '" + fileChosen.string() + "' -C" + actualDirectory).c_str());
		}
		
		else if(fileChosen.extension().string() == ".zip"){
			system("stty cooked");
			system(("unzip -qq '" + fileChosen.string() + "' -d" + actualDirectory).c_str());
			system("stty raw");
		}
		
		else{
			std::cout<<"\033[17;0f\r\033[38;5;"<<colorscheme.at("error")<<"m   The file couldn't be decompressed";
			return;
		}
		
		showFiles(actualDirectory);
		std::cout<<"\033[17;0f\r\033[38;5;"<<colorscheme.at("command_finished")<<"m   Decompressed file successfully";	
	

}

void compressFile(){
	char type;

	std::cout<<"\033["<<17<<";0f\033[2K";
	std::cout<<"\r\033[38;5;"<<colorscheme.at("command_line")<<"m   compress [1] tar.gz [2] tar.bz2";
	
	type = getchar();

	std::experimental::filesystem::directory_entry *data = filesSelected.data(); 
	std::string allFiles;

	for(int i = 0; i<filesSelected.size(); i++) allFiles = allFiles + "'" + data[i].path().string() + "' ";
	
	std::string flags, name;

	switch(type){
		case '1': flags = " -czf ";
			name = actualDirectory + "/compressed.tar.gz ";
			break;

		case '2': flags = " -cjf ";
			name = actualDirectory + "/compressed.tar.bz2 ";
			break;
	}
	
	system(("tar " + flags + name + allFiles).c_str());

	filesSelected.erase(filesSelected.begin(), filesSelected.end());
	selectingFiles = true;
	rangeSelect.fill("");

	showFiles(actualDirectory);
}


void help(){
	system("clear");

	std::cout<<" Keybindings:\n\r\e[38;5;116m  h, j, k, l\033[0m Navigate\n\r\e[38;5;116m  t\033[0m Open a new tab\n\r\e[38;5;116m  H\033[0m Move to the left tab\n\r\e[38;5;116m  L\033[0m Move to the right tab\n\r\e[38;5;116m  d\033[0m Open search bar\n\r\e[38;5;116m  z\033[0m Select files\n\r\e[38;5;116m  c\033[0m Copy file\n\r\e[38;5;116m  x\033[0m Move file\n\r\e[38;5;116m  s\033[0m Create file\n\r\e[38;5;116m  S\033[0m Create dir\n\r\e[38;5;116m  f\033[0m Rename file\n\r\e[38;5;116m  X\033[0m Delete file (be careful when deleting a file, there is no way to get it back)\n\r\e[38;5;116m  q\033[0m Close file manager\n\n\r  Press h, j, k or l to return to file manager";
}
