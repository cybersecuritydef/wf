#ifndef __ENCODE_H__
#define __ENCODE_H__

/*#include <openssl/md5.h>
#include <openssl/sha.h>*/

#define MD5_LEN_HASH 32
#define SHA1_LEN_HASH 40
#define SHA256_LEN_HASH 64
#define SHA512_LEN_HASH 128

/* size buffer encode  (4 * ((strlen(string) + 2) / 3)) + 1
   size buffer decode (strlen(string) * 3) / 4
*/
size_t size_b64encode(const char *str);

size_t size_b64decode(const char *str);

void b64encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void b64decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);


void md5(const char *inbuf, const size_t inlen, char *outbuf);

void sha1(const char *inbuf, const size_t inlen, char *outbuf);

void sha256(const char *inbuf, const size_t inlen, char *outbuf);

void sha512(const char *inbuf, const size_t inlen, char *outbuf);


/* size buffer urlencode  strlen(string) * 3 + 1
   size buffer urldecode strlen(string) / 3 + 1*/

size_t size_urlencode(const char *str);

size_t size_urldecode(const char *str);

void urlencode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void urldecode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);


#endif
