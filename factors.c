#include "factors.h"

void factorize(mpz_t num)
{
    mpz_t i, factor, quotient, remainder, sqrt_num;
    mpz_inits(i, factor, quotient, remainder, sqrt_num, NULL);
    mpz_set_ui(i, 2);
    mpz_sqrt(sqrt_num, num);

    while (mpz_cmp(i, sqrt_num) <= 0)
    {
        mpz_fdiv_qr(quotient, remainder, num, i);
        if (mpz_cmp_ui(remainder, 0) == 0)
        {
            gmp_printf("%Zd=%Zd*%Zd\n", num, quotient, i);
            mpz_set(num, quotient);
            break;
        }
        mpz_add_ui(i, i, 1);
    }

    mpz_clears(i, factor, quotient, remainder, sqrt_num, NULL);
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
	alarm(5);
	setup_alarm();
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	mpz_t num;
	mpz_init(num);

	if (argc != 2)
	{
		fprintf(stderr, "Usage: factors <file> %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");

	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
	{
		mpz_set_str(num, line, 10);
		factorize(num);
	}

	mpz_clear(num);
	return 0;
}
