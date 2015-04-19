/*
 * main_scanner.cpp
 *
 *  Created on: 2015年4月19日
 *      Author: lhb
 */

#include <string.h>

#include "main_scanner.h"
#include "main_utils.h"

#define SCANNER_NEXT_NONE -1
#define SCANNER_BUFFER_SIZE	1024

void main_scanner_initial(struct main_scanner *scanner, FILE *fp)
{
	scanner->buffer = NULL;
	scanner->size = 0;
	scanner->capacity = 0;
	scanner->fp = fp;
	scanner->next = SCANNER_NEXT_NONE;
}

void main_scanner_release(struct main_scanner *scanner)
{
	if (scanner)
	{
		if (scanner->buffer)
		{
			free(scanner->buffer);
			scanner->buffer = NULL;
		}
		scanner->size = scanner->capacity = 0;
		scanner->fp = NULL;
	}
}

char *main_scanner_next_line(struct main_scanner *scanner)
{
	char *p;
	int s;
	int n;
	int eof;

	if (!scanner || !scanner->fp)
	{
		return NULL;
	}

	if (scanner->size > 0)
	{
		memcpy(scanner->buffer, scanner->buffer + scanner->next, scanner->size);
		scanner->buffer[scanner->size] = E_CHAR;
	}

	s = 0;
	p = NULL;
	eof = 0;
	while (true)
	{
		p = NULL;
		if (s < scanner->size)
		{
			if ((p = strchr(scanner->buffer + s, '\n')) != NULL)
			{
				scanner->next = p - scanner->buffer + 1;
				scanner->size -= scanner->next;
				*p = E_CHAR;
				break;
			}
			else
			{
				s = scanner->size;
			}
		}
		else
		{
			if (eof)
			{
				scanner->size = 0;
				scanner->next = SCANNER_NEXT_NONE;
				break;
			}
		}

		// 扩展内存
		if (scanner->size + SCANNER_BUFFER_SIZE > scanner->capacity)
		{
			scanner->capacity += SCANNER_BUFFER_SIZE;
			if (scanner->buffer)
			{
				scanner->buffer = (char*) realloc(scanner->buffer, scanner->capacity);
			}
			else
			{
				scanner->buffer = (char*) malloc(sizeof(char) * scanner->capacity);
				scanner->buffer[0] = E_CHAR;
			}
		}

		n = (int) fread(scanner->buffer + scanner->size, 1, (scanner->capacity - scanner->size - 1),
				scanner->fp);
		scanner->size += n;
		scanner->buffer[scanner->size] = E_CHAR;
		if (n == 0)
		{
			eof = 1;
		}
	}

	if (n == 0 && scanner->buffer[0] == E_CHAR)
	{
		return NULL;
	}
	return scanner->buffer;
}

//################################################################################################//
// 测试代码

void main_scanner_test()
{
	FILE *fp;
	char *p;
	main_scanner scanner;
	int isFirst;

	fp = fopen("D:\\workspace_cpp\\Main\\strchr.html", "r");
	if (!fp)
	{
		return;
	}

	main_scanner_initial(&scanner, fp);
	isFirst = 1;
	while ((p = main_scanner_next_line(&scanner)))
	{
		if (!isFirst)
		{
			fprintf(stdout, "\n");
		}
		isFirst = 0;
		fprintf(stdout, "%s", p);
	}
	main_scanner_release(&scanner);

	fclose(fp);
	fp = NULL;
}
