#ifndef W_SERD_CONFIG_H_WAF
#define W_SERD_CONFIG_H_WAF

#define HAVE_GCOV 1
#define HAVE_POSIX_MEMALIGN 1


#if ! __APPLE__
#define HAVE_POSIX_FADVISE 1
#endif

#define HAVE_FILENO 1
#define SERD_VERSION "0.26.0"

#endif /* W_SERD_CONFIG_H_WAF */
