# Variables
INCLUDE_DIR = src/include
LIB_DIR = src/lib
OBJECTS = main.o game.o stagebuilder.o stage.o movablentity.o player.o animation.o event.o eventfactory.o staticentity.o 
EXECUTABLE = debug-outcastgame

# Regla principal
all: compile link

# Regla para compilar los archivos fuente
compile: $(OBJECTS)

# Regla genérica para compilar los archivos fuente
%.o: src/%.cpp
	g++ -I $(INCLUDE_DIR) -c $< -o $@

# Regla para enlazar los objetos y crear el ejecutable
link: $(OBJECTS)
	g++ $(OBJECTS) -o $(EXECUTABLE) -L $(LIB_DIR) -lsfml-system -lsfml-window -lsfml-graphics

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
