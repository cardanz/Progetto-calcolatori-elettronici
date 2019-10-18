
CC = gcc

CFLAGS = -g -Wall

LIBS = -lpthread

OBJECTS = scheduler/Scheduler.o strutture/lista_istruzione.o strutture/lista_task.o utility/FCFS.o utility/lettura_terminale.o utility/round_robin.o utility/scrittura_file.o utility/struttura_thread.o main.o

PROGRAM_NAME = simulator

all: simulator

$(PROGRAM_NAME):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJECTS) $(LIBS)

clean:
	@rm -f $(PROGRAM_NAME)
	@rm -f *.o
	@rm -f scheduler/*.o
	@rm -f strutture/*.o
	@rm -f utility/*.o
	@rm -f core

test: test1 test2 test3 test4 test5

test1: all
	./simulator -i tasks/01_tasks.csv -on no_pre_1.csv -op pre_1.csv
test2: all
	./simulator -i tasks/02_tasks.csv -on no_pre_2.csv -op pre_2.csv
test3: all
	./simulator -i tasks/03_tasks.csv -on no_pre_3.csv -op pre_3.csv
test4: all
	./simulator -i tasks/04_tasks.csv -on no_pre_4.csv -op pre_4.csv
test5: all
	./simulator -i tasks/05_tasks.csv -on no_pre_5.csv -op pre_5.csv
