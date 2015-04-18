#ifndef MAIN_CURL_MAIN_H
#define MAIN_CURL_MAIN_H

#ifdef F_USE_CURL

#include <curl/curl.h>

void curl_main_test();

void curl_main_enter();
void curl_main_leave();

#endif

#endif // MAIN_CURL_MAIN_H
