#include "file_specter.h"

int inotify_fd;
int inotify_wd;

uint32_t inotify_mask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF;

char* get_filename_from_path(char* basePath) {
    char* token = strtok(basePath, "/");
    while (token != NULL) { 
        basePath = token;
        token = strtok(NULL, "/");
    }
    return basePath;
}

void run_filespecter(char** argv) {
    char* full_path = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    strcpy(full_path, argv[1]);
    
    char* filename = get_filename_from_path(full_path);

    if (filename == NULL) {
        fprintf(stderr, "ERROR: Cannot get base path.\n");
        exit(EXIT_ERROR_BASE_PATH_NULL);
    }

    inotify_fd = inotify_init();
    if (inotify_fd == -1) {
        fprintf(stderr, "ERROR: Cannot Initialize inotify instance.\n");
        exit(EXIT_ERROR_INIT_INOTIFY);
    }

    inotify_wd = inotify_add_watch(inotify_fd, argv[1], inotify_mask);
    if (inotify_wd == -1) {
        fprintf(stderr, "ERROR: Cannot add file to watch instance (file may not exist).\n");
        exit(EXIT_ERROR_FILE_MAY_NOT_EXIST);
    }

    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    while (true) handle_events(filename);
}

void handle_events(char* filename) {
    printf("Waiting for event....\n");
    char buffer[4096];
    const struct inotify_event* event;
    ssize_t len;

    len = read(inotify_fd, buffer, sizeof(buffer)); // reads some events into the buffer
                                                    
    if (len == -1) {
        fprintf(stderr, "ERROR: Cannot read from inotify instance\n");
        exit(EXIT_ERROR_READ_INOTIFY);
    }

    /* Loop over all events in the buffer. */
    for (char* ptr = buffer; ptr < buffer + len; ptr += sizeof(struct inotify_event) + event->len) {
        event = (const struct inotify_event*)ptr;
        check(event, filename);
    }
}

void check(const struct inotify_event* event, char* filename) {
    char* notification;
    notification = NULL;

    if (event->mask & IN_CREATE) notification = "IN_CREATE: File have been created.\n";
	if (event->mask & IN_DELETE) notification = "IN_DELETE: File have been deleted.\n";
	if (event->mask & IN_ACCESS) notification = "IN_ACCESS: File have been accessed.\n";
	if (event->mask & IN_CLOSE_WRITE) notification = "IN_CLOSE_WRITE: File have been written and closed.\n";
	if (event->mask & IN_MODIFY) notification = "IN_MODIFY: File have been modified.\n";
    if (event->mask & IN_MOVE_SELF) notification = "IN_MOVE_SELF: File have been moved.\n";
    
    if (notification == NULL) return;
    notify(filename, notification);
}

void notify(char* filename, char* message) {
    bool libnotify_init_status = notify_init("File Specter");

    if (!libnotify_init_status) {
        fprintf(stderr, "ERROR: Cannot initialize libnotify instance (libnotify may be missing).\n");
        exit(EXIT_ERROR_INIT_LIBNOTIFY);
    }

    NotifyNotification* notification = notify_notification_new(filename, message, NULL);
    if (notification == NULL) {
        fprintf(stderr, "ERROR: Notification handle was null.\n");
        return; 
    }

    notify_notification_show(notification, NULL);
}

void signal_handler(int signal) {
    printf("\nSignal received, cleaning up...\n");
    
    int close_status = inotify_rm_watch(inotify_fd, inotify_wd);
    if (close_status == -1)
        fprintf(stderr, "ERROR: Cannot remove the inotify instance\n");

    close(inotify_fd);

    exit(EXIT_SUCCESS);
}
