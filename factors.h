#ifndef FACTORS_H
#define FACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void setup_alarm();
void handle_timeout(int sig);

void factorize(long int n);

#endif
