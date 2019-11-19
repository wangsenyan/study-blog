#include <pthread.h>
struct task_struct
{
  /*
	 * offsets of these are hardcoded elsewhere - touch with care
	 */
  volatile long state; /* -1 unrunnable, 0 runnable, >0 stopped */
  unsigned long flags; /* per process flags, defined below */
  int sigpending;
  mm_segment_t addr_limit; /* thread address space:
					 	0-0xBFFFFFFF for user-thead
						0-0xFFFFFFFF for kernel-thread
					 */
  struct exec_domain *exec_domain;
  volatile long need_resched;
  unsigned long ptrace;

  int lock_depth; /* Lock depth */

  /*
 * offset 32 begins here on 32-bit platforms. We keep
 * all fields in a single cacheline that are needed for
 * the goodness() loop in schedule().
 */
  long counter;
  long nice;
  unsigned long policy;
  struct mm_struct *mm;
  int processor;
  /*
	 * cpus_runnable is ~0 if the process is not running on any
	 * CPU. It's (1 << cpu) if it's running on a CPU. This mask
	 * is updated under the runqueue lock.
	 *
	 * To determine whether a process might run on a CPU, this
	 * mask is AND-ed with cpus_allowed.
	 */
  unsigned long cpus_runnable, cpus_allowed;
  /*
	 * (only the 'next' pointer fits into the cacheline, but
	 * that's just fine.)
	 */
  struct list_head run_list;
  unsigned long sleep_time;

  struct task_struct *next_task, *prev_task;
  struct mm_struct *active_mm;
  struct list_head local_pages;
  unsigned int allocation_order, nr_local_pages;

  /* task state */
  struct linux_binfmt *binfmt;
  int exit_code, exit_signal;
  int pdeath_signal; /*  The signal sent when the parent dies  */
  /* ??? */
  unsigned long personality;
  int did_exec : 1;
  pid_t pid;
  pid_t pgrp;
  pid_t tty_old_pgrp;
  pid_t session;
  pid_t tgid;
  /* boolean value for session group leader */
  int leader;
  /* 
	 * pointers to (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with 
	 * p->p_pptr->pid)
	 */
  struct task_struct *p_opptr, *p_pptr, *p_cptr, *p_ysptr, *p_osptr;
  struct list_head thread_group;

  /* PID hash table linkage. */
  struct task_struct *pidhash_next;
  struct task_struct **pidhash_pprev;

  wait_queue_head_t wait_chldexit; /* for wait4() */
  struct completion *vfork_done;   /* for vfork() */
  unsigned long rt_priority;
  unsigned long it_real_value, it_prof_value, it_virt_value;
  unsigned long it_real_incr, it_prof_incr, it_virt_incr;
  struct timer_list real_timer;
  struct tms times;
  unsigned long start_time;
  long per_cpu_utime[NR_CPUS], per_cpu_stime[NR_CPUS];
  /* mm fault and swap info: this can arguably be seen as either mm-specific or thread-specific */
  unsigned long min_flt, maj_flt, nswap, cmin_flt, cmaj_flt, cnswap;
  int swappable : 1;
  /* process credentials */
  uid_t uid, euid, suid, fsuid;
  gid_t gid, egid, sgid, fsgid;
  int ngroups;
  gid_t groups[NGROUPS];
  kernel_cap_t cap_effective, cap_inheritable, cap_permitted;
  int keep_capabilities : 1;
  struct user_struct *user;
  /* limits */
  struct rlimit rlim[RLIM_NLIMITS];
  unsigned short used_math;
  char comm[16];
  /* file system info */
  int link_count, total_link_count;
  struct tty_struct *tty; /* NULL if no tty */
  unsigned int locks;     /* How many file locks are being held */
                          /* ipc stuff */
  struct sem_undo *semundo;
  struct sem_queue *semsleeping;
  /* CPU-specific state of this task */
  struct thread_struct thread;
  /* filesystem information */
  struct fs_struct *fs;
  /* open file information */
  struct files_struct *files;
  /* signal handlers */
  spinlock_t sigmask_lock; /* Protects signal and blocked */
  struct signal_struct *sig;

  sigset_t blocked;
  struct sigpending pending;

  unsigned long sas_ss_sp;
  size_t sas_ss_size;
  int (*notifier)(void *priv);
  void *notifier_data;
  sigset_t *notifier_mask;

  /* Thread group tracking */
  u32 parent_exec_id;
  u32 self_exec_id;
  /* Protection of (de-)allocation: mm, files, fs, tty */
  spinlock_t alloc_lock;

  /* journalling filesystem info */
  void *journal_info;
};
//与进程相关的文件
struct fs_struct
{
  atomic_t count; //共享这个表的进程个数
  rwlock_t lock;  //用于表中字段的读/写自旋锁
  int umask;      //当打开文件设置文件权限时所使用的位掩码
  struct dentry *root, *pwd, *altroot;
  //根目录的目录项
  //当前工作目录的目录项
  //模拟根目录的目录项（在80x86结构上始终为NULL）
  struct vfsmount *rootmnt, *pwdmnt, *altrootmnt;
  //根目录所安装的文件系统对象
  //当前工作目录所安装的文件系统对象
  //模拟根目录所安装的文件系统对象（在80x86结构上始终为NULL）
};

//文件描述符标志
struct files_struct
{
  atomic_t count;
  struct fdtable *fdt;
  struct fdtable fdtab;

  spinlock_t file_lock ____cacheline_aligned_in_smp;
  int next_fd;
  struct embedded_fd_set close_on_exec_init;
  struct embedded_fd_set open_fds_init;
  struct file *fd_array[NR_OPEN_DEFAULT];
};

struct fdtable
{
  unsigned int max_fds;
  int max_fdset;
  struct file **fd; /* current fd array */
  fd_set *close_on_exec;
  fd_set *open_fds;
  struct rcu_head rcu;
  struct files_struct *free_files;
  struct fdtable *next;
};