package com.entgroup;

import java.nio.charset.StandardCharsets;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * 加密算法工具类
 *
 * @author yu
 */
public class Encrypt {

    /**
     * 加密数据
     *
     * @param data 需要加密的数据
     */
    public static byte[] encrypt(String data) {
        byte even_xor = random();
        byte odd_xor = random();
        byte skip = random();
        byte pad = random();
        return encrypt(data, even_xor, odd_xor, skip, pad);
    }

    private static byte random() {
        return (byte) (Math.random() * 0x7f % 8);
    }

    private static byte[] encrypt(String data, byte even_xor, byte odd_xor, byte skip, byte pad) {
        final byte[] data_bytes = data.getBytes(StandardCharsets.UTF_8);
        final int len = data_bytes.length;
        final int all = 12 + len + skip + pad;
        byte[] result = new byte[Math.max(0, all)];
        try {
            //-2
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
            result[index]     = (byte) (len >> 24 & 0xff ^ even_xor);
            result[index + 1] = (byte) (len >> 16 & 0xff ^ odd_xor);
            result[index + 2] = (byte) (len >> 8  & 0xff ^ even_xor);
            result[index + 3] = (byte) (len       & 0xff ^ odd_xor);
            index += 4;
            for (int i = len - 1; i >= 0; --i) {
                result[index + i] = (byte) (data_bytes[i] ^ ((i & 1) == 0 ? even_xor : odd_xor));
            }
            index += len;
            for (int i = pad - 1; i >= 0; --i) {
                result[index + i] = random();
            }
        } catch (Exception e) {
            Logger.getLogger(Encrypt.class.getName()).log(
                    Level.WARNING,
                    String.format("encrypt error, all:%s, data.length:%s, exor:%s, oxor:%s, skip:%s, pad:%s",
                            all, len, even_xor, odd_xor, skip, pad),
                    e);
        }
        return result;
    }
}
