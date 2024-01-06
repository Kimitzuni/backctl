CC		= g++
CFLAGS		= -O2 -pipe
INCLUDE		= -I include/
LIBS		= 
SOURCES		= main.cpp
OBJECTS		= $(patsubst %.cpp, %.o, $(SOURCES))
EXEC		= backctl

all: $(OBJECTS) $(EXEC)

clean:
	@rm -vf $(OBJECTS) $(EXEC)

install: $(EXEC)
	cp backctl /usr/local/bin/

uninstall:
	rm /usr/local/bin/backctl -vf

$(OBJECTS): ./%.o : ./%.cpp
	@printf ">>> Compiling \033[1;95m$@\033[0m\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(LIBS)

$(EXEC): $(OBJECTS)
	@printf ">>> Linking to \033[1;96m$(EXEC)\033[0m\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(EXEC) $(OBJECTS) $(LIBS)
