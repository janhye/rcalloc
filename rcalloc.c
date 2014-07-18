#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "rcalloc.h"

struct rc_object_t {
  size_t retain_count;
  void (*dealloc)(void *ptr);
};

void *rc_alloc(struct rc_alloc_context_t *ctx, long nbytes) {
  struct rc_object_t *o;
  char *p;

  assert(nbytes > 0);

  o = (struct rc_object_t *)malloc(sizeof *o + nbytes);
  if (o == NULL) 
    return NULL;

  o->retain_count = 1;
  if (ctx != NULL)
    o->dealloc = ctx->dealloc;
  else
    o->dealloc = NULL;

  p = (char *)o;
  p += sizeof *o;

  return (void *)p;
}

void *rc_calloc(struct rc_alloc_context_t *ctx, long count, long nbytes) {
  struct rc_object_t *o;
  void *p;

  assert(count > 0);
  assert(nbytes > 0);

  o = (struct rc_object_t *)calloc(1, sizeof *o + count * nbytes);
  if (o == NULL) 
    return NULL;

  o->retain_count = 1;
  if (ctx != NULL)
    o->dealloc = ctx->dealloc;
  else
    o->dealloc = NULL;

  p = (char *)o;
  p += sizeof *o;

  return (void *)p;
}

void *rc_realloc(void *ptr, long nbytes) {
  struct rc_object_t *o;
  void *p;

  assert(ptr != NULL);
  assert(nbytes > 0);

  p = (char *)ptr;
  p -= sizeof *o;
  o = (struct rc_object_t *)p;

  o = (struct rc_object_t *)realloc(o, sizeof *o + nbytes);
  if (o == NULL)
    return NULL;

  p = (char *)o;
  p += sizeof *o;

  return (void *)p;
}

void *rc_retain(void *ptr) {
  struct rc_object_t *o;
  char *p;

  assert(ptr != NULL);

  p = (char *)ptr;
  p -= sizeof *o;
  o = (struct rc_object_t *)p;
  o->retain_count++;

  return ptr;
}

void rc_release(void **ptr) {
  struct rc_object_t *o;
  char *p;

  assert(ptr != NULL);
  assert(*ptr != NULL);

  p = (char *)(*ptr);
  p -= sizeof *o;
  o = (struct rc_object_t *)p;
  o->retain_count--;

  if (o->retain_count == 0) {
    if (o->dealloc != NULL)
      o->dealloc(*ptr);

    free(o);
    *ptr = NULL;
  }
}

size_t rc_get_retain_count(void *ptr) {
  struct rc_object_t *o;
  char *p;

  assert(ptr != NULL);

  p = (char *)ptr;
  p -= sizeof *o;
  o = (struct rc_object_t *)p;
  
  return o->retain_count;
}
