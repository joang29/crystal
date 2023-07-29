NAME = crystalfm
BIN = /usr/local/bin/crystalfm
SRC = crystal/fileManager.cpp crystal/keys.cpp crystal/main.cpp crystal/previews.cpp crystal/loadConfiguration.cpp crystal/icons.cpp
DCONF = ${HOME}/.config/crystal/
CONF = crystal/crystal.conf crystal/keys.conf crystal/colorscheme.conf
CXX ?= g++

install:
	mkdir -p ${DCONF}	
	cp ${CONF} ${DCONF}
	${CXX} ${SRC} -o ${NAME} -lstdc++fs
	sudo install -Dm 775 ${NAME} ${BIN}

clean:
	rm ${BIN}
	rm -r ${DCONF}
