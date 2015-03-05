#include <stdio.h>
#include <stdlib.h>

#include "local_signal.h"

static void main_signal_handler(int signo);
static void main_signal_process(int signo);

int main(int argc, char **argv)
{
	void (*old_handler)(int);

	old_handler = NULL;
	old_handler = local_signal(10, main_signal_handler);
	if (old_handler != NULL)
	{
		return 0;
	}

	do_local_signal(10);
	old_handler = local_signal(10, main_signal_process);
	if (old_handler != main_signal_handler)
	{
		printf("get old handler failure\n");
		return 0;
	}

	do_local_signal(10);
	old_handler = local_signal(10, main_signal_handler);
	if (old_handler != main_signal_process)
	{
		printf("get old process failure\n");
		return 0;
	}

	do_local_signal(10);
	release_local_signal_handlers();
	do_local_signal(10);
	printf("Hellow world\n");
	return EXIT_SUCCESS;
}

void main_signal_handler(int signo)
{
	char buffer[1024];

	printf("main_signal_handler:singo=%d\n", signo);
}

void main_signal_process(int signo)
{
	char buffer[1024];

	printf("main_signal_process:singo=%d\n", signo);
}