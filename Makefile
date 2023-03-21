.PHONY : all make test run val clean

PROJ = ipkcpc
LOGIN = xhubin04
SERVER = merlin.fit.vutbr.cz
CPP = g++
OBJ = obj
CPPFLAGS = -Wall -std=c++20 -pedantic -Wall -Wextra -g
SRCS = src/%.cpp
OBJS = udp.o tcp.o main.o
INCS = inc/*.h

all: $(PROJ)

%.o: $(SRCS) $(INCS)
	$(CPP) $(CPPFLAGS) $< -c -o $@

$(PROJ): $(OBJS)
	$(CPP) $(CPFLAGS) $(OBJS) -o $@ 

run: all
	./$(PROJ) -h 127.0.0.1 -p 2023 -m tcp

$(LOGIN).zip: $(PROJ) src inc test Makefile LICENSE CHANGELOG.md README.md
	zip -r $@ $^

upload: $(LOGIN).zip
	scp $(LOGIN).zip $(LOGIN)@$(SERVER):~/

nix:
	nix-shell -p unzip gnumake
	scp $(LOGIN)@$(SERVER):~/$(LOGIN).zip .

test: all
	test/./test.sh

clean: 
	rm *.o ./$(PROJ) ./testfile

valgrind: $(PROJ)
	valgrind ./$(PROJ) --leakcheck=full