/* Copyright (c) 2011-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

package com.arm.malideveloper.openglessdk.antialias;
 
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

import com.arm.malideveloper.openglessdk.*;

class AntiAliasView extends MaliSamplesView
{
    public AntiAliasView(Context context) 
    { 
        super(context);
    }
	
    @Override protected void setRendererCallback()
    {
        setRenderer(new Renderer());
    }
    
    @Override protected void destroyContextCallback()
    {
    	AntiAlias.uninit();
    }

    protected class Renderer implements GLSurfaceView.Renderer 
    {
        public void onDrawFrame(GL10 gl) 
        {
        	AntiAlias.step();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) 
        {
        	AntiAlias.init(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) 
        {
        }
    }
};

public class AntiAlias extends MaliSamplesActivity 
{
	AntiAliasView mView;
    
    public static native void init(int width, int height);
    public static native void step();
    public static native void uninit();
    
    @Override protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
           WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        mView = new AntiAliasView(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() 
    {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() 
    {
        super.onResume();
        mView.onResume();
    }

    @Override protected void onDestroy()
    {
    	super.onDestroy();
    }

    static 
    {
        // Load the NDK library for this example, built with ndk-build
        System.loadLibrary("Native");
    }
}


