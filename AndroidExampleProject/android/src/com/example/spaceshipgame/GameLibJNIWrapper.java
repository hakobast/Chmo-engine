package com.example.spaceshipgame;

import android.content.res.AssetManager;
import android.view.MotionEvent;

public class GameLibJNIWrapper {

	static {
		System.loadLibrary("game");
	}
	public static native void init_asset_manager(AssetManager manager);
	
	public static native void on_surface_created();
	
	public static native void on_surface_changed(int width, int height);
	
	public static native void on_draw_frame();
	
	public static native void on_touch_event(MotionEvent event);
	
	public static native void on_resume();
	
	public static native void on_pause();
	
	public static native void on_destroy();
	
}
