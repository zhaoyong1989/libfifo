package com.libfifo;

import android.os.Handler;
import android.os.Message;

import com.entgroup.BasicToolUtil;
import com.entgroup.GlobalConfig;

public class FifoController {

	static {
		System.loadLibrary("fifo-v7a");
	}

	public static native String decryptVipPlayInfo(String encryptPlayInfo);

	public static native void createFifo(String fifoName, String channelId);

	public static native void multiStreamCreateFifo(String channelId, String bitrate);
	
	public static native void createFifo2(String channelId);

	public static native void writeFifo(byte[] bytes, int len);

	public static native void getKey(Object obj);

	public static native void closeFifo();

	public static native int getFifoLength();

	public static native int getFifoSize();
	
	public static native String getFifoVersion();
	
	public static native void setClientInfo(String platform, String id, String model);
	
	public static native void setClientInfo2(String platform, String id, String model, String device, String pid);
	
	public static native void setVLCPlayStart();
	
	public static native void setVLCVout();
	
	public static native void setVLCPlayCard();
	
	public static Boolean debugState = true;
	public static native void setDebug(boolean param);
	
	public static native double getCurrentPlayTime();
	
	public static native int checkCard(double buffersize, double vlcReadBytes);
	
	///Bytes per second
	public static native int getP2PDownloadRate();
	
	public static native int getP2PUploadRate();
	
	public static native int getCDNDownloadRate();
	
	public static native String getPlayUrl();
	
	public static native void setFifoEventHandler(FifoEventHandler eventHandler);
	
	public static native void setPlayStatus();
	public static native void setCardStatus();
	
	////////////////////////////////////////////////
	public static native void setDirectPlayStart();
	public static native void setDirectVout();
	public static native void setDirectPlayCard();
	////////////////////////////////////////////////
	
	/**
	 * 修改于20150409；为了减少客户端的逻辑，将vout和卡播上报统一起来
	 * 播放模式(.data、rtmp)的区分在fifo里进行；播放的启动(createFifo、createFifo2)在fifo里识别
	 * 播放器的状态(画面出来、卡、播)需要客户端告诉给fifo
	 * */
	public static native void setPlayerVout();
	public static native void setPlayerCard();
	public static native void setPlayerPlay();
	
	/**
	 * 修改于20150422；用于向内核传递播放器读取的数据量
	 * */
	public static native void updateDataState(long playerReadBytes);
	
	private static String updaterJarName = "updater.jar";
	private static String updaterJarUrl = "http://mobile.kukuplay.com/core/android/zy_update/updater_jar.php";
	private static String className = "com.fifo.updater.Updater";
	private static String methodName = "start";
	private static String method2Name = "getInstance";
	private static String TAG = "FifoController";
	
	public static FifoController mInstance = null;
    public String nativeDir;
    public String deviceImei;
    public String apkVersion;
    
    public static int UPDATE_JAR_OK = 0x01;
    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
        }
    };
    

	public static FifoController getInstance(){
		if(mInstance == null){
			mInstance = new FifoController();
		}
		return mInstance;
	}

	public static boolean isWifiState(){
		return BasicToolUtil.isWifiState(GlobalConfig.instance().getApplicationContext());
	}
}
