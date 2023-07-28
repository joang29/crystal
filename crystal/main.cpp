#include<sys/stat.h>
#include<unistd.h>
#include<fstream>
#include "keys.h"

#include "fileManager.h"

int main(){
	system("stty raw");

	char directory[256];
	getcwd(directory, 256);

	showFiles(directory);
	keys();
	
	return 0;
}
