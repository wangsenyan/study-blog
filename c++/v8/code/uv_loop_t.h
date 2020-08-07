
#define UV_PLATFORM_LOOP_FIELDS /* empty */
#define UV_LOOP_PRIVATE_FIELDS                                                 \
  unsigned long flags;                                                         \
  int backend_fd;                                                              \
  void* pending_queue[2];                                                      \
  void* watcher_queue[2];                                                      \
  uv__io_t** watchers;                                                         \
  unsigned int nwatchers;                                                      \
  unsigned int nfds;                                                           \
  void* wq[2];                                                                 \
  uv_mutex_t wq_mutex;                                                         \
  uv_async_t wq_async;                                                         \
  uv_rwlock_t cloexec_lock;                                                    \
  uv_handle_t* closing_handles;                                                \
  void* process_handles[2];                                                    \
  void* prepare_handles[2];                                                    \
  void* check_handles[2];                                                      \
  void* idle_handles[2];                                                       \
  void* async_handles[2];                                                      \
  void (*async_unused)(void); /* TODO(bnoordhuis) Remove in libuv v2. */       \
  uv__io_t async_io_watcher;                                                   \
  int async_wfd;                                                               \
  struct {                                                                     \
    void* min;                                                                 \
    unsigned int nelts;                                                        \
  } timer_heap;                                                                \
  uint64_t timer_counter;                                                      \
  uint64_t time;                                                               \
  int signal_pipefd[2];                                                        \
  uv__io_t signal_io_watcher;                                                  \
  uv_signal_t child_watcher;                                                   \
  int emfile_fd;                                                               \
  UV_PLATFORM_LOOP_FIELDS

struct uv_loop_s {
    /* User data - use this for whatever. */
    void* data;
    /* Loop reference counting. */
    //是uv_loop_t 的引用计数，每投递一个uv_handle_t 或 uv_req_t 都会使其递增，结束会递减
    unsigned int active_handles;
    //是uv_handle_t族的队列
    void* handle_queue[2];
    //是uv_req_t族的队列
    union {
        void* unused[2];
        unsigned int count;
    } active_reqs;
    /* Internal flag to signal loop stop. */
    unsigned int stop_flag;
    UV_LOOP_PRIVATE_FIELDS
};

typedef struct uv_loop_s uv_loop_t;