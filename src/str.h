#ifndef _STR_H_
#define _STR_H_

#include <string.h>

#define INLINE static inline

struct _str {
	char *s;
	int len;
};
typedef struct _str str;

/* inits a str object from any binary string. returns out */
INLINE str *str_init_len(str *out, char *s, int len);
/* shifts pointer by len chars and decrements len. returns -1 if buffer too short, 0 otherwise */
INLINE int str_shift(str *s, int len);
/* shifts the string by given length and returns the shifted part. returns -1 if string is too short */
INLINE int str_shift_ret(str *s, int len, str *ret);
INLINE int str_shift(str *s, int len) {
	return str_shift_ret(s, len, NULL);
}
INLINE int str_shift_ret(str *s, int len, str *ret) {
	if (s->len < len)
		return -1;
	if (ret)
		str_init_len(ret, s->s, len);
	s->s += len;
	s->len -= len;
	return 0;
}
INLINE str *str_init_len(str *out, char *s, int len) {
	out->s = s;
	out->len = len;
	return out;
}

#endif
