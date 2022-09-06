# remove the # in the following line to enable reorg compilation (and running)
all: cruncher # reorg

cruncher: cruncher.c utils.h
	gcc -I. -O3 -o cruncher cruncher.c

loader: loader.c utils.h
	gcc -I. -O3 -o loader loader.c

reorg: reorg.c utils.h
	gcc -I. -O3 -o reorg reorg.c

cruncher_debug: cruncher.c utils.h
	gcc -I. -g -O0 -fsanitize=address cruncher.c

loader_debug: loader.c utils.h
	gcc -I. -g -O0 -fsanitize=address loader.c

reorg_debug: reorg.c utils.h
	gcc -I. -g -O0 -fsanitize=address reorg.c

clean:
	rm -f loader cruncher reorg
