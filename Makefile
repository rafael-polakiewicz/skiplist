all: compile

run:
	./exe

compile:
	gcc skip_list_lib.c main.c -o exe

clean:
	find -name "*.o" | xargs rm -f {}
	rm -rf projeto_1.zip
	rm -f exe

zip:
	zip -r projeto_1 skip_list_lib.c skip_list_lib.h main.c Makefile
