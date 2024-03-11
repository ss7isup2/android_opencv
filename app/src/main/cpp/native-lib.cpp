#include <jni.h>
#include <opencv2/opencv.hpp>

#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"

#include "LoadYolov8.h"

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
Java_com_aos_opencv_ImageActivity_ConvertRGBtoGray(JNIEnv *env, jobject instance,
                                                                    jlong inputMat,
                                                                    jlong outputMat) {


    // 입력 RGBA 이미지를 GRAY 이미지로 변환

    Mat &inputImage = *(Mat *) inputMat;
    Mat &outputImage = *(Mat *) outputMat;

    cvtColor(inputImage, outputImage, COLOR_RGBA2GRAY);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_ImageActivity_detectEdgeJNI
(JNIEnv *env, jobject instance, jlong inputImage, jlong outputImage, jint th1, jint th2) {

    // TODO
    Mat &inputMat = *(Mat *) inputImage;
    Mat &outputMat = *(Mat *) outputImage;

    cvtColor(inputMat, outputMat, COLOR_RGB2GRAY);
    Canny(outputMat, outputMat, th1, th2);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_ImageActivity_(JNIEnv *env, jobject instance,
                                  jlong inputImage, jlong outputImage,
                                  jint th1, jint th2) {

    // TODO
    Mat &inputMat = *(Mat *) inputImage;
    Mat &outputMat = *(Mat *) outputImage;

    cvtColor(inputMat, outputMat, COLOR_RGB2GRAY);
    Canny(outputMat, outputMat, th1, th2);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_detectEdgeJNI(JNIEnv *env, jobject thiz, jlong inputImage,
                                                 jlong outputImage, jint th1, jint th2) {
    // TODO: implement detectEdgeJNI()

    Mat &inputMat = *(Mat *) inputImage;
    Mat &outputMat = *(Mat *) outputImage;

    cvtColor(inputMat, outputMat, COLOR_RGB2GRAY);
    Canny(outputMat, outputMat, th1, th2);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_flipJNI(JNIEnv *env, jobject thiz, jlong inputImage, jlong outputImage, jint flipCode) {
    // TODO: implement detectEdgeJNI()

    Mat &inputMat = *(Mat *) inputImage;
    Mat &outputMat = *(Mat *) outputImage;

    flip(inputMat, outputMat, flipCode);
}

const char *FILE_NAME = "yolov8n-seg.onnx";
const char *LABEL_NAME = "yolov8n.txt";

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_LoadModel(JNIEnv *env, jobject instance, jobject assetManager) {

    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    AAsset *asset = AAssetManager_open(mgr, FILE_NAME, AASSET_MODE_UNKNOWN);

    const void *buff = AAsset_getBuffer(asset);
    off_t length = AAsset_getLength(asset);


    LoadYolov8::net = cv::dnn::readNetFromONNX((char *)buff, length);

    AAsset_close(asset);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_LoadLabel(JNIEnv *env, jobject instance, jobject assetManager) {

    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    AAsset *asset = AAssetManager_open(mgr, LABEL_NAME, AASSET_MODE_UNKNOWN);

//    const void *buff = AAsset_getBuffer(asset);
    off_t fileSize = AAsset_getLength(asset);

    std::string line;

    LoadYolov8::labels.clear();

    std::string assetText(fileSize, 0x00);
    AAsset_read(asset, (void*)assetText.data(), fileSize);

    std::istringstream ss(assetText);

    while (getline(ss, line, '\n')){
        if (line.compare("\0\n") == 0) continue;
        LoadYolov8::labels.push_back(line);
    }

    AAsset_close(asset);
}
