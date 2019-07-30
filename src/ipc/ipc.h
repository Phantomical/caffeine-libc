#include "syscall.h"

#define IPCOP_semop      1
#define IPCOP_semget     2
#define IPCOP_semctl     3
#define IPCOP_semtimedop 4
#define IPCOP_msgsnd    11
#define IPCOP_msgrcv    12
#define IPCOP_msgget    13
#define IPCOP_msgctl    14
#define IPCOP_shmat     21
#define IPCOP_shmdt     22
#define IPCOP_shmget    23
#define IPCOP_shmctl    24

#ifndef IPC_64
#define IPC_64 0x100
#endif
