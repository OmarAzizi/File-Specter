#ifndef FILE_SPECTER_H
#define FILE_SPECTER_H

#include <sys/inotify.h>

// exit codes
#define     EXIT_SUCCESS                    0
#define     EXIT_FALIURE                    1
#define     EXIT_ERROR_INIT_INOTIFY         2
#define     EXIT_ERROR_FILE_MAY_NOT_EXIST   3
#define     EXIT_ERROR_BASE_PATH_NULL       4
#define     EXIT_ERROR_READ_INOTIFY         5

char* get_filename_from_path(char*);
void run_filespecter(char**);
void handle_events(int, char*);
void check(const struct inotify_event*, char*);

#endif
