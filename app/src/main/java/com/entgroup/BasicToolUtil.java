package com.entgroup;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;


public class BasicToolUtil {

    public static boolean isWifiState(Context context) {
        try {
            ConnectivityManager connectivity = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            if (null != connectivity) {
                NetworkInfo info = connectivity.getActiveNetworkInfo();
                if (info != null) {
                    return info.getType() == ConnectivityManager.TYPE_WIFI || info.getType() == AndroidUtil.ConnectivityManager.TYPE_ETHERNET
                            || info.getType() == ConnectivityManager.TYPE_WIMAX;
                }
            }
        } catch (Exception e) {
        }
        return false;
    }
}