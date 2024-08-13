#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "common.h"
#include "encode.h"

static const char B64TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char TABLE[] = "0123456789abcdef";


size_t size_b64encode(const char *str){
    return ((4 * ((strlen(str) + 2) / 3)) + 1);
}

size_t size_b64decode(const char *str){
    return ((strlen(str) * 3) / 4);
}

size_t size_urlencode(const char *str){
    return ((strlen(str) * 3) + 1);
}

size_t size_urldecode(const char *str){
    return ((strlen(str) / 3) + 1);
}

void b64encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            outbuf[index++] = B64TABLE[(buf[pos] >> 2)];
            outbuf[index++] = B64TABLE[(((buf[pos] & 3) << 4) | (buf[pos + 1] >> 4))];
            if((inlen - pos) > 1)
                outbuf[index++] = B64TABLE[(((buf[pos + 1] & 15) << 2) | (buf[pos + 2] >> 6))];
            else
                outbuf[index++] = '=';
            if((inlen - pos) > 2)
                outbuf[index++] = B64TABLE[(buf[pos + 2] & 63)];
            else
                outbuf[index++] = '=';
            pos += 3;
        }
        outbuf[index] = '\0';
    }
}


void b64decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t pos = 0;
    size_t index = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < outlen){
            buf[index++] = ((int)(strchr(B64TABLE, inbuf[pos]) - B64TABLE) << 2) | ((int)(strchr(B64TABLE, inbuf[pos + 1]) - B64TABLE) >> 4);
            if(inbuf[pos + 2] != '=')
                buf[index++] = (((int)(strchr(B64TABLE, inbuf[pos + 1]) - B64TABLE) & 15) << 4) | ((int)(strchr(B64TABLE, inbuf[pos + 2]) - B64TABLE) >> 2);
            if(inbuf[pos + 3] != '=')
                buf[index++] = (((int)(strchr(B64TABLE, inbuf[pos + 2]) - B64TABLE) & 3) << 6) | (int)(strchr(B64TABLE, inbuf[pos + 3]) - B64TABLE);
            pos += 4;
        }
        buf[index] = '\0';
    }
}


void urlencode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            outbuf[index++] = '%';
            outbuf[index++] = TABLE[buf[pos] >> 4];
            outbuf[index++] = TABLE[buf[pos++] & 15];
        }
        outbuf[index] = '\0';
    }
}

void urldecode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < outlen){
            buf[index++] = ((int)(strchr(TABLE, inbuf[pos + 1]) - TABLE) << 4) | (int)(strchr(TABLE, inbuf[pos + 2]) - TABLE);
            pos += 3;
        }
        buf[index] = '\0';
    }
}


void b16encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            outbuf[index++] = TABLE[buf[pos] >> 4];
            outbuf[index++] = TABLE[buf[pos++] & 15];
        }
        outbuf[index] = '\0';
    }
}


void b16decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < outlen){
            buf[index++] = ((int)(strchr(TABLE, inbuf[pos]) - TABLE) << 4) | (int)((strchr(TABLE, inbuf[pos + 1])) - TABLE);
            pos += 2;
        }
        buf[index] = '\0';
    }
}


/*void md5(const char *inbuf, const size_t inlen, char *outbuf){
    MD5_CTX ctx_md5;
    unsigned char hash[MD5_DIGEST_LENGTH] = {'\0'};
    if(inbuf && outbuf && inlen > 0){
        MD5_Init(&ctx_md5);
        MD5_Update(&ctx_md5, inbuf, inlen);
        MD5_Final(hash, &ctx_md5);
        b16encode(hash, MD5_DIGEST_LENGTH, outbuf, MD5_LEN_HASH + 1);
    }
}


void sha1(const char *inbuf, const size_t inlen, char *outbuf){
    SHA_CTX ctx_sha1;
    unsigned char hash[SHA_DIGEST_LENGTH] = {'\0'};
    if(inbuf && outbuf && inlen > 0){
        SHA1_Init(&ctx_sha1);
        SHA1_Update(&ctx_sha1, inbuf, inlen);
        SHA1_Final(hash, &ctx_sha1);
        b16encode(hash, SHA_DIGEST_LENGTH, outbuf, SHA1_LEN_HASH + 1);
    }
}


void sha256(const char *inbuf, const size_t inlen, char *outbuf){
    SHA256_CTX ctx_sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH] = {'\0'};
    if(inbuf && outbuf && inlen > 0){
        SHA256_Init(&ctx_sha256);
        SHA256_Update(&ctx_sha256, inbuf, inlen);
        SHA256_Final(hash, &ctx_sha256);
        b16encode(hash, SHA256_DIGEST_LENGTH, outbuf, SHA256_LEN_HASH + 1);
    }
}

void sha512(const char *inbuf, const size_t inlen, char *outbuf){
    SHA512_CTX ctx_sha512;
    unsigned char hash[SHA512_DIGEST_LENGTH] = {'\0'};
    if(inbuf && outbuf && inlen > 0){
        SHA512_Init(&ctx_sha512);
        SHA512_Update(&ctx_sha512, inbuf, inlen);
        SHA512_Final(hash, &ctx_sha512);
        b16encode(hash, SHA512_DIGEST_LENGTH, outbuf, SHA512_LEN_HASH + 1);
    }
}*/
