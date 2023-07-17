#ifndef FUNCTIONS
#define FUNCTIONS

#include<string>
#include<array>

//keys.cpp
void keys();

//showFiles.cpp
void showFiles(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);
void searchBar();
void renameFile();
void deleteFile();
//showPreviews.cpp
void showPreviews(std::string, std::string);

//settings.cpp
void showSettings();
void moveAroundSettings(bool);
void changeSettings();
std::array<bool, 4> returnSettings();
#endif
