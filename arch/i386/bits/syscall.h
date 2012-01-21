#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) __SYSCALL_LL_E((x))

static inline long __syscall0(long __n)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n) : "memory");
	return __ret;
}

#ifndef __PIC__

static inline long __syscall1(long __n, long __a1)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1) : "memory");
	return __ret;
}

static inline long __syscall2(long __n, long __a1, long __a2)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2) : "memory");
	return __ret;
}

static inline long __syscall3(long __n, long __a1, long __a2, long __a3)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3) : "memory");
	return __ret;
}

static inline long __syscall4(long __n, long __a1, long __a2, long __a3, long __a4)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4) : "memory");
	return __ret;
}

static inline long __syscall5(long __n, long __a1, long __a2, long __a3, long __a4, long __a5)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5) : "memory");
	return __ret;
}

static inline long __syscall6(long __n, long __a1, long __a2, long __a3, long __a4, long __a5, long __a6)
{
	unsigned long __ret;
	__asm__ __volatile__ ("pushl %7 ; pushl %%ebp ; mov 4(%%esp),%%ebp ; int $128 ; popl %%ebp ; popl %%ecx"
		: "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5), "g"(__a6) : "memory");
	return __ret;
}

#else

static inline long __syscall1(long __n, long __a1)
{
	unsigned long __ret;
	__asm__ __volatile__ ("xchg %2,%%ebx ; int $128 ; xchg %2,%%ebx"
		: "=a"(__ret) : "a"(__n), "r"(__a1) : "memory");
	return __ret;
}

static inline long __syscall2(long __n, long __a1, long __a2)
{
	unsigned long __ret;
	__asm__ __volatile__ ("xchg %2,%%ebx ; int $128 ; xchg %2,%%ebx"
		: "=a"(__ret) : "a"(__n), "r"(__a1), "c"(__a2) : "memory");
	return __ret;
}

static inline long __syscall3(long __n, long __a1, long __a2, long __a3)
{
	unsigned long __ret;
	__asm__ __volatile__ ("xchg %2,%%ebx ; int $128 ; xchg %2,%%ebx"
		: "=a"(__ret) : "a"(__n), "r"(__a1), "c"(__a2), "d"(__a3) : "memory");
	return __ret;
}

static inline long __syscall4(long __n, long __a1, long __a2, long __a3, long __a4)
{
	unsigned long __ret;
	__asm__ __volatile__ ("xchg %2,%%ebx ; int $128 ; xchg %2,%%ebx"
		: "=a"(__ret) : "a"(__n), "r"(__a1), "c"(__a2), "d"(__a3), "S"(__a4) : "memory");
	return __ret;
}

#if 0
static inline long __syscall5(long __n, long __a1, long __a2, long __a3, long __a4, long __a5)
{
	unsigned long __ret;
	__asm__ __volatile__ ("pushl %2 ; pushl %%ebx ; mov 4(%%esp),%%ebx ; int $128 ; popl %%ebx ; popl %%ecx"
		: "=a"(__ret) : "a"(__n), "g"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5) : "memory");
	return __ret;
}
#else
static inline long __syscall5(long __n, long __a1, long __a2, long __a3, long __a4, long __a5)
{
	return (__syscall)(__n, __a1, __a2, __a3, __a4, __a5);
}
#endif

static inline long __syscall6(long __n, long __a1, long __a2, long __a3, long __a4, long __a5, long __a6)
{
	return (__syscall)(__n, __a1, __a2, __a3, __a4, __a5, __a6);
}

#endif


#define __SC_socket      1
#define __SC_bind        2
#define __SC_connect     3
#define __SC_listen      4
#define __SC_accept      5
#define __SC_getsockname 6
#define __SC_getpeername 7
#define __SC_socketpair  8
#define __SC_send        9
#define __SC_recv        10
#define __SC_sendto      11
#define __SC_recvfrom    12
#define __SC_shutdown    13
#define __SC_setsockopt  14
#define __SC_getsockopt  15
#define __SC_sendmsg     16
#define __SC_recvmsg     17

#define __socketcall(nm,a,b,c,d,e,f) syscall(SYS_socketcall, __SC_##nm, \
    ((long [6]){ (long)a, (long)b, (long)c, (long)d, (long)e, (long)f }))
