#ifndef FACTORS_H
#define FACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>
#include <gmp.h>

#define MAX_LINE_LENGTH 1000

void setup_alarm();
void handle_timeout(int sig);

void factorize(mpz_t num);

#endif
