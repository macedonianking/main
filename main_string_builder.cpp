#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>

#include "main_string_builder.h"
#include "main_utils.h"

#define STRING_BUILDER_DEFAULT_CAPACITY 	1024

struct main_string_builder
{
	char 	*data;
	int		size;
	int		capacity;
};

static void main_string_builder_capacity_check(struct main_string_builder *builder, int target);

void main_string_builder_acquire(int capacity, struct main_string_builder **data)
{
	char *ptr;

	if (capacity < 0)
	{
		capacity = STRING_BUILDER_DEFAULT_CAPACITY;
	}

	ptr = (char *) malloc(sizeof(char) * capacity);
	if (ptr == NULL)
	{
		*data = NULL;
		return;
	}

	*data = (struct main_string_builder*) malloc(sizeof(main_string_builder));
	if (*data == NULL)
	{
		return;
	}

	(*data)->capacity = capacity;
	(*data)->size = 0;
	(*data)->data = ptr;
	memset(ptr, 0, capacity);
}

void main_string_builder_release(struct main_string_builder *data)
{
	if (data != NULL) {
		if (data->data != NULL) {
			free(data->data);
			data->data = NULL;
		}
		free(data);
	}
}

void main_string_builder_capacity_check(struct main_string_builder *builder, int target)
{
	int capacity;

	if (builder->capacity < target)
	{
		capacity = builder->capacity + STRING_BUILDER_DEFAULT_CAPACITY;
		if (capacity < target)
		{
			capacity = target;
		}
		builder->data = (char*) realloc(builder->data, capacity);
		builder->capacity = capacity;
	}
}

void main_string_builder_append_char(struct main_string_builder *builder, char n)
{
	main_string_builder_capacity_check(builder, builder->size + 2);

	builder->data[builder->size] = (char) n;
	++builder->size;
	builder->data[builder->size] = E_CHAR;
}

void main_string_builder_append_int(struct main_string_builder *builder, int n)
{
	char buffer[100];

	snprintf(buffer, 100, "%d", n);
	main_string_builder_append_text(builder, buffer);
}

void main_string_builder_append_text(struct main_string_builder *builder, const char *text)
{
	int n;
	char *iter;

	n = strlen(text);
	main_string_builder_capacity_check(builder, builder->size + n + 1);
	iter = builder->data + builder->size;
	builder->size += n;
	while (n > 0)
	{
		*(iter++) = *(text++);
		--n;
	}
	builder->data[builder->size] = E_CHAR;
}

void main_string_builder_append_format(struct main_string_builder *builder, const char *format, ...)
{
	char buffer[1024];
	va_list vaList;

	va_start(vaList, format);
	vsprintf(buffer, format, vaList);
	va_end(vaList);
	buffer[1023] = '\0';

	main_string_builder_append_text(builder, buffer);
}

char *main_string_builder_data(struct main_string_builder *builder)
{
	return builder->data;
}

void main_string_builder_test()
{
	struct main_string_builder *builder;

	builder = NULL;
	main_string_builder_acquire(1024, &builder);
	if (builder == NULL)
	{
		fprintf(stderr, "%s failure\n", "main_string_builder_acquire");
		return;
	}

	main_string_builder_append_char(builder, 'n');
	printf("%s\n", builder->data);

	main_string_builder_append_int(builder, 100);
	printf("%s\n", builder->data);

	main_string_builder_append_text(builder, "Hello world");
	printf("%s\n", builder->data);

	main_string_builder_append_format(builder, "%s %s", "A", "Bs");
	printf("%s\n", builder->data);

	main_string_builder_release(builder);
}