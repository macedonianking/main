#include <stdio.h>
#include <stdlib.h>

#include "curl_main.h"

static void curl_main_test_version_info();
static void curl_main_test_http();
static void curl_main_test_write_data_file(void *buffer, size_t size, size_t nmemb, void *data);

#ifndef NDEBUG
#define CURL_MAIN_TEST_FLAG 0
#endif // NDEBUG

void curl_main_test()
{
	#ifdef CURL_MAIN_TEST_FLAG
	curl_main_test_version_info();
	#endif // CURL_MAIN_TEST_FLAG

	curl_main_test_http();
}

void curl_main_enter()
{
	if (CURLE_OK != curl_global_init(CURL_GLOBAL_ALL))
	{
		printf("curl_global_init failure\n");
		exit(-1);
	}
}

void curl_main_leave()
{
	curl_global_cleanup();
}

void curl_main_test_version_info()
{
	curl_version_info_data *info;
	int major, minor, patch;

	info = curl_version_info(CURLVERSION_NOW);
	if (info == NULL)
	{
		printf("curl_version_info failure\n");
		return;
	}

	printf("info->age=%d\n", info->age);
	printf("info->version=%s\n", info->version);

	if (info->ssl_version != NULL)
	{
		printf("info->ssl_version=%s\n", info->ssl_version);
	}

	/**
	 * Parse libcurl version from curl_version_info_data.version_num;
	 */
	major = (info->version_num >> 16) & 0xFF;
	minor = (info->version_num >> 8)  & 0xFF;
	patch = (info->version_num) & 0xFF;
	printf("info->version=%d.%d.%d\n", major, minor, patch);
}

void curl_main_test_http()
{
	CURL *curl = NULL;
	CURLcode r;
	FILE *file;

	curl = curl_easy_init();
	if (!curl)
	{
		return;
	}

	file = fopen("index.html", "w+");

	curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com/index.html");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curl_main_test_write_data_file);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (file != NULL)
	{
		fclose(file);
		file = NULL;
	}
	curl = NULL;
}

static int gwrite_data_times = 0;

void curl_main_test_write_data_file(void *buffer, size_t size, size_t nmemb, void *data)
{
	FILE *file;

	printf("gwrite_data_times=%d, size=%d, nmemb=%d\n", gwrite_data_times, size, nmemb);
	++gwrite_data_times;

	file = (FILE*) data;
	if (file == NULL)
	{
		file = stdout;
	}
	fwrite(buffer, size, nmemb, file);
}