#define __socketcall_cp(nm,a,b,c,d,e,f) syscall_cp(SYS_socketcall, __SC_##nm, \
    ((long [6]){ (long)a, (long)b, (long)c, (long)d, (long)e, (long)f }))

#define __NR_restart_syscall      0
#define __NR_exit		  1
#define __NR_fork		  2
#define __NR_read		  3
#define __NR_write		  4
#define __NR_open		  5
#define __NR_close		  6
#define __NR_waitpid		  7
#define __NR_creat		  8
#define __NR_link		  9
#define __NR_unlink		 10
#define __NR_execve		 11
#define __NR_chdir		 12
#define __NR_time		 13
#define __NR_mknod		 14
#define __NR_chmod		 15
#define __NR_lchown		 16
#define __NR_break		 17
#define __NR_oldstat		 18
#define __NR_lseek		 19
#define __NR_getpid		 20
#define __NR_mount		 21
#define __NR_umount		 22
#define __NR_setuid		 23
#define __NR_getuid		 24
#define __NR_stime		 25
#define __NR_ptrace		 26
#define __NR_alarm		 27
#define __NR_oldfstat		 28
#define __NR_pause		 29
#define __NR_utime		 30
#define __NR_stty		 31
#define __NR_gtty		 32
#define __NR_access		 33
#define __NR_nice		 34
#define __NR_ftime		 35
#define __NR_sync		 36
#define __NR_kill		 37
#define __NR_rename		 38
#define __NR_mkdir		 39
#define __NR_rmdir		 40
#define __NR_dup		 41
#define __NR_pipe		 42
#define __NR_times		 43
#define __NR_prof		 44
#define __NR_brk		 45
#define __NR_setgid		 46
#define __NR_getgid		 47
#define __NR_signal		 48
#define __NR_geteuid		 49
#define __NR_getegid		 50
#define __NR_acct		 51
#define __NR_umount2		 52
#define __NR_lock		 53
#define __NR_ioctl		 54
#define __NR_fcntl		 55
#define __NR_mpx		 56
#define __NR_setpgid		 57
#define __NR_ulimit		 58
#define __NR_oldolduname	 59
#define __NR_umask		 60
#define __NR_chroot		 61
#define __NR_ustat		 62
#define __NR_dup2		 63
#define __NR_getppid		 64
#define __NR_getpgrp		 65
#define __NR_setsid		 66
#define __NR_sigaction		 67
#define __NR_sgetmask		 68
#define __NR_ssetmask		 69
#define __NR_setreuid		 70
#define __NR_setregid		 71
#define __NR_sigsuspend		 72
#define __NR_sigpending		 73
#define __NR_sethostname	 74
#define __NR_setrlimit		 75
#define __NR_getrlimit		 76   /* Back compatible 2Gig limited rlimit */
#define __NR_getrusage		 77
#define __NR_gettimeofday	 78
#define __NR_settimeofday	 79
#define __NR_getgroups		 80
#define __NR_setgroups		 81
#define __NR_select		 82
#define __NR_symlink		 83
#define __NR_oldlstat		 84
#define __NR_readlink		 85
#define __NR_uselib		 86
#define __NR_swapon		 87
#define __NR_reboot		 88
#define __NR_readdir		 89
#define __NR_mmap		 90
#define __NR_munmap		 91
#define __NR_truncate		 92
#define __NR_ftruncate		 93
#define __NR_fchmod		 94
#define __NR_fchown		 95
#define __NR_getpriority	 96
#define __NR_setpriority	 97
#define __NR_profil		 98
#define __NR_statfs		99
#define __NR_fstatfs		100
#define __NR_ioperm		101
#define __NR_socketcall		102
#define __NR_syslog		103
#define __NR_setitimer		104
#define __NR_getitimer		105
#define __NR_stat		106
#define __NR_lstat		107
#define __NR_fstat		108
#define __NR_olduname		109
#define __NR_iopl		110
#define __NR_vhangup		111
#define __NR_idle		112
#define __NR_vm86old		113
#define __NR_wait4		114
#define __NR_swapoff		115
#define __NR_sysinfo		116
#define __NR_ipc		117
#define __NR_fsync		118
#define __NR_sigreturn		119
#define __NR_clone		120
#define __NR_setdomainname	121
#define __NR_uname		122
#define __NR_modify_ldt		123
#define __NR_adjtimex		124
#define __NR_mprotect		125
#define __NR_sigprocmask	126
#define __NR_create_module	127
#define __NR_init_module	128
#define __NR_delete_module	129
#define __NR_get_kernel_syms	130
#define __NR_quotactl		131
#define __NR_getpgid		132
#define __NR_fchdir		133
#define __NR_bdflush		134
#define __NR_sysfs		135
#define __NR_personality	136
#define __NR_afs_syscall	137
#define __NR_setfsuid		138
#define __NR_setfsgid		139
#define __NR__llseek		140
#define __NR_getdents		141
#define __NR__newselect		142
#define __NR_flock		143
#define __NR_msync		144
#define __NR_readv		145
#define __NR_writev		146
#define __NR_getsid		147
#define __NR_fdatasync		148
#define __NR__sysctl		149
#define __NR_mlock		150
#define __NR_munlock		151
#define __NR_mlockall		152
#define __NR_munlockall		153
#define __NR_sched_setparam		154
#define __NR_sched_getparam		155
#define __NR_sched_setscheduler		156
#define __NR_sched_getscheduler		157
#define __NR_sched_yield		158
#define __NR_sched_get_priority_max	159
#define __NR_sched_get_priority_min	160
#define __NR_sched_rr_get_interval	161
#define __NR_nanosleep		162
#define __NR_mremap		163
#define __NR_setresuid		164
#define __NR_getresuid		165
#define __NR_vm86		166
#define __NR_query_module	167
#define __NR_poll		168
#define __NR_nfsservctl		169
#define __NR_setresgid		170
#define __NR_getresgid		171
#define __NR_prctl              172
#define __NR_rt_sigreturn	173
#define __NR_rt_sigaction	174
#define __NR_rt_sigprocmask	175
#define __NR_rt_sigpending	176
#define __NR_rt_sigtimedwait	177
#define __NR_rt_sigqueueinfo	178
#define __NR_rt_sigsuspend	179
#define __NR_pread64		180
#define __NR_pwrite64		181
#define __NR_chown		182
#define __NR_getcwd		183
#define __NR_capget		184
#define __NR_capset		185
#define __NR_sigaltstack	186
#define __NR_sendfile		187
#define __NR_getpmsg		188
#define __NR_putpmsg		189
#define __NR_vfork		190
#define __NR_ugetrlimit		191
#define __NR_mmap2		192
#define __NR_truncate64		193
#define __NR_ftruncate64	194
#define __NR_stat64		195
#define __NR_lstat64		196
#define __NR_fstat64		197
#define __NR_lchown32		198
#define __NR_getuid32		199
#define __NR_getgid32		200
#define __NR_geteuid32		201
#define __NR_getegid32		202
#define __NR_setreuid32		203
#define __NR_setregid32		204
#define __NR_getgroups32	205
#define __NR_setgroups32	206
#define __NR_fchown32		207
#define __NR_setresuid32	208
#define __NR_getresuid32	209
#define __NR_setresgid32	210
#define __NR_getresgid32	211
#define __NR_chown32		212
#define __NR_setuid32		213
#define __NR_setgid32		214
#define __NR_setfsuid32		215
#define __NR_setfsgid32		216
#define __NR_pivot_root		217
#define __NR_mincore		218
#define __NR_madvise		219
#define __NR_madvise1		219
#define __NR_getdents64		220
#define __NR_fcntl64		221
/* 223 is unused */
#define __NR_gettid		224
#define __NR_readahead		225
#define __NR_setxattr		226
#define __NR_lsetxattr		227
#define __NR_fsetxattr		228
#define __NR_getxattr		229
#define __NR_lgetxattr		230
#define __NR_fgetxattr		231
#define __NR_listxattr		232
#define __NR_llistxattr		233
#define __NR_flistxattr		234
#define __NR_removexattr	235
#define __NR_lremovexattr	236
#define __NR_fremovexattr	237
#define __NR_tkill		238
#define __NR_sendfile64		239
#define __NR_futex		240
#define __NR_sched_setaffinity	241
#define __NR_sched_getaffinity	242
#define __NR_set_thread_area	243
#define __NR_get_thread_area	244
#define __NR_io_setup		245
#define __NR_io_destroy		246
#define __NR_io_getevents	247
#define __NR_io_submit		248
#define __NR_io_cancel		249
#define __NR_fadvise64		250
/* 251 is available for reuse (was briefly sys_set_zone_reclaim) */
#define __NR_exit_group		252
#define __NR_lookup_dcookie	253
#define __NR_epoll_create	254
#define __NR_epoll_ctl		255
#define __NR_epoll_wait		256
#define __NR_remap_file_pages	257
#define __NR_set_tid_address	258
#define __NR_timer_create	259
#define __NR_timer_settime	(__NR_timer_create+1)
#define __NR_timer_gettime	(__NR_timer_create+2)
#define __NR_timer_getoverrun	(__NR_timer_create+3)
#define __NR_timer_delete	(__NR_timer_create+4)
#define __NR_clock_settime	(__NR_timer_create+5)
#define __NR_clock_gettime	(__NR_timer_create+6)
#define __NR_clock_getres	(__NR_timer_create+7)
#define __NR_clock_nanosleep	(__NR_timer_create+8)
#define __NR_statfs64		268
#define __NR_fstatfs64		269
#define __NR_tgkill		270
#define __NR_utimes		271
#define __NR_fadvise64_64	272
#define __NR_vserver		273
#define __NR_mbind		274
#define __NR_get_mempolicy	275
#define __NR_set_mempolicy	276
#define __NR_mq_open 		277
#define __NR_mq_unlink		(__NR_mq_open+1)
#define __NR_mq_timedsend	(__NR_mq_open+2)
#define __NR_mq_timedreceive	(__NR_mq_open+3)
#define __NR_mq_notify		(__NR_mq_open+4)
#define __NR_mq_getsetattr	(__NR_mq_open+5)
#define __NR_kexec_load		283
#define __NR_waitid		284
/* #define __NR_sys_setaltroot	285 */
#define __NR_add_key		286
#define __NR_request_key	287
#define __NR_keyctl		288
#define __NR_ioprio_set		289
#define __NR_ioprio_get		290
#define __NR_inotify_init	291
#define __NR_inotify_add_watch	292
#define __NR_inotify_rm_watch	293
#define __NR_migrate_pages	294
#define __NR_openat		295
#define __NR_mkdirat		296
#define __NR_mknodat		297
#define __NR_fchownat		298
#define __NR_futimesat		299
#define __NR_fstatat64		300
#define __NR_unlinkat		301
#define __NR_renameat		302
#define __NR_linkat		303
#define __NR_symlinkat		304
#define __NR_readlinkat		305
#define __NR_fchmodat		306
#define __NR_faccessat		307
#define __NR_pselect6		308
#define __NR_ppoll		309
#define __NR_unshare		310
#define __NR_set_robust_list	311
#define __NR_get_robust_list	312
#define __NR_splice		313
#define __NR_sync_file_range	314
#define __NR_tee		315
#define __NR_vmsplice		316
#define __NR_move_pages		317
#define __NR_getcpu		318
#define __NR_epoll_pwait	319
#define __NR_utimensat		320
#define __NR_signalfd		321
#define __NR_timerfd_create	322
#define __NR_eventfd		323
#define __NR_fallocate		324
#define __NR_timerfd_settime	325
#define __NR_timerfd_gettime	326
#define __NR_signalfd4		327
#define __NR_eventfd2		328
#define __NR_epoll_create1	329
#define __NR_dup3		330
#define __NR_pipe2		331
#define __NR_inotify_init1	332
#define __NR_preadv		333
#define __NR_pwritev		334
#define __NR_prlimit64		340

