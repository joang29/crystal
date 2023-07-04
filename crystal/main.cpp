#include<sys/stat.h>
#include<unistd.h>

#include "functions.h"

int main(){
	system("stty raw");

	struct stat checkIfDirExists;
	std::string home = getenv("HOME");
	
	if(stat((home + "/.config/crystal").c_str(), &checkIfDirExists) != 0) mkdir((home + "/.config/crystal").c_str(), 0777);
	
	char directory[256];
	getcwd(directory, 256);

	showFiles(directory);
	keys();
	
	return 0;
}
