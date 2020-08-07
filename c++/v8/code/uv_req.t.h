
#define UV_REQ_PRIVATE_FIELDS                                                  \
  union {                                                                      \
    /* Used by I/O operations */                                               \
    struct {                                                                   \
      OVERLAPPED overlapped;                                                   \
      size_t queued_bytes;                                                     \
    } io;                                                                      \
  } u;                                                                         \
  struct uv_req_s* next_req;

#define UV_REQ_FIELDS                                                          \
  /* public */                                                                 \
  void* data;                                                                  \
  /* read-only */                                                              \
  uv_req_type type;                                                            \
  /* private */                                                                \
  void* reserved[6];                                                           \
  UV_REQ_PRIVATE_FIELDS

struct uv_req_s {
    UV_REQ_FIELDS
};
typedef struct uv_req_s uv_req_t;