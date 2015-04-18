#ifndef MAIN_LOCAL_SIGNAL_H
#define MAIN_LOCAL_SIGNAL_H

void (*local_signal(int signo, void (*handler)(int)))(int);
void do_local_signal(int singo);
void release_local_signal_handlers();

#endif // MAIN_LOCAL_SIGNAL_H