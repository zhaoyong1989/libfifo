//
// Created by 赵勇 on 2018/4/18.
//

#ifndef LIBFIFO_ENCRYPT_H
#define LIBFIFO_ENCRYPT_H

#include <memory.h>
#include "../tools/CommonTools.h"

class Encrypt {
private:
    static byte random();
    static byte* encrypt(const char* strSource, byte even_xor, byte odd_xor, byte skip, byte pad, long* outlen);

public:

    static int base64Decode(const char *indata, byte **outdata, long *outlen);

    static int base64Encode(unsigned char *indata, int inlen, char **outdata);

    static char* decrypt(byte* strSource, long length);

    static byte* encrypt(const char* strSource, long* outlen);
};

#endif //LIBFIFO_ENCRYPT_H
