package com.libfifo;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class FifoEventHandler {
	
	public static final int fifo_ChannelPropertySuccess	= 0x00;
	public static final int fifo_FlvHeaderSuccess		= 0x01;
	public static final int fifo_FirstDataSuccess		= 0x02;
	public static final int fifo_SecondDataSuccess		= 0x03;
	
	public static final int fifo_ChannelPropertyFail	= 0x100;
	public static final int fifo_FlvHeaderFail			= 0x101;
	public static final int fifo_PlayerBlock			= 0x102;
	
	public Handler fifoHandler;
	private static FifoEventHandler mInstance;
	
	public static FifoEventHandler getInstance(){
		if(mInstance == null){
			mInstance = new FifoEventHandler();
		}
		return mInstance;
	}
	
	public void callback(int event){
		Message msg = new Message();
		msg.what = event;
		fifoHandler.sendMessage(msg);
	}
	
	public void callback(int event, Bundle b){
		Message msg = new Message();
		msg.what = event;
		msg.setData(b);
		fifoHandler.sendMessage(msg);
	}
}
