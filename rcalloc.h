#ifndef RCALLOC_INCLUDED
#define RCALLOC_INCLUDED

struct rc_alloc_context_t {
  void (*dealloc)(void *ptr);
};

extern void *rc_alloc(struct rc_alloc_context_t *ctx, long nbytes);
extern void *rc_calloc(struct rc_alloc_context_t *ctx, long count, long nbytes);
extern void *rc_realloc(void *ptr, long nbytes);
extern void *rc_retain(void *ptr);
extern void rc_release(void **ptr);
extern size_t rc_get_retain_count(void *ptr);

#define ALLOC(nbytes) \
  rc_alloc(NULL, (nbytes))

#define ALLOC_WITH_CTX(ctx, nbytes) \
  rc_alloc((ctx), (nbytes))

#define CALLOC(count, nbytes) \
  rc_calloc(NULL, (count), (nbytes))

#define CALLOC_WITH_CTX(ctx, count, nbytes) \
  rc_calloc((ctx), (count), (nbytes))

#define REALLOC(p, nbytes) \
  rc_realloc((p), (nbytes))

#define RETAIN(p) \
  rc_retain((void *)(p))

#define RELEASE(p) \
  rc_release((void **)&(p))

#define NEW(p) \
  ((p) = ALLOC((long)sizeof *(p)))

#define NEW_WITH_CTX(ctx, p) \
  ((p) = ALLOC_WITH_CTX((ctx), (long)sizeof *(p)))

#define NEW0(p) \
  ((p) = CALLOC(1, (long)sizeof *(p)))

#define NEW0_WITH_CTX(ctx, p) \
  ((p) = CALLOC_WITH_CTX((ctx), 1, (long)sizeof *(p)))

#define GET_RETAIN_COUNT(p) \
  rc_get_retain_count((void *)(p))

#endif
