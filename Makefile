AUTOMAKE_OPTIONS=help
EXE_NAME=draw_lines

help:
	@echo -e "Make options\n"
	@echo "build"
	@echo "install"
build:
	g++ src/*.cpp src/include/*.cpp -lX11 -o ${EXE_NAME}
install:
	mv ${EXE_NAME} /usr/bin
