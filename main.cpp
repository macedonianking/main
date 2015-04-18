#include <stdio.h>
#include <stdlib.h>

#include "main_config.h"
#include "main_signal.h"
#include "main_curl.h"
#include "main_sort.h"
#include "main_sqlite3.h"
#include "main_string_builder.h"
#include "main_solutions.h"
#include "main_priority_queue.h"
#include "main_hash_table.h"
#include "main_tree.h"

static void main_program_enter();
static void main_program_leave();

// 主程序入口
int main(int argc, char **argv)
{
	main_program_enter();
	// main_signal_test();
	// curl_main_test();
	// main_sort_test();
	// main_priority_queue_test();
	// main_sqlite3_test();
	// main_string_builder_test();
	// main_solutions_run();
	// main_hash_table_test();
	main_tree_test();

	// printf("Hello world\n");
	main_program_leave();
	return EXIT_SUCCESS;
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
