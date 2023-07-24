#include<sys/stat.h>
#include<unistd.h>
#include<fstream>

#include "functions.h"

int main(){
	system("stty raw");
	
	char directory[256];
	getcwd(directory, 256);

	showFiles(directory);
	keys();
	
	return 0;
}
