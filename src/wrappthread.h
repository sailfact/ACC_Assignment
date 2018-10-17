#include	"acc.h"
#include 	"error.h"

void Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg);
void Pthread_join(pthread_t tid, void **status);
void Pthread_detach(pthread_t tid);
void Pthread_kill(pthread_t tid, int signo);
void Pthread_mutexattr_init(pthread_mutexattr_t *attr);
#ifdef	_POSIX_THREAD_PROCESS_SHARED
void Pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int flag);
#endif

void Pthread_mutex_init(pthread_mutex_t *mptr, pthread_mutexattr_t *attr);
void Pthread_mutex_lock(pthread_mutex_t *mptr);
void Pthread_mutex_unlock(pthread_mutex_t *mptr);
void Pthread_cond_broadcast(pthread_cond_t *cptr);
void Pthread_cond_signal(pthread_cond_t *cptr);
void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);
void Pthread_cond_timedwait(pthread_cond_t *cptr, pthread_mutex_t *mptr, const struct timespec *tsptr);
void Pthread_once(pthread_once_t *ptr, void (*func)(void));
void Pthread_key_create(pthread_key_t *key, void (*func)(void *));
void Pthread_setspecific(pthread_key_t key, const void *value);