/* fixup legacy 16-bit junk */
#undef __NR_lchown
#undef __NR_getuid
#undef __NR_getgid
#undef __NR_geteuid
#undef __NR_getegid
#undef __NR_setreuid
#undef __NR_setregid
#undef __NR_getgroups
#undef __NR_setgroups
#undef __NR_fchown
#undef __NR_setresuid
#undef __NR_getresuid
#undef __NR_setresgid
#undef __NR_getresgid
#undef __NR_chown
#undef __NR_setuid
#undef __NR_setgid
#undef __NR_setfsuid
#undef __NR_setfsgid
#define __NR_lchown __NR_lchown32
#define __NR_getuid __NR_getuid32
#define __NR_getgid __NR_getgid32
#define __NR_geteuid __NR_geteuid32
#define __NR_getegid __NR_getegid32
#define __NR_setreuid __NR_setreuid32
#define __NR_setregid __NR_setregid32
#define __NR_getgroups __NR_getgroups32
#define __NR_setgroups __NR_setgroups32
#define __NR_fchown __NR_fchown32
#define __NR_setresuid __NR_setresuid32
#define __NR_getresuid __NR_getresuid32
#define __NR_setresgid __NR_setresgid32
#define __NR_getresgid __NR_getresgid32
#define __NR_chown __NR_chown32
#define __NR_setuid __NR_setuid32
#define __NR_setgid __NR_setgid32
#define __NR_setfsuid __NR_setfsuid32
#define __NR_setfsgid __NR_setfsgid32


