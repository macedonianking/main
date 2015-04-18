#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_HANDLER_BUFFER_SIZE	16

struct signo_handler_entity
{
	int 	signo;
	void 	(*handler)(int);
	struct signo_handler_entity *next;
};

static signo_handler_entity *gHandlerBuffer[MAX_HANDLER_BUFFER_SIZE] = {};

// ²âÊÔµÄÀý×Ó
static void main_signal_handler(int signo);
static void main_signal_process(int signo);

void (*local_signal(int signo, void (*handler)(int)))(int)
{
	struct signo_handler_entity **ptr, *next;
	void (*old_handler)(int);

	ptr = &gHandlerBuffer[signo % MAX_HANDLER_BUFFER_SIZE];

	while (*ptr != NULL && (*ptr)->signo > signo)
	{
		ptr = &(*ptr)->next;
	}

	old_handler = NULL;
	if (handler == NULL)
	{
		if (*ptr != NULL && (*ptr)->signo == signo)
		{
			old_handler = (*ptr)->handler;
			(*ptr)->handler = handler;
			next = (*ptr)->next;
			free(*ptr);
			*ptr = next;
		}
		return old_handler;
	}

	if (*ptr == NULL)
	{
		/**
		 * Meet and end
		 */
		*ptr = (struct signo_handler_entity*) malloc(sizeof(struct signo_handler_entity));
		(*ptr)->signo = signo;
		(*ptr)->handler = handler;
		(*ptr)->next = NULL;
	}
	else if ((*ptr)->signo == signo)
	{
		old_handler = (*ptr)->handler;
		(*ptr)->handler = handler;
	}
	else
	{
		next = (*ptr)->next;
		*ptr = (struct signo_handler_entity*) malloc(sizeof(struct  signo_handler_entity));
		(*ptr)->signo = signo;
		(*ptr)->handler = handler;
		(*ptr)->next = next;
	}

	return old_handler;
}

void do_local_signal(int signo)
{
	struct signo_handler_entity *ptr;

	ptr = gHandlerBuffer[signo % MAX_HANDLER_BUFFER_SIZE];
	while (ptr != NULL && ptr->signo > signo)
	{
		ptr = ptr->next;
	}

	if (ptr != NULL && ptr->signo == signo && ptr->handler != NULL)
	{
		(*(ptr->handler))(signo);
	}
}

void release_local_signal_handlers()
{
	int i;
	struct signo_handler_entity **ptr, *next;

	for (i = 0; i < MAX_HANDLER_BUFFER_SIZE; ++i)
	{
		ptr = &gHandlerBuffer[i];

		while (*ptr != NULL)
		{
			next = (*ptr)->next;
			free(*ptr);
			*ptr = next;
		}
	}
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
	printf("main_signal_handler:signo=%d\n", signo);
}

void main_signal_process(int signo)
{
	printf("main_signal_process:signo=%d\n", signo);
}
