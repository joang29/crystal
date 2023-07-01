#ifndef FUNCTIONS
#define FUNCTIONS

#include<string>
#include<array>

//showFiles.cpp
void showFiles(std::string);
void changeFileChosen(bool);
void moveAroundFiles(std::string);

//keys.cpp
void keys();

//settings.cpp
void showSettings();
void moveAroundSettings(bool);
void changeSettings();
std::array<bool, 4> returnSettings();
#endif
