cmake_minimum_required(VERSION 3.12)
project(progetto_calcolatori C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_executable(progetto_calcolatori main.c scheduler/Scheduler.c scheduler/Scheduler.h strutture/lista_istruzione.c strutture/lista_istruzione.h strutture/lista_task.c strutture/lista_task.h utility/FCFS.c utility/FCFS.h utility/round_robin.c utility/round_robin.h utility/scrittura_file.c utility/scrittura_file.h utility/struttura_thread.c utility/struttura_thread.h utility/lettura_terminale.c utility/lettura_terminale.h)