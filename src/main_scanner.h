/*
 * main_scanner.h
 *
 *  Created on: 2015年4月19日
 *      Author: lhb
 */

#ifndef MAIN_SCANNER_H
#define MAIN_SCANNER_H

#include <stdio.h>
#include <stdlib.h>

struct main_scanner
{
	char *buffer;
	int size;
	int capacity;
	int next;
	FILE *fp;
};

void main_scanner_initial(struct main_scanner *scanner, FILE *fp);
void main_scanner_release(struct main_scanner *scanner);
char* main_scanner_next_line(struct main_scanner *scanner);

void main_scanner_test();

#endif // MAIN_SCANNER_H
