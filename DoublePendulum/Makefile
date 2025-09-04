OBJ = double_pendulum.o my_odesolvers.o

CXX = g++
CFLAGS = -c
SRC = $(HOME)/Documents/Uni/Algoritmi/Lib
VPATH = ./:$(SRC)
INCLUDE_DIRS = -I./ -I$(SRC)
LDFLAGS = -lm

double_pendulum: $(OBJ)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $@
	@echo "\nINFO: Finished compiling"

data: double_pendulum
	@echo "\nINFO: Executing binary...\n"
	@./double_pendulum
	@echo "\nINFO: Data baked\n"

double_pendulum.dat: data

%.o: %.cpp
	@$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<

energy: double_pendulum.dat
	@gnuplot energy.gp
	@echo "INFO: Energy plot completed!\n"

gif: double_pendulum.dat
	@echo "\nINFO: Working on it...\n"
	@gnuplot double_pendulum.gp 2>/dev/null
	@echo "\nINFO: GIF completed!\n"

plots: energy, gif

caos: double_pendulum.dat double_pendulum1.dat
	@echo "\nINFO: Working on it...\n"
	@gnuplot multi_pendulum.gp 2>/dev/null
	@echo "\nINFO: GIF baked... Ready for CAOS!\n"

clean: 
	@rm -f *.o 
	@echo make clean: done

.PHONY: data, energy, gif, plots, caos
