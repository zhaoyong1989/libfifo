package com.entgroup;

/**
 * 解密算法工具类
 *
 * @author yu
 */
public class Decrypt {

    public static byte[] decrypt(byte[] data) {
        if (data.length > 12) {
            if (data[0] == (byte) 0xff
                    && data[1] == (byte) 0xff
                    && data[2] == (byte) 0xff
                    && data[3] == (byte) 0xfe) {
                byte even_xor = data[4];
                byte odd_xor  = data[5];
                byte skip     = data[6];
                byte pad      = data[7];
                int length = (data[skip + 8]  & 0xff ^ even_xor) << 24
                           | (data[skip + 9]  & 0xff ^ odd_xor ) << 16
                           | (data[skip + 10] & 0xff ^ even_xor) << 8
                           | (data[skip + 11] & 0xff ^ odd_xor);
                if (length == (data.length - 12 - skip - pad)) {
                    byte[] result = new byte[length];
                    int offset = skip + 12;
                    for (int i = length - 1; i >= 0; i--) {
                        result[i] = (byte) (data[offset + i] ^ ((i & 1) == 0 ? even_xor : odd_xor));
                    }
                    return result;
                }
            }
        }
        return new byte[0];
    }
}
