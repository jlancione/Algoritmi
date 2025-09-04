OBJ = double_pendulum.o my_odesolvers.o

CXX = g++
CFLAGS = -c
SRC = $(HOME)/Documents/Uni/Algoritmi/Lib
VPATH = ./:$(SRC)
INCLUDE_DIRS = -I./ -I$(SRC)
LDFLAGS = -lm

double_pendulum: $(OBJ)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $@
	@echo "\n\nINFO: Finished compiling\n\n"

data: double_pendulum
	@./double_pendulum
	@echo "\n\nINFO: Data baked\n\n"

%.o: %.cpp
	@$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<

energy: double_pendulum
	@./double_pendulum
	@gnuplot energy.gp
	@echo -e "\n\nINFO: Energy plot completed!\n\n"

gif: double_pendulum
	@./double_pendulum
	@echo -e "INFO: Working on it..."
	@gnuplot double_pendulum.gp
	@echo -e "\n\nINFO: GIF completed!\n\n"

plots: energy, gif

caos: double_pendulum.dat double_pendulum1.dat
	@echo "\n\nINFO: Working on it...\n\n"
	@gnuplot multi_pendulum.gp
	@echo "\n\nINFO: GIF baked... Ready for CAOS!\n\n"

clean: 
	@rm -f *.o 
	@echo make clean: done

.PHONY: data, energy, gif, plots, caos
