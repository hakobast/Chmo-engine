package com.example.spaceshipgame;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.os.Build;
import android.view.MotionEvent;
import android.widget.Toast;

public class ChmoEngineBridge implements Renderer{
	
	private Activity activity_;
	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;
	public ChmoEngineBridge(Activity activity)
	{
		activity_ = activity;
		ActivityManager activityManager = (ActivityManager)activity_.getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
		
		final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
		
		if(supportsEs2)
		{
			GameLibJNIWrapper.init_asset_manager(activity_.getAssets());
			glSurfaceView = new GLSurfaceView(activity_);
			
			if(isProbablyEmulator())
			{
				glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
			}
			
			glSurfaceView.setEGLContextClientVersion(2);
			glSurfaceView.setRenderer(this);
			activity_.setContentView(glSurfaceView);
			rendererSet = true;
		}
		else
		{
			Toast.makeText(activity, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
		}
	}
	
	public boolean OnTouchEvent(MotionEvent event)
	{
		if(rendererSet)
		{
			//TODO implement touches
		}
		return true;
	}
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		GameLibJNIWrapper.on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		GameLibJNIWrapper.on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		GameLibJNIWrapper.on_draw_frame();
	}
	
	public void pause()
	{
		if(rendererSet)
		{
			glSurfaceView.queueEvent(new Runnable() {
				@Override
				public void run() {
					GameLibJNIWrapper.on_pause();
				}
			});				
			glSurfaceView.onPause();
		}
		
		//TEMP
		activity_.finish();
	}
	
	public void resume()
	{
		if(rendererSet)
		{
			glSurfaceView.onResume();
			glSurfaceView.queueEvent(new Runnable() {
				@Override
				public void run() {
					GameLibJNIWrapper.on_resume();
				}
			});		
		}
	}
	
	public void destroy()
	{
		/*if(rendererSet)
		{
			glSurfaceView.queueEvent(new Runnable() {
				@Override
				public void run() {
					GameLibJNIWrapper.on_destroy();
				}
			});
		}*/
	}
	
	private boolean isProbablyEmulator() {
	    return Build.VERSION.SDK_INT >= 15 // ice_scream_sandwich_mr1
	            && (Build.FINGERPRINT.startsWith("generic")
	                    || Build.FINGERPRINT.startsWith("unknown")
	                    || Build.MODEL.contains("google_sdk")
	                    || Build.MODEL.contains("Emulator")
	                    || Build.MODEL.contains("Android SDK built for x86"));
	}
}