/* fixup legacy 32-bit-vs-lfs64 junk */
#undef __NR_fcntl
#undef __NR_getdents
#undef __NR_ftruncate
#undef __NR_truncate
#undef __NR_stat
#undef __NR_fstat
#undef __NR_lstat
#undef __NR_statfs
#undef __NR_fstatfs
#define __NR_fcntl __NR_fcntl64
#define __NR_getdents __NR_getdents64
#define __NR_ftruncate __NR_ftruncate64
#define __NR_truncate __NR_truncate64
#define __NR_stat __NR_stat64
#define __NR_fstat __NR_fstat64
#define __NR_lstat __NR_lstat64
#define __NR_statfs __NR_statfs64
#define __NR_fstatfs __NR_fstatfs64
#define __NR_fstatat __NR_fstatat64
#define __NR_pread __NR_pread64
#define __NR_pwrite __NR_pwrite64

#define __NR_fadvise __NR_fadvise64_64

#undef __NR_getrlimit
#define __NR_getrlimit __NR_ugetrlimit

#undef __NR_select
#define __NR_select __NR__newselect


/* Repeated with SYS_ prefix */

#define SYS_restart_syscall      0
#define SYS_exit		  1
#define SYS_fork		  2
#define SYS_read		  3
#define SYS_write		  4
#define SYS_open		  5
#define SYS_close		  6
#define SYS_waitpid		  7
#define SYS_creat		  8
#define SYS_link		  9
#define SYS_unlink		 10
#define SYS_execve		 11
#define SYS_chdir		 12
#define SYS_time		 13
#define SYS_mknod		 14
#define SYS_chmod		 15
#define SYS_lchown		 16
#define SYS_break		 17
#define SYS_oldstat		 18
#define SYS_lseek		 19
#define SYS_getpid		 20
#define SYS_mount		 21
#define SYS_umount		 22
#define SYS_setuid		 23
#define SYS_getuid		 24
#define SYS_stime		 25
#define SYS_ptrace		 26
#define SYS_alarm		 27
#define SYS_oldfstat		 28
#define SYS_pause		 29
#define SYS_utime		 30
#define SYS_stty		 31
#define SYS_gtty		 32
#define SYS_access		 33
#define SYS_nice		 34
#define SYS_ftime		 35
#define SYS_sync		 36
#define SYS_kill		 37
#define SYS_rename		 38
#define SYS_mkdir		 39
#define SYS_rmdir		 40
#define SYS_dup		 41
#define SYS_pipe		 42
#define SYS_times		 43
#define SYS_prof		 44
#define SYS_brk		 45
#define SYS_setgid		 46
#define SYS_getgid		 47
#define SYS_signal		 48
#define SYS_geteuid		 49
#define SYS_getegid		 50
#define SYS_acct		 51
#define SYS_umount2		 52
#define SYS_lock		 53
#define SYS_ioctl		 54
#define SYS_fcntl		 55
#define SYS_mpx		 56
#define SYS_setpgid		 57
#define SYS_ulimit		 58
#define SYS_oldolduname	 59
#define SYS_umask		 60
#define SYS_chroot		 61
#define SYS_ustat		 62
#define SYS_dup2		 63
#define SYS_getppid		 64
#define SYS_getpgrp		 65
#define SYS_setsid		 66
#define SYS_sigaction		 67
#define SYS_sgetmask		 68
#define SYS_ssetmask		 69
#define SYS_setreuid		 70
#define SYS_setregid		 71
#define SYS_sigsuspend		 72
#define SYS_sigpending		 73
#define SYS_sethostname	 74
#define SYS_setrlimit		 75
#define SYS_getrlimit		 76   /* Back compatible 2Gig limited rlimit */
#define SYS_getrusage		 77
#define SYS_gettimeofday	 78
#define SYS_settimeofday	 79
#define SYS_getgroups		 80
#define SYS_setgroups		 81
#define SYS_select		 82
#define SYS_symlink		 83
#define SYS_oldlstat		 84
#define SYS_readlink		 85
#define SYS_uselib		 86
#define SYS_swapon		 87
#define SYS_reboot		 88
#define SYS_readdir		 89
#define SYS_mmap		 90
#define SYS_munmap		 91
#define SYS_truncate		 92
#define SYS_ftruncate		 93
#define SYS_fchmod		 94
#define SYS_fchown		 95
#define SYS_getpriority	 96
#define SYS_setpriority	 97
#define SYS_profil		 98
#define SYS_statfs		99
#define SYS_fstatfs		100
#define SYS_ioperm		101
#define SYS_socketcall		102
#define SYS_syslog		103
#define SYS_setitimer		104
#define SYS_getitimer		105
#define SYS_stat		106
#define SYS_lstat		107
#define SYS_fstat		108
#define SYS_olduname		109
#define SYS_iopl		110
#define SYS_vhangup		111
#define SYS_idle		112
#define SYS_vm86old		113
#define SYS_wait4		114
#define SYS_swapoff		115
#define SYS_sysinfo		116
#define SYS_ipc		117
#define SYS_fsync		118
#define SYS_sigreturn		119
#define SYS_clone		120
#define SYS_setdomainname	121
#define SYS_uname		122
#define SYS_modify_ldt		123
#define SYS_adjtimex		124
#define SYS_mprotect		125
#define SYS_sigprocmask	126
#define SYS_create_module	127
#define SYS_init_module	128
#define SYS_delete_module	129
#define SYS_get_kernel_syms	130
#define SYS_quotactl		131
#define SYS_getpgid		132
#define SYS_fchdir		133
#define SYS_bdflush		134
#define SYS_sysfs		135
#define SYS_personality	136
#define SYS_afs_syscall	137
#define SYS_setfsuid		138
#define SYS_setfsgid		139
#define SYS__llseek		140
#define SYS_getdents		141
#define SYS__newselect		142
#define SYS_flock		143
#define SYS_msync		144
#define SYS_readv		145
#define SYS_writev		146
#define SYS_getsid		147
#define SYS_fdatasync		148
#define SYS__sysctl		149
#define SYS_mlock		150
#define SYS_munlock		151
#define SYS_mlockall		152
#define SYS_munlockall		153
#define SYS_sched_setparam		154
#define SYS_sched_getparam		155
#define SYS_sched_setscheduler		156
#define SYS_sched_getscheduler		157
#define SYS_sched_yield		158
#define SYS_sched_get_priority_max	159
#define SYS_sched_get_priority_min	160
#define SYS_sched_rr_get_interval	161
#define SYS_nanosleep		162
#define SYS_mremap		163
#define SYS_setresuid		164
#define SYS_getresuid		165
#define SYS_vm86		166
#define SYS_query_module	167
#define SYS_poll		168
#define SYS_nfsservctl		169
#define SYS_setresgid		170
#define SYS_getresgid		171
#define SYS_prctl              172
#define SYS_rt_sigreturn	173
#define SYS_rt_sigaction	174
#define SYS_rt_sigprocmask	175
#define SYS_rt_sigpending	176
#define SYS_rt_sigtimedwait	177
#define SYS_rt_sigqueueinfo	178
#define SYS_rt_sigsuspend	179
#define SYS_pread64		180
#define SYS_pwrite64		181
#define SYS_chown		182
#define SYS_getcwd		183
#define SYS_capget		184
#define SYS_capset		185
#define SYS_sigaltstack	186
#define SYS_sendfile		187
#define SYS_getpmsg		188
#define SYS_putpmsg		189
#define SYS_vfork		190
#define SYS_ugetrlimit		191
#define SYS_mmap2		192
#define SYS_truncate64		193
#define SYS_ftruncate64	194
#define SYS_stat64		195
#define SYS_lstat64		196
#define SYS_fstat64		197
#define SYS_lchown32		198
#define SYS_getuid32		199
#define SYS_getgid32		200
#define SYS_geteuid32		201
#define SYS_getegid32		202
#define SYS_setreuid32		203
#define SYS_setregid32		204
#define SYS_getgroups32	205
#define SYS_setgroups32	206
#define SYS_fchown32		207
#define SYS_setresuid32	208
#define SYS_getresuid32	209
#define SYS_setresgid32	210
#define SYS_getresgid32	211
#define SYS_chown32		212
#define SYS_setuid32		213
#define SYS_setgid32		214
#define SYS_setfsuid32		215
#define SYS_setfsgid32		216
#define SYS_pivot_root		217
#define SYS_mincore		218
#define SYS_madvise		219
#define SYS_madvise1		219
#define SYS_getdents64		220
#define SYS_fcntl64		221
/* 223 is unused */
#define SYS_gettid		224
#define SYS_readahead		225
#define SYS_setxattr		226
#define SYS_lsetxattr		227
#define SYS_fsetxattr		228
#define SYS_getxattr		229
#define SYS_lgetxattr		230
#define SYS_fgetxattr		231
#define SYS_listxattr		232
#define SYS_llistxattr		233
#define SYS_flistxattr		234
#define SYS_removexattr	235
#define SYS_lremovexattr	236
#define SYS_fremovexattr	237
#define SYS_tkill		238
#define SYS_sendfile64		239
#define SYS_futex		240
#define SYS_sched_setaffinity	241
#define SYS_sched_getaffinity	242
#define SYS_set_thread_area	243
#define SYS_get_thread_area	244
#define SYS_io_setup		245
#define SYS_io_destroy		246
#define SYS_io_getevents	247
#define SYS_io_submit		248
#define SYS_io_cancel		249
#define SYS_fadvise64		250
/* 251 is available for reuse (was briefly sys_set_zone_reclaim) */
#define SYS_exit_group		252
#define SYS_lookup_dcookie	253
#define SYS_epoll_create	254
#define SYS_epoll_ctl		255
#define SYS_epoll_wait		256
#define SYS_remap_file_pages	257
#define SYS_set_tid_address	258
#define SYS_timer_create	259
#define SYS_timer_settime	(SYS_timer_create+1)
#define SYS_timer_gettime	(SYS_timer_create+2)
#define SYS_timer_getoverrun	(SYS_timer_create+3)
#define SYS_timer_delete	(SYS_timer_create+4)
#define SYS_clock_settime	(SYS_timer_create+5)
#define SYS_clock_gettime	(SYS_timer_create+6)
#define SYS_clock_getres	(SYS_timer_create+7)
#define SYS_clock_nanosleep	(SYS_timer_create+8)
#define SYS_statfs64		268
#define SYS_fstatfs64		269
#define SYS_tgkill		270
#define SYS_utimes		271
#define SYS_fadvise64_64	272
#define SYS_vserver		273
#define SYS_mbind		274
#define SYS_get_mempolicy	275
#define SYS_set_mempolicy	276
#define SYS_mq_open 		277
#define SYS_mq_unlink		(SYS_mq_open+1)
#define SYS_mq_timedsend	(SYS_mq_open+2)
#define SYS_mq_timedreceive	(SYS_mq_open+3)
#define SYS_mq_notify		(SYS_mq_open+4)
#define SYS_mq_getsetattr	(SYS_mq_open+5)
#define SYS_kexec_load		283
#define SYS_waitid		284
/* #define SYS_sys_setaltroot	285 */
#define SYS_add_key		286
#define SYS_request_key	287
#define SYS_keyctl		288
#define SYS_ioprio_set		289
#define SYS_ioprio_get		290
#define SYS_inotify_init	291
#define SYS_inotify_add_watch	292
#define SYS_inotify_rm_watch	293
#define SYS_migrate_pages	294
#define SYS_openat		295
#define SYS_mkdirat		296
#define SYS_mknodat		297
#define SYS_fchownat		298
#define SYS_futimesat		299
#define SYS_fstatat64		300
#define SYS_unlinkat		301
#define SYS_renameat		302
#define SYS_linkat		303
#define SYS_symlinkat		304
#define SYS_readlinkat		305
#define SYS_fchmodat		306
#define SYS_faccessat		307
#define SYS_pselect6		308
#define SYS_ppoll		309
#define SYS_unshare		310
#define SYS_set_robust_list	311
#define SYS_get_robust_list	312
#define SYS_splice		313
#define SYS_sync_file_range	314
#define SYS_tee		315
#define SYS_vmsplice		316
#define SYS_move_pages		317
#define SYS_getcpu		318
#define SYS_epoll_pwait	319
#define SYS_utimensat		320
#define SYS_signalfd		321
#define SYS_timerfd_create	322
#define SYS_eventfd		323
#define SYS_fallocate		324
#define SYS_timerfd_settime	325
#define SYS_timerfd_gettime	326
#define SYS_signalfd4		327
#define SYS_eventfd2		328
#define SYS_epoll_create1	329
#define SYS_dup3		330
#define SYS_pipe2		331
#define SYS_inotify_init1	332
#define SYS_preadv		333
#define SYS_pwritev		334
#define SYS_prlimit64		340

