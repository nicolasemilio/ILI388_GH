flags = -Wno-deprecated -g -ggdb -O3
comp = g++
prog  = GE

#El problema
config = Functionsf1-f8/f5.config
results = results.txt

cr = 0.6
mr = 0.01
ps = 3
so = 1
mo = 1
co = 1
max_evals=100000

semilla = 4

comp:$(prog)

exe:$(prog)
	#valgrind --leak-check=full --show-reachable=yes 
	./$(prog) $(config) $(results) $(so) $(co) $(mo) $(cr) $(mr) $(ps) $(max_evals) $(semilla)

$(prog): main.o
	$(comp) main.o -o $(prog) $(flags)

main.o: main.cpp includes.h globales.h
	$(comp) -c main.cpp $(flags)

clean:
	rm -f *~
	rm -f *.o
	rm -f *.txt
	rm -f *.ps
	rm -f $(prog)
	rm -f core*
