#ifndef MAIN_LOCAL_SIGNAL_H
#define MAIN_LOCAL_SIGNAL_H

// ≤‚ ‘≥Ã–Ú»Îø⁄
void main_signal_test();

void (*main_set_local_handler(int signo, void (*handler)(int)))(int);
void main_do_local_signal(int singo);
void main_release_local_handlers();

#endif // MAIN_LOCAL_SIGNAL_H
