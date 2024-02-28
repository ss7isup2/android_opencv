package com.aos.opencv;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import com.aos.opencv.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'opencv' library on application startup.
//    static {
////        System.loadLibrary("opencv");
//        System.loadLibrary("native-lib");
//    }

    private ActivityMainBinding binding;

    Context context;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        context = this;

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
//        tv.setText(stringFromJNI());

        binding.btnOpencv.setOnClickListener(v -> {
            Intent intent = new Intent(context, ImageActivity.class);
            ((Activity)context).startActivityForResult(intent, 100);

        });

        binding.btnCamera.setOnClickListener(v -> {
            Intent intent = new Intent(context, CameraActivity.class);
            ((Activity)context).startActivityForResult(intent, 100);

        });

    }

    /**
     * A native method that is implemented by the 'opencv' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}