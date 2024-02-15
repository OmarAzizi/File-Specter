# Flie Specter ⛓️
![C Icon](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)

1. [About File Specter](#about-file-specter)
2. [Demo](#demo)
3. [The Reason Behind This](#the-reason-behind-It)
4. [Installation & Usage](#installation--usage)
5. [Daemon Implementation](#daemon-implementation)
    - [Monitoring The Files](#monitoring-the-files)
    - [Multithreading](#multithreading)
    - [Desktop Notifications](#desktop-notifications)

## About File Specter
The file inspector or as I like to call it **File Specter** is a multithreaded Linux [Daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) that monitors your files and notifies you via desktop notifications if they have been accessed.

## Demo



https://github.com/OmarAzizi/File-Specter/assets/110500643/bcc2db88-33ef-4cef-9f4d-6d0c0634ef88




## The Reason Behind It
The main reason I created this daemon is primarily because I'm trying to teach myself systems-level programming in UNIX-based systems and familiarize myself with the available system libraries and their APIs. So this is probably not the best way I could write a daemon as I'm still learning. Therefore, if you have any suggestions for improvement or if you spot any bugs, you can contribute to this repository or reach out to me, so I can learn from it.

## Installation & Usage
In order to install open the terminal and write:
```bash
git clone https://github.com/OmarAzizi/File-Specter.git
```
Then change your directory and build the project:
```bash
cd File-Specter
make filespecter
```
To run it properly you need to give it the path to the file you want to monitor, so you need to run it as follows:
```bash
./filespecterd <path>
```

## Daemon Implementation
### Monitoring The Files
To monitor the files I used the [inotify API](https://man7.org/linux/man-pages/man7/inotify.7.html), which provides a mechanism for monitoring filesystem events.

### Multithreading
I used threads in the daemon so that instead of doing the work sequentially, it can monitor the file and report any changes or access to it on different threads. Therefore, they run in parallel and they wont wait for each other to finish executing inorder to run. To get that done, I used the [POSIX threads (Pthreads)](https://man7.org/linux/man-pages/man7/pthreads.7.html).

### Desktop Notifications
To show the user that his file has been accessed, instead of printing it to the **syslog**, I used the [libnotify](https://developer-old.gnome.org/libnotify/unstable/ch01.html) notification API to do that in real-time.
