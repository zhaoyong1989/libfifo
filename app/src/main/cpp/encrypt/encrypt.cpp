//
// Created by 赵勇 on 2018/4/18.
//

#include "encrypt.h"

#define LOG_TAG "zhaoyong1"

int Encrypt::base64Encode(unsigned char *indata, int inlen, char **outdata) {
    long len;
    long str_len;
    char *res;
    int i,j;
    //定义base64编码表
    char *base64_table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    //计算经过base64编码后的字符串长度
    str_len = inlen;
    if(str_len % 3 == 0)
        len = str_len/3*4;
    else
        len = (str_len/3+1)*4;

    res = (char*)malloc(sizeof(unsigned char)*len+1);
    res[len] = '\0';

    //以3个8位字符为一组进行编码
    for(i=0,j=0; i<len-2; j+=3,i+=4)
    {
        res[i] = base64_table[indata[j]>>2]; //取出第一个字符的前6位并找出对应的结果字符
        res[i+1] = base64_table[(indata[j]&0x3)<<4 | (indata[j+1]>>4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        res[i+2] = base64_table[(indata[j+1]&0xf)<<2 | (indata[j+2]>>6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        res[i+3] = base64_table[indata[j+2]&0x3f]; //取出第三个字符的后6位并找出结果字符
    }

    switch(str_len % 3)
    {
        case 1:
            res[i-2] = '=';
            res[i-1] = '=';
            break;
        case 2:
            res[i-1] = '=';
            break;
    }

    *outdata = res;

    return 0;
}

int Encrypt::base64Decode(const char *indata, byte **outdata, long *outlen) {

    //根据base64表，以字符找到对应的十进制数据
    int table[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,54,55,56,57,58,59,60,61,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
    long len;
    long str_len;
    int i,j;
    byte *res;

    //计算解码后的字符串长度
    len = strlen(indata);
    //判断编码后的字符串后是否有=
    if(strstr(indata,"=="))
        str_len = len/4*3-2;
    else if(strstr(indata,"="))
        str_len = len/4*3-1;
    else
        str_len = len/4;

    res = (byte*)malloc(sizeof(unsigned char)*str_len+1);
    //outdata[str_len]='\0';

    //以4个字符为一位进行解码
    for(i=0,j=0; i < len-2; j+=3,i+=4)
    {
        res[j] = ((unsigned char)table[indata[i]])<<2 | (((unsigned char)table[indata[i+1]])>>4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合
        res[j+1] = (((unsigned char)table[indata[i+1]])<<4) | (((unsigned char)table[indata[i+2]])>>2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合
        res[j+2] = (((unsigned char)table[indata[i+2]])<<6) | ((unsigned char)table[indata[i+3]]); //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
    }

    *outlen = str_len;
    *outdata = res;

    return 0;
}

byte *Encrypt::encrypt(const char *strSource, long* outlen) {
    byte even_xor = random();
    byte odd_xor = random();
    byte skip = random();
    byte pad = random();
    return encrypt(strSource, even_xor, odd_xor, skip, pad, outlen);
}

byte *Encrypt::encrypt(const char *strSource, byte even_xor,
                       byte odd_xor, byte skip, byte pad, long* outlen) {
    byte *data_bytes = (byte *) strSource;
    int len = strlen(strSource);
    int all = 12 + len + skip + pad;
    byte *result = new byte[MAX(0, all)];
    *outlen = MAX(0, all);

    result[0] = (byte) 0xff;
    result[1] = (byte) 0xff;
    result[2] = (byte) 0xff;
    result[3] = (byte) 0xfe;
    result[4] = even_xor;
    result[5] = odd_xor;
    result[6] = skip;
    result[7] = pad;
    int index = 8;
    for (int i = skip - 1; i >= 0; --i) {
        result[index + i] = random();
    }
    index += skip;
    result[index] = (byte) (len >> 24 & 0xff ^ even_xor);
    result[index + 1] = (byte) (len >> 16 & 0xff ^ odd_xor);
    result[index + 2] = (byte) (len >> 8 & 0xff ^ even_xor);
    result[index + 3] = (byte) (len & 0xff ^ odd_xor);
    index += 4;
    for (int i = len - 1; i >= 0; --i) {
        result[index + i] = (byte) (data_bytes[i] ^ ((i & 1) == 0 ? even_xor : odd_xor));
    }
    index += len;
    for (int i = pad - 1; i >= 0; --i) {
        result[index + i] = random();
    }

    return result;
}

char *Encrypt::decrypt(byte *strSource, long inlen) {
    if (inlen > 12) {
        if (strSource[0] == (byte) 0xff
            && strSource[1] == (byte) 0xff
            && strSource[2] == (byte) 0xff
            && strSource[3] == (byte) 0xfe) {
            byte even_xor = strSource[4];
            byte odd_xor = strSource[5];
            byte skip = strSource[6];
            byte pad = strSource[7];
            int length = (strSource[skip + 8] & 0xff ^ even_xor) << 24
                         | (strSource[skip + 9] & 0xff ^ odd_xor) << 16
                         | (strSource[skip + 10] & 0xff ^ even_xor) << 8
                         | (strSource[skip + 11] & 0xff ^ odd_xor);
            if (length == (inlen - 12 - skip - pad)) {
                char *result = new char[length];
                int offset = skip + 12;
                for (int i = length - 1; i >= 0; i--) {
                    result[i] = (byte) (strSource[offset + i] ^
                                        ((i & 1) == 0 ? even_xor : odd_xor));
                }
                return result;
            }
        }
    }
    return new char[0];
}

byte Encrypt::random() {
    return (byte) ((int)((double)rand() / RAND_MAX * 0x7f) % 8);
}