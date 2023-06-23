#include "factors.h"

void factorize(long int n)
{
	long int i;
	for (i = 2; i < n; i++)
	{
		if (n % i == 0)
		{
			printf("%ld=%ld*%ld\n", n, n/i, i);
			return;
		}
	}
	printf("%ld is a prime number\n", n);
}

void handle_timeout(int sig)
{
	printf("Program timed out\n");
	exit(1);
}

void setup_alarm()
{
	struct sigaction sa;
	sa.sa_handler = handle_timeout;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	long int n;
	setup_alarm();
	alarm(5);

	if (argc != 2)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
        
	fp = fopen(argv[1], "r");

        if (!fp)
        {
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
        }

	while (fscanf(fp, "%ld", &n) == 1)
	{
		factorize(n);
	}
	
	fclose(fp);
	return 0;
}
