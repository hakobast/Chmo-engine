package com.example.spaceshipgame;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;

public class MainActivity extends Activity
{	
	private ChmoEngineBridge bridge;
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
	
		bridge = new ChmoEngineBridge(this);
	}
	
	public void onPause()
	{
		super.onPause();
		bridge.pause();
	}

	public void onResume()
	{
		super.onResume();
		bridge.resume();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		return bridge.OnTouchEvent(event);
	}
}