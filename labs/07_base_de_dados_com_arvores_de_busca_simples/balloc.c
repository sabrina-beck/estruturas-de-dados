/* Last update: "balloc.c: 2013-04-04 (Thu)  14:10:46 BRT (tk)" */

/*! @file balloc.c
 *
 * @brief Simple controlled memory allocation utility implementation
 *
 * <b>history:</b> See balloc.h
 */

#include "balloc.h"
#include <string.h>

/**
 * Structure used to register allocated blocks
 */
typedef struct Register_Tag {
  struct Register_Tag *next;  /**< next registered block */
  void *ptr;                  /**< pointer to the allocated block */
  char *who;                  /**< caller file name */
  int where;                  /**< caller line number */
  size_t size;                  /**< allocated block size */
} Register;

/**
 * Linked list head. Field 'where' will be used as a counter for
 * registered blocks.
 */
Register head = {NULL,NULL,0};

/* Auxiliary */

void auxfree(Register **p) {

  Register *q = *p;
  *p = q->next;
  memset(q->ptr,0,q->size);
  free(q->ptr);
  free(q);
  head.where--;
  return;
  
} /* auxfree */

/* API implementation */

void *balloc(char *who, int where, size_t n) {

  void *p;
  Register *r = malloc(sizeof(Register));
  if (r==NULL)
    return NULL;
  p = malloc(n);
  if (p==NULL) {
    free(r);
    return NULL;
  }
  r->next = head.next;
  r->ptr = p;
  r->who = who;
  r->where = where;
  r->size = n;
  head.next = r;
  head.where++;
  return p;
  
} /* balloc */

int bfree(void *ptr) {
  
  Register **p;
  if (ptr==NULL)
    return 1;      // attempt to free a NULL pointer
  for (p=&(head.next); (((*p)!=NULL)&&(((*p)->ptr)!=ptr)); p=&((*p)->next)) {
    // advance through the list
  }
  if ((*p)==NULL)  // attempt to free an unregistered pointer 
    return 2;
  auxfree(p);
  return 0;        // OK

} /* bfree */

int bnextfree(char **who, int *where) {

  Register *p = head.next;
  if (p==NULL)
    return 1;
  *who = p->who;
  *where = p->where;
  auxfree(&(head.next));
  return 0;
  
} /* bnextfree */

void bfreeall() {

  while (head.next!=NULL)
    auxfree(&(head.next));
  
} /* bfreeall */

int bcheck() {

  return head.where;
  
} /* bcheck */

void bapply(bfunc *bf) {

  Register *p;
  for (p=head.next;p!=NULL;p=p->next)
    bf(p->who,p->where,p->ptr,p->size);

} /* bapply */
