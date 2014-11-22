/* Last update: "balloc.h: 2013-04-04 (Thu)  14:09:08 BRT (tk)" */

/*! @file balloc.h
 *
 * @brief Simple controlled memory allocation utility
 *
 * May be used freely under for any purpose
 *
 * <p>Author: Tomasz Kowaltowski</p>
 * <p>Inspired by a package by C. L. Lucchesi</p>
 *
 * <b>history</b>
 * <p>2006-07-26 initial version</p>
 * <p>2013-04-04 added block size and block filling with 0s in freeing
 */

#ifndef __BALLOC_DEFINED
#define __BALLOC_DEFINED

#include <stdlib.h>

/**
 * Convenience defintions replacing standard \code malloc and \code
 * free function calls.
 */

#define MALLOC(n)     balloc(__FILE__,__LINE__,n)
#define FREE(ptr)     bfree(ptr)

/**
 * Allocates and registers a memory block.
 * @param who caller file name
 * @param where caller line number
 * @param n number of bytes to be allocated
 * @return a pointer to the allocated area (NULL if not available)
 */
void *balloc(char *who, int where, size_t n);

/**
 * Frees a memory block if registered.
 * @param ptr the pointer to the block to be freed
 * @return 0 if operation successful; 
 *         1 if attempt to free a NULL pointer;
 *         2 if attempt to free an unregistered pointer 
 */
int bfree(void *ptr);

/**
 * Gets info about the next registered memory block which was not
 * freed yet, and frees it before returning.
 * @param who upon return will contain caller file name in which the
 * function \ref balloc was called
 * @param where upon return will contain caller line number in which the
 * function \ref balloc was called
 * @return 0 if successful; 
 *         1 if unsuccessful (no more blocks to free)
 */
int bnextfree(char **who, int *where);

/**
 * Frees all remaining registered blocks.
 */
void bfreeall();

/**
 * Counts registered memory to be freed.
 * @returns the number of blocks to be freed (possibly 0)
 */
int bcheck();

/**
 * Function argument prototype for \ref bapply.
 * @param who caller file name
 * @param where caller line number
 * @param ptr memory block pointer
 */
typedef void bfunc(char *who, int where, void *ptr, size_t size);

/**
 * Applies a function of type \ref bfunc to each block to be freed;
 * blocks remain registered.  
 * @param bf function to be applied
 */
void bapply(bfunc *bf);

#endif
