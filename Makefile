AUTOMAKE_OPTIONS=build
EXE_NAME=draw_lines
build:
	g++ *.cpp include/*.cpp -lX11 -o ${EXE_NAME}
install:
	mv ${EXE_NAME} /usr/bin
