package com.example.spaceshipgame;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.widget.Toast;


public class MainActivity extends Activity {

	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;
	
	
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
	
		ActivityManager activityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
		
		final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
		
		if(supportsEs2)
		{
			glSurfaceView = new GLSurfaceView(this);
			
			if(isProbablyEmulator())
			{
				glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
			}
			
			glSurfaceView.setEGLContextClientVersion(2);
			glSurfaceView.setRenderer(new RendererWrapper());
			rendererSet = true;
			setContentView(glSurfaceView);
		}
		else
		{
			Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
		}
	}
	
	public void onPause()
	{
		super.onPause();
		if(rendererSet)
			glSurfaceView.onPause();
	}
	
	public void onResume()
	{
		super.onPause();
		if(rendererSet)
			glSurfaceView.onResume();
	}
	
	private boolean isProbablyEmulator() {
	    return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
	            && (Build.FINGERPRINT.startsWith("generic")
	                    || Build.FINGERPRINT.startsWith("unknown")
	                    || Build.MODEL.contains("google_sdk")
	                    || Build.MODEL.contains("Emulator")
	                    || Build.MODEL.contains("Android SDK built for x86"));
	}
}