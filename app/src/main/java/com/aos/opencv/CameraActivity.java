package com.aos.opencv;

import static android.Manifest.permission.CAMERA;


import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Camera;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

import com.aos.opencv.databinding.ActivityCameraBinding;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.core.Mat;
import org.opencv.dnn.Net;
import org.opencv.imgproc.Imgproc;

import java.util.List;

public class CameraActivity extends Activity implements CameraBridgeViewBase.CvCameraViewListener2 {
    ActivityCameraBinding binding;
    private static final String TAG = CameraActivity.class.getName();
    private static final int CAMERA_PERMISSION_REQUEST_CODE = 200;

    private CameraBridgeViewBase mOpenCvCameraView;


    public native void LoadModel(AssetManager assetManager);
    public native void LoadLabel(AssetManager assetManager);


    @Override
    protected void onStart() {
        super.onStart();
        boolean havePermission = true;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(CAMERA) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{CAMERA}, CAMERA_PERMISSION_REQUEST_CODE);
                havePermission = false;
            }
        }
        if (havePermission) {
            mOpenCvCameraView.setCameraPermissionGranted();
        }
    }

    @Override
    @TargetApi(Build.VERSION_CODES.M)
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (requestCode == CAMERA_PERMISSION_REQUEST_CODE && grantResults.length > 0
                && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            mOpenCvCameraView.setCameraPermissionGranted();
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    @SuppressLint("MissingInflatedId")
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);

        System.loadLibrary("opencv_java4");
        System.loadLibrary("native-lib");


//        setContentView(R.layout.activity_camera);
        binding = ActivityCameraBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());



        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.cameraView);
        mOpenCvCameraView.setCvCameraViewListener(this);

//        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCameraIndex(CameraBridgeViewBase.CAMERA_ID_BACK);


//        Canvas canvas = getHolder().lockCanvas();
//// Rotate canvas to 90 degrees
//        canvas.rotate(90f, canvas.getWidth()/2, canvas.getHeight()/2);
//
//        // Resize
//        Bitmap bitmap = Bitmap.createScaledBitmap(mCacheBitmap, canvas.getHeight(), canvas.getWidth(), true);
//// Use bitmap instead of mCacheBitmap
//        canvas.drawBitmap(bitmap, new Rect(0,0,bitmap.getWidth(), bitmap.getHeight()), new Rect(
//                (int)((canvas.getWidth() - mScale*bitmap.getWidth()) / 2),
//                (int)((canvas.getHeight() - mScale*bitmap.getHeight()) / 2),
//                (int)((canvas.getWidth() - mScale*bitmap.getWidth()) / 2 + mScale*bitmap.getWidth()),
//                (int）((canvas.getHeight() - mScale*bitmap.getHeight()) / 2 + mScale*bitmap.getHeight()
//        )), null);
//
//// Unlock canvas
//        getHolder().unlockCanvasAndPost(canvas);

        AssetManager assetManager = this.getAssets();
        LoadModel(assetManager);
        LoadLabel(assetManager);

        net = Load.Companion.loadModel(getAssets(), getFilesDir().toString());
        labels = Load.Companion.loadLabel(getAssets());



        binding.btnChangeCamera.setOnClickListener(v -> {

//            mOpenCvCameraView.get
//            int activeCamera = CameraBridgeViewBase.CAMERA_ID_BACK;
//
//            mOpenCvCameraView.setCameraIndex(activeCamera);
            swapCamera();

            if (mCameraId == 0) { // back
                binding.btnChangeCamera.setText("Back");
            } else { // front
                binding.btnChangeCamera.setText("Front");
            }
        });

    }

    int mCameraId = 0;
    private void swapCamera() {
        mCameraId = mCameraId^1; //bitwise not operation to flip 1 to 0 and vice versa
        mOpenCvCameraView.disableView();
        mOpenCvCameraView.setCameraIndex(mCameraId);
        mOpenCvCameraView.enableView();
    }

    @Override
    public void onResume() {
        super.onResume();
        mOpenCvCameraView.enableView();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {

    }

    public void onCameraViewStopped() { }

    private Net net;
    private String[] labels;

    public native void detectEdgeJNI(long inputImage, long outputImage, int th1, int th2);
    public native void DrawSeg(long inputImage, long outputImage, Result[] resultArray, String[] stringArray);
    public native void Detect(long inputImage);
    public native void flipJNI(long inputImage, long outputImage, int flipCode);

    Mat outMat = null;

    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {

//        Mat rgba = inputFrame.rgba();
//
//        Mat edge = getEdgeImage(inputFrame, 50, 150);
//

//
//        return edge;

//        return inputFrame.rgba();

        if (inputFrame == null) return null;

        Mat frameMat = inputFrame.rgba();



//        // java로 처리
//        {
//            List<Result> results = Inference.Companion.detect(frameMat, net, labels);
//            Imgproc.cvtColor(frameMat, frameMat, Imgproc.COLOR_RGBA2RGB);
//
//            outMat = Draw.Companion.drawSeg(frameMat, results, labels);
//        }



        // jni로 처리
        {
            Detect(frameMat.getNativeObjAddr());
//            Imgproc.cvtColor(frameMat, frameMat, Imgproc.COLOR_RGBA2RGB);

            if (outMat == null) {
                outMat = new Mat();
            }

//        int arrListSize = results.size();
//        Result results1[] = results.toArray(new Result[arrListSize]);

            DrawSeg(frameMat.getNativeObjAddr(), outMat.getNativeObjAddr(), null, labels);

            frameMat.release();
        }


        // back camera 인 경우는 화면을 180도 뒤집는다.
        Mat flip = new Mat();
        if (mCameraId == 1) {   // front camera
            flipJNI(outMat.getNativeObjAddr(), flip.getNativeObjAddr(), 1);

            return flip;
        }

        return outMat;

    }

    Mat getEdgeImage(CameraBridgeViewBase.CvCameraViewFrame inputFrame, int th1, int th2) {
        Mat rgba = inputFrame.rgba();

        Mat edge = new Mat();

        detectEdgeJNI(rgba.getNativeObjAddr(), edge.getNativeObjAddr(), th1, th2);

        return edge;
    }
}