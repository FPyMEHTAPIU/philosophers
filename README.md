# philosophers
Implementation of the classic dining philosophers problem using threads and mutexes. The project demonstrates synchronization techniques to prevent race conditions and deadlocks in a multithreaded environment.

## What Was Done:

- Implemented multithreading with `pthread_create`, `pthread_join`, and `pthread_detach`.
- Used **mutexes** to manage access to shared resources and **prevent race conditions**.
- Designed algorithms to **avoid deadlock**s while ensuring all philosophers could eat without starving.
- Managed execution timing using `gettimeofday` and `usleep`.
- Created a robust `Makefile` for compiling and managing the project.
