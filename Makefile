all: testprog elfwriter

testprog: testprog.c
	gcc testprog.c -o testprog

elfwriter: elfwriter.c
	gcc elfwriter.c -lelf -o elfwriter

.PHONY: repro
repro: testprog elfwriter
	rm -f ./testprog_copy
	cp ./testprog ./testprog_copy
	./elfwriter ./testprog_copy
	./testprog_copy
