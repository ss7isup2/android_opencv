#include <jni.h>
#include <opencv2/opencv.hpp>


//#include <string>

//extern "C" JNIEXPORT jstring JNICALL
//Java_learn_kotlin_com_androidopencv_MainActivity_stringFromJNI(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}

using namespace cv;

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_ConvertRGBtoGray(JNIEnv *env, jobject instance,
        jlong inputMat,
jlong outputMat) {


// 입력 RGBA 이미지를 GRAY 이미지로 변환

Mat &inputImage = *(Mat *) inputMat;
Mat &outputImage = *(Mat *) outputMat;

cvtColor(inputImage, outputImage, COLOR_RGBA2GRAY);

}