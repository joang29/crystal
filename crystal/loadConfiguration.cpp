#include<iostream>
#include<unordered_map>
#include<fstream>

std::unordered_map<std::string, unsigned int> loadConfig(std::string config){
	std::string path;
	if(config == "keys") path = std::string(getenv("HOME")) + "/.config/crystal/keys.conf";
	else if(config == "general") path = std::string(getenv("HOME")) + "/.config/crystal/crystal.conf";
	else if(config == "colorscheme") path = std::string(getenv("HOME")) + "/.config/crystal/themes/colorscheme.conf";
	std::ifstream file(path);
	
	std::unordered_map<std::string, unsigned int> configMap;

	while(file.eof()==0){
		std::string line;
		std::getline(file, line);
		if(line[0] == '#') continue;

		std::string option;
		unsigned int value;
		
		file>>option;
		file>>value;
	
		configMap.insert({{option, value}});
	}
	return configMap;
}
