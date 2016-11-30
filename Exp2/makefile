CC		=	g++ -Wall -O2 -std=c++11
CFLAGS		=	-I include/
SOURCE		=	include/source.h
TARGET		=	algebraic_attacks
LFSR		=	lfsr
BOOL		=	bool_func
ELIM		=	gauss_elim
COMPILE		=	$(CC) $(CFLAGS) -c $< -o $@
LINK		=	$(CC) $(CFLAGS) $^ -o $@

all: bin_win/$(TARGET).exe

bin_win/$(TARGET).exe: obj_win/main_win.o obj_win/$(LFSR)_win.o obj_win/$(BOOL)_win.o obj_win/$(ELIM)_win.o
	@echo linking files
	@$(LINK)

obj_win/main_win.o: src/main.cpp include/*
	@echo compiling main
	@$(COMPILE) 

lfsr: obj_win/$(LFSR)_win.o

obj_win/$(LFSR)_win.o: src/$(LFSR).cpp include/$(LFSR).h
	@echo compiling $(LFSR)
	@$(COMPILE) 

bool: obj_win/$(BOOL)_win.o

obj_win/$(BOOL)_win.o: src/$(BOOL).cpp include/$(BOOL).h
	@echo compiling $(BOOL)
	@$(COMPILE) 

elim: obj_win/$(ELIM)_win.o

obj_win/$(ELIM)_win.o: src/$(ELIM).cpp include/$(ELIM).h
	@echo compiling $(ELIM)
	@$(COMPILE) 