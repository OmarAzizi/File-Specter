#ifndef FILE_SPECTER_H
#define FILE_SPECTER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/inotify.h>
#include <libnotify/notify.h>
#include <libnotify/notification.h>
#include <pthread.h>

// exit codes
#define     THREAD_ERROR                   -1
#define     EXIT_SUCCESS                    0
#define     EXIT_FALIURE                    1
#define     EXIT_ERROR_INIT_INOTIFY         2
#define     EXIT_ERROR_FILE_MAY_NOT_EXIST   3
#define     EXIT_ERROR_BASE_PATH_NULL       4
#define     EXIT_ERROR_READ_INOTIFY         5
#define     EXIT_ERROR_INIT_LIBNOTIFY       6
#define     EXIT_ERROR_BUFFER_OVERFLOW      7

char* get_filename_from_path(char*);
void run_filespecter(char**);
void handle_events(char*);
void* notify(void*);
void signal_handler(int);

#endif
