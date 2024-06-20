#include <stdexcept>
#include<unordered_map>
#include<string>
#include<experimental/filesystem>
#include<iostream>

std::unordered_map<std::string, std::string> icons = {
	{".cpp", " "},
	{".cc", " "},
	{".nix", "󱄅 "},
	{".java", " "},
	{".class", " "},
	{".jar", " "},
	{".js", " "},
	{".json", "󰘦 "},
	{".py", " "},
	{".ts", " "},
	{".go", " "},
	{".c", " "},
	{".h", " "},
	{".cs", "󰌛 "},
	{".css", " "},
	{".scss", " "},
	{".sass", " "},
	{".html", " "},
	{".rs", " "},
	{".kt", " "},
	{".lua", " "},
	{".rb", " "},
	{".swift", " "},
	{".php", " "},
	{".phps", " "},
	{".phtml", " "},
	{".pl", " "},
	{".ls", " "},
	{".apk", " "},
	{".sql", " "},
	{".iml", " "},
	{".md", " "},
	{".xml", "󰗀 "},
	{".iso", " "},
	{".cfg", " "},
	{".conf", " "},
	{".config", " "},
	{".run", "󰥥 "},
	{".toml", " "},
	{".yml", " "},
	{".fish", "󰈺 "},
	{".theme", " "},
	{".pdf", " "},
	{".sh", " "},
	{".gz", " "},
	{".tgz", " "},
	{".zst", " "},
	{".bz2", " "},
	{".zip", " "},
	{".csv", "󰈙 "},
	{".log", " "},
	{".txt", " "},
	{".ttf", " "},
	{".otf", " "},
	{".mp3", "󰈣 "},
	{".mp4", "󰈫 "},
	{".png", " "},
	{".svg", " "},
	{".jpg", " "},
	{".jpeg", " "},
	{".gif", "󰵸 "},
	{".AppImage", "󰥥 "},
	{".desktop", "󱁼 "},
	{".rtf", " "},
	{".odt", " "},
	{".fodt", " "},
	{".odp", "󰐩 "},
	{".fodp", "󰐩 "},
	{".ods", "󰱾 "},
	{".fods", "󰱾 "},
};

std::unordered_map<std::string, std::string> iconsExactFilename = {
	{"LICENSE", "󱕴 "},
	{"license", "󱕴 "},
	{"Makefile", " "},
	{"makefile", " "},
	{"home", "󱂵 "},
	{"Desktop", " "},
	{"Documents", "󰈢 "},
	{"Downloads", " "},
	{"Music", "󱍚 "},
	{"Videos", "󰯜 "},
	{"Pictures", "󰉏 "},
	{".config", " "},
	{".cache", "󰍛 "},
	{"playlist", "󰲸 "},
	{"AndroidStudioProjects", "󰀴 "},
	{".vscode", "󰨞 "},
	{".idea", " "},
	{".zshrc", " "},
	{".zsh_history", " "},
	{".bashrc", " "},
	{".bash_history", " "},
	{".bash_logout"," "},
	{".bash_profile", " "},
	{".bash_aliases", " "},
	{".profile", " "},
	{".git", " "},
	{".gitignore", " "},
	{".gitconfig", " "},
	{".vimrc", " "},
	{".vim", " "},
	{".viminfo", " "},
	{".npm", " "},
	{"node_modules", " "},
};

std::string returnIcon(std::experimental::filesystem::path file){
	if(std::experimental::filesystem::is_symlink(file)) return "  ";
	if(file.has_extension() && file.filename().string()[0] != '.') {
		try{
			//if the extension is not in the map, it returns a default icon
			return icons.at(file.extension()) + " ";
		}catch(std::out_of_range){return "  ";}
	}
	try{
		//if it doesn't match any defined directory/file, return a default icon
		return iconsExactFilename.at(file.filename()) + " ";
	}catch(std::out_of_range){
		if(std::experimental::filesystem::is_directory(file)) return "  ";
		else return "  ";
}	}
