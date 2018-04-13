package com.libfifo;

import android.content.Context;

public class GlobalConfig {

    private static GlobalConfig mInstance = null;
    private Context mApplicationContext;

    /**
     * @WARNING initialize the object before you use it.
     */
    public static GlobalConfig instance() {
        if (null == mInstance) {
            mInstance = new GlobalConfig();
        }
        return mInstance;
    }

    public void init(Context context) {
        if (null != context) {
            mApplicationContext = context.getApplicationContext();
        }
    }

    public Context getApplicationContext() {
        return mApplicationContext;
    }
}
