#include <stdio.h>
#include <stdlib.h>

#ifdef F_USE_CURL

#include "main_log.h"
#include "main_http.h"

#include "curl_main.h"

#define URL_BAIDU_HOME				"http://www.baidu.com/"
#define URL_LINUX_IDC_HTTP_AUTH		"http://linux.linuxidc.com/"
#define URL_HTTP_POST_POSTHERE		"http://posthere.com/"

static void curl_main_test_version_info();
static void curl_main_test_http();
static void curl_main_test_http_auth();
static void curl_main_test_http_post();
static void curl_main_test_get_info();

static size_t curl_main_test_write_data_file(void *buffer, size_t size, size_t nmemb, void *data);

void curl_main_test()
{
#ifdef MAIN_DEBUG_ENABLED
	curl_main_test_version_info();
#endif // MAIN_DEBUG_ENABLED

	// curl_main_test_http();
	// curl_main_test_http_auth();
	// curl_main_test_http_post();
	curl_main_test_get_info();
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
		DEBUG_FAILURE("curl_version_info");
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
	minor = (info->version_num >> 8) & 0xFF;
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
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "baidu.cookie");
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	/**
	 * Show details for http response data.
	 */
	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	r = curl_easy_perform(curl);
	if (r != CURLE_OK)
	{
		DEBUG_FAILURE("curl_easy_perform");
	}
	curl_easy_cleanup(curl);

	if (file != NULL)
	{
		fclose(file);
		file = NULL;
	}
	curl = NULL;
}

/**
 * test how to use http basic authenticate.
 */
void curl_main_test_http_auth()
{
	CURL *curl;
	CURLcode r;

	curl = curl_easy_init();
	if (!curl)
	{
		DEBUG_FAILURE("curl_easy_init");
		return;
	}

	curl_easy_setopt(curl, CURLOPT_URL, URL_LINUX_IDC_HTTP_AUTH);
	curl_easy_setopt(curl, CURLOPT_USERPWD, "www.linuxidc.com:www.linuxidc.com");
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	r = curl_easy_perform(curl);
	if (r != CURLE_OK)
	{
		DEBUG_FAILURE("curl_easy_perform");
	}
	curl_easy_cleanup(curl);
	curl = NULL;
}

size_t curl_main_test_write_data_file(void *buffer, size_t size, size_t nmemb, void *data)
{
	FILE *file;

	file = (FILE*) data;
	if (file == NULL)
	{
		file = stdout;
	}
	fwrite(buffer, size, nmemb, file);

	return size * nmemb;
}

void curl_main_test_http_post()
{
	CURL *curl;
	struct curl_slist *header;
	const char *data = "name=daniel&project=curl";

	curl = curl_easy_init();
	if (!curl)
	{
		DEBUG_FAILURE("curl_easy_init");
		return;
	}

	header = NULL;
	header = curl_slist_append(header, "Content-Type: text/xml");

	curl_easy_setopt(curl, CURLOPT_URL, URL_HTTP_POST_POSTHERE);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	// curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 23L);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	if (CURLE_OK != curl_easy_perform(curl))
	{
		DEBUG_FAILURE("curl_easy_perform");
	}
	curl_easy_cleanup(curl);
	curl_slist_free_all(header);
	header = NULL;
	curl = NULL;
}

/**
 * CURLOPT_FOLLOWLOCATION 1L to enable auto redirect.
 * CURLINFO_REDIRECT_URL to get the location.
 * CURLINFO_REDIRECT_COUNT to get the redirect count.
 */
void curl_main_test_get_info()
{
	CURL *curl;
	FILE *file;
	long status_code;
	long filetime;
	long n;
	char *url;
	char *header_value;
	double v;

	file = NULL;
	curl = curl_easy_init();
	if (!curl)
	{
		DEBUG_FAILURE("curl_easy_init");
		return;
	}

	file = fopen("/dev/null", "a+");
	if (!file)
	{
		DEBUG_FAILURE("fopen");
	}

	curl_easy_setopt(curl, CURLOPT_URL, URL_BAIDU_HOME);
	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
	if (file)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	}
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_perform(curl);

	fprintf(stdout, "\n");
	if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code))
	{
		fprintf(stdout, "Http Response Code=%ld\n", status_code);
	}

	if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime))
	{
		fprintf(stdout, "File time:%ld\n", filetime);
	}

	url = NULL;
	n = 0L;
	if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &url)
			&& CURLE_OK == curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT, &n))
	{
		fprintf(stdout, "Http redirect url:%s count=%ld\n", url, n);
	}

	if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &v))
	{
		n = (long) v;
		if (n != -1)
		{
			fprintf(stdout, "Content-Length:%ld\n", n);
		}
	}

	if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &header_value))
	{
		fprintf(stdout, "Content-Type:%s\n", header_value);
	}
	CURL_FINISH:
	if (file != NULL)
	{
		fclose(file);
		file = NULL;
	}
	curl_easy_cleanup(curl);
	curl = NULL;
}
#endif
