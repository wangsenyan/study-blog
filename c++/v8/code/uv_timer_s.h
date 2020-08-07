#define UV_HANDLE_PRIVATE_FIELDS                                               \
  uv_handle_t* endgame_next;                                                   \
  unsigned int flags;//是否停止

#define UV_HANDLE_FIELDS                                                       \
  /* public */                                                                 \
  void* data;                                                                  \
  /* read-only */                                                              \
  uv_loop_t* loop;                                                             \
  uv_handle_type type;                                                         \
  /* private */                                                                \
  uv_close_cb close_cb;                                                        \
  void* handle_queue[2];                                                       \
  union {                                                                      \
    int fd;                                                                    \
    void* reserved[4];                                                         \
  } u;                                                                         \
  UV_HANDLE_PRIVATE_FIELDS

#define UV_TIMER_PRIVATE_FIELDS                                                \
  void* heap_node[3];                                                          \
  int unused;                                                                  \
  uint64_t timeout;                                                            \
  uint64_t repeat;                                                             \
  uint64_t start_id;                                                           \
  uv_timer_cb timer_cb;


struct uv_timer_s {
    UV_HANDLE_FIELDS
        UV_TIMER_PRIVATE_FIELDS
};

typedef struct uv_timer_s uv_timer_t;
