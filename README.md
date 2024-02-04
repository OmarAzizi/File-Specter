# Flie Specter
![C Icon](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)

# Table of Contents 🚨
1. [About File Specter](#about-file-specter)
2. [The Reason Behind This](#the-reason-behind-It)
3. [Daemon Implementation](#daemon-implementation)
    - [Monitoring The Files](#monitoring-the-files)
    - [Multithreading](#multithreading)
## About File Specter
The file inspector or as I like to call it **File Specter** is a multithreaded Linux [Daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) that monitors your files and notifies you via desktop notifications if they have been accessed.


## The Reason Behind It
The main reason I created this daemon is primarily because I'm trying to teach myself systems-level programming in UNIX-based systems and familiarize myself with the available system libraries and their APIs. So this is probably not the best way I could write a daemon as I'm still learning. Therefore, if you have any suggestions for improvement or if you spot bugs, you can contribute to this repository or reach out to me, so I can learn from it.

## Daemon Implementation

### Monitoring The File
To monitor the files I used the [inotify API](https://man7.org/linux/man-pages/man7/inotify.7.html), which provides a mechanism for monitoring filesystem events.

### Multithreading
I used threads in the daemon so that instead of doing the work sequentially, it can monitor the file and report any changes or access to it on different threads. Therefore, they run in parallel and they wont wait for each other to finish executing inorder to run. To get that done, I used the [POSIX threads (Pthreads)](https://man7.org/linux/man-pages/man7/pthreads.7.html);
