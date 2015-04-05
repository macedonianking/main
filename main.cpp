#include <stdio.h>
#include <stdlib.h>

#include "local_signal.h"
#include "curl_main.h"
#include "main_sort.h"
#include "main_sqlite3.h"
#include "main_string_builder.h"
#include "main_solutions.h"

static void main_program_enter();
static void main_program_leave();
static void main_signal_handler(int signo);
static void main_signal_process(int signo);
static void main_signal_test();

int main(int argc, char **argv)
{
	main_program_enter();
	// main_signal_test();
	// curl_main_test();
	// main_sort_test();
	main_sqlite3_test();
	// main_string_builder_test();
	// main_solutions_run();

	// printf("Hello world\n");
	main_program_leave();
	return EXIT_SUCCESS;
}

void main_signal_test()
{
	void (*old_handler)(int);

	old_handler = NULL;
	old_handler = local_signal(10, main_signal_handler);
	if (old_handler != NULL)
	{
		return;
	}

	do_local_signal(10);
	old_handler = local_signal(10, main_signal_process);
	if (old_handler != main_signal_handler)
	{
		printf("get old handler failure\n");
		return;
	}

	do_local_signal(10);
	old_handler = local_signal(10, main_signal_handler);
	if (old_handler != main_signal_process)
	{
		printf("get old process failure\n");
		return;
	}

	do_local_signal(10);
	release_local_signal_handlers();
	do_local_signal(10);
}

void main_signal_handler(int signo)
{
	printf("main_signal_handler:singo=%d\n", signo);
}

void main_signal_process(int signo)
{
	printf("main_signal_process:singo=%d\n", signo);
}

void main_program_enter()
{
#ifdef F_USE_CURL
	curl_main_enter();
#endif
}

void main_program_leave()
{
#ifdef F_USE_CURL
	curl_main_leave();
#endif
}
