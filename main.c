#include <stdio.h>
#include <signal.h>

void	stuff(int signal)
{
	if (signal == SIGINT)
		printf("salut");
}

int main(int argc, const char *argv[])
{
	signal(SIGINT, stuff);
	while(1);
	return 0;
}
