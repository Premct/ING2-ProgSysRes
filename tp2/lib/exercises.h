/**
 * Header file for TP2 exercises
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#ifndef TP2_EXERCISES_H
#define TP2_EXERCISES_H

void sigHandler(int signal);

void sendSignal(int sig, pid_t p_dest);

void alarmHandler();

void exerciseOne();

void exerciseTwo();

void exerciseThree();

#endif //TP2_EXERCISES_H
