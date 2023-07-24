NAME = crystalfm
BIN = /usr/local/bin/crystalfm
SRC = crystal/functions.h crystal/files.cpp crystal/keys.cpp crystal/main.cpp crystal/previews.cpp
DCONF = ${HOME}/.config/crystal/
CONF = crystal/keys.h crystal/config.h
CXX ?= g++

config:
	cp ${DCONF}/config.h ${CURDIR}/crystal/
	cp ${DCONF}/keys.h ${CURDIR}/crystal/
	${CXX} ${SRC} -o ${NAME} -lstdc++fs
	sudo install -Dm 775 ${NAME} ${BIN}

install:
	mkdir -p ${DCONF}	
	cp ${CONF} ${DCONF}
	${CXX} ${SRC} -o ${NAME} -lstdc++fs
	sudo install -Dm 775 ${NAME} ${BIN}

clean:
	rm ${BIN}
	rm -r ${DCONF}
