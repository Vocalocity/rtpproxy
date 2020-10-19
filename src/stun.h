#ifndef _STUN_H_
#define _STUN_H_


/*
#include <string.h>
*/
#include <arpa/inet.h>
/*
#include <sys/types.h>
#include "compat.h"
#include "call.h"
*/
#include "str.h"
/*
#include "socket.h"
*/


#define PASSWORD "on3mbLYv18aG3uI7+2w90QY"

struct ice_agent {
	str pwd[2];
};
struct call_media {
	struct ice_agent *ice_agent;
};
struct packet_stream {
	struct call_media *media;
};
struct socket {
	int fd;
};
struct stream_fd {
	struct socket socket;
	struct packet_stream *stream;
};

struct socket_family {
	int af;
};
struct socket_address {
	struct socket_family *family;
	union {
		struct in_addr ipv4;
		struct in6_addr ipv6;
	} u;
};
struct endpoint {
	struct socket_address address;
	unsigned int port;
	struct sockaddr_in *sin;
};

typedef struct endpoint endpoint_t;
#define ZERO(x) memset(&(x), 0, sizeof(x))

#define STUN_COOKIE 0x2112A442UL



struct stun_attrs {
	str username;
	char *msg_integrity_attr;
	str msg_integrity;
	u_int32_t priority;
	char *fingerprint_attr;
	u_int32_t fingerprint;
	u_int64_t tiebreaker;
	endpoint_t mapped;
	unsigned int error_code;
	int use:1,
	    controlled:1,
	    controlling:1;
};


INLINE int is_stun(const str *s) {
	const unsigned char *b = (const void *) s->s;
	const u_int32_t *u;

	if (s->len < 20)
		return 0;
	if ((b[0] & 0xc0) != 0x00)
		return 0;
	if ((b[3] & 0x3) != 0x0)
		return 0;
	u = (const void *) &b[4];
	if (*u != htonl(STUN_COOKIE))
		return 0;

	return 1;
}


int stun(const str *, struct stream_fd *, const endpoint_t *);

#if 0
int stun_binding_request(const endpoint_t *dst, u_int32_t transaction[3], str *pwd,
		str ufrags[2], int controlling, u_int64_t tiebreaker, u_int32_t priority,
		socket_t *, int);
#endif

#endif
