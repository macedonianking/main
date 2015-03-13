#include <stdio.h>
#include <stdlib.h>

#include "curl_main.h"

void curl_main_test()
{

}

void curl_main_enter()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

void curl_main_leave()
{
	curl_global_cleanup();
}