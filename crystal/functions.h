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
void copyFile();
void pasteFile();
void moveFile();
void makeDir();
void createFile();
void selectFiles();
void cancelSelectFiles();

//showPreviews.cpp
void showPreviews(std::string, std::string);

//settings.cpp
void createSettings();
std::array<bool, 4> returnSettings();
#endif
