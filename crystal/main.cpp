#include "functions.h"
#include<sys/stat.h>

int main(){
	system("stty raw");

	struct stat checkIfDirExists;
	std::string home = getenv("HOME");
	
	if(stat((home + "/.config/crystal").c_str(), &checkIfDirExists) != 0) mkdir((home + "/.config/crystal").c_str(), 0777);
	showFiles(getenv("HOME"));
	keys();
}
