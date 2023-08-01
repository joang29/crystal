NAME = crystalfm
BIN = /usr/local/bin/crystalfm
SRC = crystal/fileManager.cpp crystal/keys.cpp crystal/main.cpp crystal/previews.cpp crystal/loadConfiguration.cpp crystal/icons.cpp
DCONF = ${HOME}/.config/crystal/
CONF = crystal/crystal.conf crystal/keys.conf 
THEME_CONF = crystal/themes/green.conf crystal/themes/purple.conf crystal/themes/ice.conf crystal/themes/red.conf crystal/themes/colorscheme.conf
DTHEME = ${HOME}/.config/crystal/themes/
CXX ?= g++

install:
	mkdir -p ${DCONF} ${DTHEME}	
	cp ${CONF} ${DCONF}
	cp ${THEME_CONF} ${DTHEME}
	${CXX} ${SRC} -o ${NAME} -lstdc++fs
	sudo install -Dm 775 ${NAME} ${BIN}

clean:
	sudo rm ${BIN}
	rm -r ${DCONF}
