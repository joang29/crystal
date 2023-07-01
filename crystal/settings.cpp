#include "functions.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include<iostream>
#include<fstream>

void showSettings();
void moveAroundSettings(bool);
void changeSettings();
void manageSettings();
std::array<bool, 4> returnSettings();

int selectedSetting = 0;

void showSettings(){
	system("clear");

	manageSettings();
	
	std::array<bool, 4> settings = returnSettings();
	std::array<std::string, 4> settingOptions;

	settingOptions[0] = settings[0] ? "Show hidden files [X]" : "Show hidden files [ ]";
	settingOptions[1] = settings[1] ? "Preview files [X]" : "Preview files [ ]";
	settingOptions[2] = settings[2] ? "Preview directories [X]" : "Preview directories [ ]";
	settingOptions[3] = settings[3] ? "Preview images [X]" : "Preview images [ ]";
	
	std::cout<<"\033[1;94m  Settings:\033[0m\n\n";
	for(int i = 0; i<4; i++){
		selectedSetting == i ? std::cout<<"\r> "<<settingOptions[i]<<std::endl : std::cout<<"\r  "<<settingOptions[i]<<std::endl;
	}
}

void moveAroundSettings(bool up){
	if(!up && selectedSetting < 3) selectedSetting++;
	else if(selectedSetting > 0) selectedSetting--;

	showSettings();
}

void changeSettings(){
	std::ifstream settingsFile(std::string(getenv("HOME")) + "/.config/crystal/crystal.conf");
	std::ofstream newSettingsFile(std::string(getenv("HOME")) + "/.config/crystal/newCrystal.conf");
	int i = 0;
	while(settingsFile.eof()==0){
		std::string line;
		getline(settingsFile, line);
	
		if(selectedSetting == i)line.find("TRUE") != std::string::npos ? line.replace(line.find("TRUE"), 4, "FALSE") : line.replace(line.find("FALSE"), 5, "TRUE");
		
		newSettingsFile<<line<<std::endl;
		i++;
	}

	remove((std::string(getenv("HOME")) + "/.config/crystal/crystal.conf").c_str());
	std::rename((std::string(getenv("HOME")) + "/.config/crystal/newCrystal.conf").c_str(), (std::string(getenv("HOME")) + "/.config/crystal/crystal.conf").c_str());

	showSettings();
}

void manageSettings(){
	std::ifstream settingsFile(std::string(getenv("HOME"))+"/.config/crystal/crystal.conf");
	if(!settingsFile.is_open()){
		std::ofstream creatingSettingsFile(std::string(getenv("HOME"))+"/.config/crystal/crystal.conf");
		creatingSettingsFile<<"HIDDEN_FILES =        FALSE\nPREVIEW_FILES =       TRUE\nPREVIEW_DIRECTORIES = TRUE\nPREVIEW_IMAGES =      FALSE";
		creatingSettingsFile.close();
	}
	settingsFile.close();
}

std::array<bool, 4> returnSettings(){
	std::array<bool, 4> settings;
	
	manageSettings();

	std::ifstream settingsFile(std::string(getenv("HOME"))+"/.config/crystal/crystal.conf");
	
	int i = 0;
	while(settingsFile.eof()==0){
		std::string setting;
		std::getline(settingsFile, setting);
		settings[i] = setting.find("TRUE") != std::string::npos ? true : false;
		i++;
	}

	return settings;
}
