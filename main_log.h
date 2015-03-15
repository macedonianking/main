#ifndef MAIN_LOG_H
#define MAIN_LOG_H

#include "main_config.h"

#if MAIN_DEBUG_ENABLED
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_FAILURE(msg) fprintf(stderr, msg" failure:%s %d\n", __FILE__, __LINE__);

#else

#define DEBUG_FAILURE(msg)

#endif // MAIN_DEBUG_ENABLED

#endif // MAIN_LOG_H