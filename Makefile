NAME = crystalfm
BIN = /usr/local/bin/crystalfm
SRC = crystal/functions.h crystal/showFiles.cpp crystal/settings.cpp crystal/keys.cpp crystal/main.cpp 
CXX ?= g++

install:
	${CXX} ${SRC} -o ${NAME} -lstdc++fs
	install -Dm 775 ${NAME} ${BIN}

clean:
	rm ${BIN}
