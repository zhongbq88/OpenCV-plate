package com.zbq.opencv;

import android.graphics.Bitmap;

public class ECCV{

    static {
        System.loadLibrary("ec-cv-lib");
    }

    public static native void init();

    public static native void release();

    public static native int imgPlate(String filePath,String outPath,int count);

    public static native String bitwiseNot(Bitmap bitmap,String outPath);

    public static native double matches(Bitmap bitmap1,Bitmap bitmap2);

}