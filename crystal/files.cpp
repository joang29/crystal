#include<iostream>
#include<experimental/filesystem>
#include<sys/stat.h>
#include<fstream>
#include<math.h>
#include<string.h>
#include<regex>

#include "functions.h"
#include "config.h"

void showFiles(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);
void searchBar();
void renameFile();
void copyFile();
void pasteFile();
void commandLine(std::string, std::string *);

int numberOfFileChosen = 1, stopOutput = 10;
std::string actualDirectory, selectedFilename, inputSearch = "";
std::experimental::filesystem::path fileChosen;
std::vector<std::experimental::filesystem::directory_entry> filesSelected,  copiedFile, filesToMove;
bool selectingFiles = true;
std::array<std::experimental::filesystem::path, 2> rangeSelect;

void showFiles(std::string directory){
	system("clear");

	int i = 0;
	bool validEntry = false;

	std::cout<<"\033[1;94m  "<<directory<<"\033[0m\n\n";

	for(const auto & entry : std::experimental::filesystem::directory_iterator(directory)){	
		i++;

		if(HIDDEN_FILES==1 && (entry.path().filename().string())[0] == '.' || 
				!inputSearch.empty() && entry.path().filename().string().find(inputSearch) == std::string::npos){
			i--;
			continue;
		}
		if(i>stopOutput || stopOutput-10>i) continue;

		std::string filename = entry.path().filename().string();
		if(selectingFiles){	
			if(entry.path() == rangeSelect[0] || entry.path() == rangeSelect[1]){
					validEntry = !validEntry;
					if(!validEntry) filesSelected.push_back(entry);
			}
			if(validEntry) filesSelected.push_back(entry);
		}
		if(numberOfFileChosen == i || validEntry){ 
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

		outputFile = popen(("file '" + fileChosen.string() + "'").c_str(), "r");
		fgets(output, sizeof(output), outputFile);

		if(strstr(output, "text") && PREVIEW_FILES) showPreviews("textFiles", fileChosen);
		else if(strstr(output, "image") && PREVIEW_IMAGES) showPreviews("images", fileChosen);

	}else if(s.st_mode & S_IFDIR && PREVIEW_DIRECTORIES) showPreviews("directory", fileChosen);
}

void changeFileChosen(bool up){
	if(filesSelected.size()>1) return; 
	if(up == false){
		numberOfFileChosen++;
		if(numberOfFileChosen >= stopOutput-1) stopOutput++;
	
	}else if(numberOfFileChosen != 1){	
		if(filesSelected.size()>1)filesSelected.pop_back();
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
	
	if(forwardOrBackward == "forward"){
		struct stat s;
		stat(fileChosen.c_str(), &s);
		if(s.st_mode & S_IFDIR) showFiles(fileChosen);
		else{
		 system(("xdg-open " + fileChosen.string() + "&").c_str());
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
	std::cout<<"\r\033[38;5;5m   '"<<fileToRemove<<"'\033[0m removed";
}

void copyFile(){
	std::cout<<"\033[17;0f\033[38;5;5m   Copying... \033[0m(Press 'C' to paste the file)";
	if(filesSelected.empty()) copiedFile.push_back(std::experimental::filesystem::directory_entry(fileChosen)); return;
	
	copiedFile = filesSelected;

	rangeSelect.fill("");
	filesSelected.erase(filesSelected.begin(), filesSelected.end());
	selectingFiles = true;
}

void pasteFile(){
	if(copiedFile.empty()){
		std::cout<<"\033[17;0f\033[1;31m   No file copied\033[0m";
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
			std::cout<<"\033[17;0f\033[1;31m   An error occurred while pasting the file\033[0m";
		}
	}
	copiedFile.erase(copiedFile.begin(), copiedFile.end());
	
	showFiles(actualDirectory);
}

void moveFile(){
	if(filesToMove.empty()){
		std::cout<<"\033[17;0f\033[38;5;15m  (Press 'x' again to finish moving the file)\033[0m";
		if(filesSelected.size()>1) filesToMove = filesToMove;
		else filesToMove.push_back(std::experimental::filesystem::directory_entry(fileChosen));
	}else{
		std::experimental::filesystem::directory_entry *files = filesToMove.data();
		
		for(unsigned i = 0; i<filesToMove.size(); i++) std::experimental::filesystem::rename(files[i], actualDirectory + "/" + files[i].path().filename().string());

		filesToMove.erase(filesToMove.begin(), filesToMove.end());
		showFiles(actualDirectory);
	}
}

void makeDir(){
	std::string dirName;
	commandLine("mkdir", &dirName);
	mkdir((actualDirectory + "/" + dirName).c_str(), 0777);
	std::cout<<"\033[17;0f\033[38;5;5m"<<dirName<<"\033[0m"<<" successfully created";
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
		std::cout<<"\r\033[38;5;15m   [c] Copy [X] delete [Z] cancel";

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
	std::cout<<"\r\033[38;5;15m   :"<<command<<" \033[0m\033[38;5;5m";	

	system("stty cooked");

	std::cin>>*result;
	
	system("stty raw");
}
