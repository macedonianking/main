#ifndef MAIN_STRING_BUILDER_H

struct main_string_builder;

void main_string_builder_acquire(int capacity, struct main_string_builder **builder);
void main_string_builder_release(struct main_string_builder *builder);

char *main_string_builder_data(struct main_string_builder *builder);

void main_string_builder_append_char(struct main_string_builder *builder, char n);
void main_string_builder_append_int(struct main_string_builder *builder, int n);
void main_string_builder_append_long(struct main_string_builder *builder, long n);
void main_string_builder_append_text(struct main_string_builder *builder, const char *text);
void main_string_builder_append_format(struct main_string_builder *builder, const char *format, ...);

void main_string_builder_test();

#endif // MAIN_STRING_BUILDER_H