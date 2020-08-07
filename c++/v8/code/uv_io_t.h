
#define UV_IO_PRIVATE_PLATFORM_FIELDS /* empty */

struct uv__io_s {
    uv__io_cb cb;
    void* pending_queue[2];
    void* watcher_queue[2];
    unsigned int pevents; /* Pending event mask i.e. mask at next tick. */
    unsigned int events;  /* Current event mask. */
    int fd;
    UV_IO_PRIVATE_PLATFORM_FIELDS
};

typedef struct uv__io_s uv__io_t;