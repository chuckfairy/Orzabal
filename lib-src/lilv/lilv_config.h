//Cache of file

#ifndef W_LILV_CONFIG_H_WAF
#define W_LILV_CONFIG_H_WAF

#define HAVE_GCOV 1
#define HAVE_FLOCK 1
#define HAVE_FILENO 1
#define HAVE_CLOCK_GETTIME 1
#define HAVE_LIBDL 1
#define LILV_VERSION "0.24.2"
#define LILV_PATH_SEP ":"
#define LILV_DIR_SEP "/"

#if __APPLE__
#define LILV_DEFAULT_LV2_PATH "~/.lv2:/usr/lib/lv2:/usr/local/lib/lv2:/Library/Audio/Plug-Ins/LV2/"
#else
#define LILV_DEFAULT_LV2_PATH "~/.lv2:/usr/lib/lv2:/usr/local/lib/lv2"

#endif

#endif /* W_LILV_CONFIG_H_WAF */