/* fixup legacy 16-bit junk */
#undef SYS_lchown
#undef SYS_getuid
#undef SYS_getgid
#undef SYS_geteuid
#undef SYS_getegid
#undef SYS_setreuid
#undef SYS_setregid
#undef SYS_getgroups
#undef SYS_setgroups
#undef SYS_fchown
#undef SYS_setresuid
#undef SYS_getresuid
#undef SYS_setresgid
#undef SYS_getresgid
#undef SYS_chown
#undef SYS_setuid
#undef SYS_setgid
#undef SYS_setfsuid
#undef SYS_setfsgid
#define SYS_lchown SYS_lchown32
#define SYS_getuid SYS_getuid32
#define SYS_getgid SYS_getgid32
#define SYS_geteuid SYS_geteuid32
#define SYS_getegid SYS_getegid32
#define SYS_setreuid SYS_setreuid32
#define SYS_setregid SYS_setregid32
#define SYS_getgroups SYS_getgroups32
#define SYS_setgroups SYS_setgroups32
#define SYS_fchown SYS_fchown32
#define SYS_setresuid SYS_setresuid32
#define SYS_getresuid SYS_getresuid32
#define SYS_setresgid SYS_setresgid32
#define SYS_getresgid SYS_getresgid32
#define SYS_chown SYS_chown32
#define SYS_setuid SYS_setuid32
#define SYS_setgid SYS_setgid32
#define SYS_setfsuid SYS_setfsuid32
#define SYS_setfsgid SYS_setfsgid32


/* fixup legacy 32-bit-vs-lfs64 junk */
#undef SYS_fcntl
#undef SYS_getdents
#undef SYS_ftruncate
#undef SYS_truncate
#undef SYS_stat
#undef SYS_fstat
#undef SYS_lstat
#undef SYS_statfs
#undef SYS_fstatfs
#define SYS_fcntl SYS_fcntl64
#define SYS_getdents SYS_getdents64
#define SYS_ftruncate SYS_ftruncate64
#define SYS_truncate SYS_truncate64
#define SYS_stat SYS_stat64
#define SYS_fstat SYS_fstat64
#define SYS_lstat SYS_lstat64
#define SYS_statfs SYS_statfs64
#define SYS_fstatfs SYS_fstatfs64
#define SYS_fstatat SYS_fstatat64
#define SYS_pread SYS_pread64
#define SYS_pwrite SYS_pwrite64

#define SYS_fadvise SYS_fadvise64_64

#undef SYS_getrlimit
#define SYS_getrlimit SYS_ugetrlimit

#undef SYS_select
#define SYS_select SYS__newselect
