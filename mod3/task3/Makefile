all: run-multiple rm-shm run

complie:
	@echo "--------------- Compiling ---------------"
	gcc -o sys1 sys1.c
	gcc -o sys2 sys2.c

run: complie
	@echo "--------------- Running ---------------"
	./sys1
	./sys2

run-multiple: complie
	@echo "--------------- Multiple running ---------------"
	for i in 1 2 3 4 5; do \
		./sys1; \
	done
	for i in 1 2 3; do \
		./sys2; \
	done

rm-shm:
	@echo "--------------- Removing shm ---------------"
	ipcs -m | grep 666 | awk '{print $$2}' | xargs ipcrm shm

clean:
	@echo "--------------- Cleaning ---------------"
	ipcs -m | grep 666 | awk '{print $$2}' | xargs ipcrm shm
	rm sys1 sys2
