#include <jni.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>

#include "Result.h"
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
using namespace cv::dnn;



const float ALPHA = 0.5;

extern "C"
JNIEXPORT cv::Scalar JNICALL
getColor(int index) {

    switch (index) {
        case 45:
        case 18:
        case 19:
        case 22:
        case 30:
        case 42:
        case 43:
        case 44:
        case 61:
        case 71:
        case 72:
            return cv::Scalar(255.0, 255.0, 255.0); // WHITE
        case 1:
        case 3:
        case 14:
        case 25:
        case 37:
        case 38:
        case 79:
            return cv::Scalar(0.0, 0.0, 255.0); // BLUE
        case 2:
        case 9:
        case 10:
        case 11:
        case 32:
        case 47:
        case 49:
        case 51:
        case 52:
            return cv::Scalar(255.0, 0.0, 0.0); // RED
        case 5:
        case 23:
        case 46:
        case 48:
            return cv::Scalar(0.0, 255.0, 255.0); // YELLOW
        case 6:
        case 13:
        case 34:
        case 35:
        case 36:
        case 54:
        case 59:
        case 60:
        case 73:
        case 77:
        case 78:
            return cv::Scalar(128.0, 128.0, 128.0); // GRAY
        case 7:
        case 24:
        case 26:
        case 27:
        case 28:
        case 62:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 74:
        case 75:
            return cv::Scalar(0.0, 0.0, 0.0); // BLACK
        case 12:
        case 29:
        case 33:
        case 39:
        case 41:
        case 58:
        case 50:
            return cv::Scalar(0.0, 255.0, 0.0); // GREEN
        case 15:
        case 16:
        case 17:
        case 20:
        case 21:
        case 31:
        case 40:
        case 55:
        case 57:
        case 63:
            return cv::Scalar(64.0, 64.0, 64.0); // DARK GRAY
        case 70:
        case 76:
            return cv::Scalar(192.0, 192.0, 192.0); // LIGHT GRAY
        default:
            return cv::Scalar(128.0, 0.0, 128.0); // PURPLE
    }
};

extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_ConvertRGBtoGray(JNIEnv *env, jobject instance,
        jlong inputMat, jlong outputMat) {


// 입력 RGBA 이미지를 GRAY 이미지로 변환

Mat &inputImage = *(Mat *) inputMat;
Mat &outputImage = *(Mat *) outputMat;

cvtColor(inputImage, outputImage, COLOR_RGBA2GRAY);

}

extern "C"
JNIEXPORT std::vector<std::string> JNICALL
getLabels(JNIEnv *env, jobject instance, jobjectArray stringArray) {
    std::vector<std::string> labels;
    int stringCount = env->GetArrayLength(stringArray);
    for (int i = 0; i < stringCount; i++) {
        jstring string = (jstring) (env->GetObjectArrayElement(stringArray, i));
        const char *rawString = env->GetStringUTFChars(string, 0);
        labels.push_back(rawString);
        env->ReleaseStringUTFChars(string, rawString);
        // Don't forget to call `ReleaseStringUTFChars` when you're done.
    }

    return labels;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_aos_opencv_CameraActivity_DrawSeg(JNIEnv *env, jobject instance,
//                                        cv::Mat mat, std::vector<Result> lists, std::vector<std::string> labels) {
                                           jlong inputImage, jlong outputImage, jobjectArray resultArray, jobjectArray stringArray) {

    cv::Mat &inputMat = *(Mat *) inputImage;
    cv::Mat &outputMat = *(Mat *) outputImage;

//    std::vector<std::string> labels = getLabels(env, instance, stringArray);

    std::vector<std::string> labels = LoadYolov8::labels;

//    int stringCount = env->GetArrayLength(stringArray);
//    for (int i = 0; i < stringCount; i++) {
//        jstring string = (jstring) (env->GetObjectArrayElement(stringArray, i));
//        const char *rawString = env->GetStringUTFChars(string, 0);
//        labels.push_back(rawString);
//        env->ReleaseStringUTFChars(string, rawString);
//        // Don't forget to call `ReleaseStringUTFChars` when you're done.
//    }

    std::vector<Result> lists = LoadYolov8::lists;

//    int resultCount = env->GetArrayLength(resultArray);
//
////    for (int i=0; i<resultCount; i++) {
////        jobject resultObject = (jobject) (env->GetObjectArrayElement(resultArray, i));
////        const Result *rawResult = reinterpret_cast<const Result *>(env->GetObjectClass(resultObject));
////        lists.push_back(*rawResult);
////        // Don't forget to call `ReleaseStringUTFChars` when you're done.
////    }
//
//    for (int i = 0; i < resultCount; i++) {
//        jobject objectResult = (jobject) env->GetObjectArrayElement(resultArray, i);
//
//        jclass clazzResult = env->GetObjectClass(objectResult);
//
////        struct Result {
////            cv::Rect box;
////            float confidence;
////            int index;
////            cv::Mat maskMat;
////        };
//
//        jfieldID fid;
//        jstring jstr;
//
//        Result result;
//        fid = env->GetFieldID(clazzResult, "box", "Lorg/opencv/core/Rect;");
//        jobject objectBox = (jobject) env->GetObjectField(objectResult, fid);
//
//        jclass clazzBox = env->GetObjectClass(objectBox);
//
//        cv::Rect box;
//        fid = env->GetFieldID(clazzBox, "x", "I");
//        box.x = env->GetIntField(objectBox, fid);
//
//        fid = env->GetFieldID(clazzBox, "y", "I");
//        box.y = env->GetIntField(objectBox, fid);
//
//        fid = env->GetFieldID(clazzBox, "width", "I");
//        box.width = env->GetIntField(objectBox, fid);
//
//        fid = env->GetFieldID(clazzBox, "height", "I");
//        box.height = env->GetIntField(objectBox, fid);
//
//
//        fid = env->GetFieldID(clazzResult, "confidence", "F");
//        result.confidence = (jfloat) env->GetFloatField(objectResult, fid);
//
//        fid = env->GetFieldID(clazzResult, "index", "I");
//        result.index = (jfloat) env->GetIntField(objectResult, fid);
//
//        result.box = box;
//
//        cv::Mat objectMat;
//
//        fid = env->GetFieldID(clazzResult, "maskMatAddr", "J");
//        jlong maskMatAddr = (jlong) env->GetLongField(objectResult, fid);
//
//        cv::Mat& maskMat = *(cv::Mat*)maskMatAddr;
//
//        result.maskMat = maskMat;
//
//        lists.push_back(result);
//    }



    cv::Mat maskImg = inputMat.clone();

    if (lists.size() == 0) {
        outputMat = inputMat;
//        return maskImg;
        return;
    }

    for (auto& it : lists) {
        cv::Rect box = it.box;
        cv::Scalar color = getColor(it.index);
        cv::Point textPoint(box.x, box.y - 5);
        std::string text = labels[it.index] + " " + std::to_string(static_cast<int>(std::round(it.confidence * 100))) + "%";

        cv::rectangle(inputMat, box, color, 2);
        cv::putText(inputMat, text, textPoint, cv::FONT_HERSHEY_SIMPLEX, 1.0, color, 2);

        cv::Mat cropMask = it.maskMat;

        cv::Mat cropMaskImg(maskImg, box);
        cv::Mat cropMaskRGB = cv::Mat(cropMask.size(), CV_8UC3);
        std::vector<cv::Mat> list(3, cropMask.clone());
        cv::merge(list, cropMaskRGB);

        cv::Mat temp1 = cv::Mat::zeros(cropMaskRGB.size(), cropMaskRGB.type());
        cv::add(temp1, cv::Scalar(1.0, 1.0, 1.0), temp1);
        cv::subtract(temp1, cropMaskRGB, temp1);
        cv::multiply(cropMaskImg, temp1, cropMaskImg);

        cv::Mat temp2;
        cv::multiply(cropMaskRGB, color, temp2);
        cv::add(cropMaskImg, temp2, cropMaskImg);

        cropMask.release();
        cropMaskImg.release();
        temp1.release();
        temp2.release();
        cropMaskRGB.release();
        it.maskMat.release();
        for (auto& mat : list) mat.release();
    }

    cv::Mat resultMat(inputMat.size(), inputMat.type());
//    cv::addWeighted(maskImg, ALPHA, inputMat, 1 - ALPHA, 0.0, resultMat, CV_8UC3);
    cv::addWeighted(maskImg, ALPHA, inputMat, 1 - ALPHA, 0.0, outputMat, CV_8UC3);

    maskImg.release();

}




const std::string OUTPUT_NAME_0 = "output0";
const std::string OUTPUT_NAME_1 = "output1";
const int INPUT_SIZE = 640;
const double SCALE_FACTOR = 1 / 255.0;
const int OUTPUT_SIZE = 8400;
const int OUTPUT_MASK_SIZE = 160;
const float CONFIDENCE_THRESHOLD = 0.3f;
const float NMS_THRESHOLD = 0.5f;




extern "C"
JNIEXPORT cv::Mat JNICALL
sigmoid(JNIEnv *env, jobject instance, const cv::Mat& mat) {
    cv::Mat oneMat = cv::Mat::ones(mat.size(), mat.type());
    cv::Mat mulMat;
    cv::Mat expMat;
    cv::Mat outMat;

    cv::multiply(mat, cv::Scalar(-1.0), mulMat);
    cv::exp(mulMat, expMat);
    cv::add(oneMat, expMat, outMat);
    cv::divide(oneMat, outMat, outMat);

    oneMat.release();
    mulMat.release();
    expMat.release();

    return outMat;
}


extern "C"
JNIEXPORT std::vector<cv::Rect> JNICALL
resizeBoxes(JNIEnv *env, jobject instance, const std::vector<Result>& boxOutputs, int width, int height) {
    std::vector<cv::Rect> resizedBoxes;
    for (const Result& result : boxOutputs) {
        cv::Rect rect = result.box;
        int x = rect.x * OUTPUT_MASK_SIZE / width;
        int w = rect.width * OUTPUT_MASK_SIZE / width;
        int y = rect.y * OUTPUT_MASK_SIZE / height;
        int h = rect.height * OUTPUT_MASK_SIZE / height;

        resizedBoxes.push_back(cv::Rect(x, y, w, h));
    }
    return resizedBoxes;
}

extern "C"
JNIEXPORT void JNICALL
maskOutput(JNIEnv *env, jobject instance, std::vector<Result>& boxOutputs,
        cv::Mat& output1,
        int matWidth,
        int matHeight
) {
    if (boxOutputs.size() == 0) return;

    std::vector<cv::Mat> maskPredictionList;
    for (const Result& result : boxOutputs) {
        maskPredictionList.push_back(result.maskMat);
    }
    cv::Mat maskPredictionMat;
    cv::vconcat(maskPredictionList, maskPredictionMat);
    int reshapeSize = OUTPUT_MASK_SIZE * OUTPUT_MASK_SIZE;
    cv::Mat outputMat = output1.reshape(1, output1.total() / reshapeSize);
    cv::Mat matMul;

    cv::gemm(maskPredictionMat, outputMat, 1.0, cv::Mat(), 0.0, matMul);
    cv::Mat masks = sigmoid(env, instance,matMul);
    std::vector<cv::Rect> resizedBoxes = resizeBoxes(env, instance,boxOutputs, matWidth, matHeight);
    cv::Size blurSize((matWidth / OUTPUT_MASK_SIZE), (matHeight / OUTPUT_MASK_SIZE));

    for (size_t i = 0; i < resizedBoxes.size(); ++i) {
        cv::Rect resizeBox = resizedBoxes[i];
        int scaleX = resizeBox.x;
        int scaleY = resizeBox.y;
        int scaleW = resizeBox.width;
        int scaleH = resizeBox.height;

        int w = boxOutputs[i].box.width;
        int h = boxOutputs[i].box.height;

        cv::Mat mask = masks.row(i).reshape(1, OUTPUT_MASK_SIZE);
        cv::Mat resizedCropMask(mask, cv::Rect(scaleX, scaleY, scaleW, scaleH));
        cv::Mat cropMask;
        cv::Mat blurMask;
        cv::Mat thresholdMask;
        cv::Size resizeSize(w, h);

        cv::resize(resizedCropMask, cropMask, resizeSize, 0.0, 0.0, cv::INTER_LINEAR);
        cv::blur(cropMask, blurMask, blurSize);
        cv::threshold(blurMask, thresholdMask, 0.5, 1.0, cv::THRESH_BINARY);

        thresholdMask.convertTo(thresholdMask, CV_8UC1);
        boxOutputs[i].maskMat.release();
        boxOutputs[i].maskMat = thresholdMask;

        mask.release();
        resizedCropMask.release();
        cropMask.release();
        blurMask.release();
    }

    maskPredictionMat.release();
    output1.release();
    outputMat.release();
    matMul.release();
    masks.release();
    for (cv::Mat& mask : maskPredictionList) {
        mask.release();
    }
}


extern "C"
JNIEXPORT void JNICALL
resizeBox(JNIEnv *env, jobject instance, std::vector<Result>& list, int width, int height) {
    for (Result& it : list) {
        cv::Rect box = it.box;
        int x = (box.x * width / INPUT_SIZE);
        int y = (box.y * height / INPUT_SIZE);
        int w = (box.width * width / INPUT_SIZE);
        int h = (box.height * height / INPUT_SIZE);

        if (w > width) w = width;
        if (h > height) h = height;

        if (x + w > width) w = width - x;
        if (y + h > height) h = height - y;

        cv::Rect rect(x, y, w, h);
        it.box = rect;
    }
}

extern "C"
JNIEXPORT std::vector<Result> JNICALL
boxOutput(JNIEnv *env, jobject instance, cv::Mat output, int labelSize) {
    cv::Mat detections = output.reshape(1, output.total() / OUTPUT_SIZE).t();

    std::vector<cv::Rect2d> boxes(detections.rows);
    std::vector<float> maxScores(detections.rows);
    std::vector<int> indexes(detections.rows);

    for (int i = 0; i < detections.rows; ++i) {
        cv::Mat scores = detections.row(i).colRange(4, 4 + labelSize);
        cv::Point maxLoc;
        cv::minMaxLoc(scores, nullptr, nullptr, nullptr, &maxLoc);
        float maxVal = scores.at<float>(maxLoc);
        float xPos = detections.at<float>(i, 0);
        float yPos = detections.at<float>(i, 1);
        float width = detections.at<float>(i, 2);
        float height = detections.at<float>(i, 3);
        float left = std::max(0.0f, xPos - width / 2.0f);
        float top = std::max(0.0f, yPos - height / 2.0f);

        boxes[i] = cv::Rect2d(left, top, width, height);
        maxScores[i] = maxVal;
        indexes[i] = maxLoc.x;

        scores.release();
    }
//
//    cv::MatOfRect2d rects(boxes.data());
//    cv::MatOfFloat floats(maxScores.data());
//    cv::MatOfInt ints(indexes.data());
//    cv::MatOfInt indices;


    std::vector<cv::Rect2d> rects(boxes);
    std::vector<float> floats(maxScores);
    std::vector<int> ints(indexes);
    std::vector<int> indices;


//    cv::dnn::NMSBoxesBatched(rects, floats, ints, CONFIDENCE_THRESHOLD, NMS_THRESHOLD, indices);
    cv::dnn::NMSBoxesBatched(rects, floats, ints, CONFIDENCE_THRESHOLD, NMS_THRESHOLD, indices);
//    cv::dnn::NMSBoxes(boxes, maxScores, CONFIDENCE_THRESHOLD, NMS_THRESHOLD, indices);

//    std::vector<int> indices,

    std::vector<Result> list;
//    if (indices.total() == 0) return list;
    if (indices.size() == 0) return list;

//    std::vector<int> idx(indices.rows());
//    indices.copyTo(idx);
//    std::vector<int> idx(indices.size());
//    std::copy(indices.begin(), indices.end(), idx);


    for (int it : indices) {
        cv::Mat scores = detections.row(it).colRange(4, 4 + labelSize);
        cv::Point maxLoc;
        cv::minMaxLoc(scores, nullptr, nullptr, nullptr, &maxLoc);
        float maxVal = scores.at<float>(maxLoc);
        float xPos = detections.at<float>(it, 0);
        float yPos = detections.at<float>(it, 1);
        float width = detections.at<float>(it, 2);
        float height = detections.at<float>(it, 3);

        int x = std::max(0.0f, xPos - width / 2.0f);
        int y = std::max(0.0f, yPos - height / 2.0f);
        int w = std::min(INPUT_SIZE, static_cast<int>(width));
        int h = std::min(INPUT_SIZE, static_cast<int>(height));
        cv::Rect rect(x, y, w, h);

        Result result;
        result.box = rect;
        result.confidence = maxVal;
        result.index = maxLoc.x;
        result.maskMat = detections.row(it).colRange(4 + labelSize, detections.cols);
        list.push_back(result);

        scores.release();
    }
    detections.release();
    return list;
}


extern "C"
JNIEXPORT std::vector<Result> JNICALL
postProcess(JNIEnv *env, jobject instance, cv::Mat output0, cv::Mat output1, int labelSize, int width, int height) {

    std::vector<Result> lists = boxOutput(env, instance,output0, labelSize);

    resizeBox(env, instance,lists, width, height);

    maskOutput(env, instance, lists, output1, width, height);

    output0.release();
    output1.release();

    return lists;
}

extern "C"
JNIEXPORT void JNICALL
//Java_com_aos_opencv_CameraActivity_Detect(JNIEnv *env, jobject instance, cv::Mat mat, cv::dnn::Net net, std::vector<std::string> labels) {
//Java_com_aos_opencv_CameraActivity_Detect(JNIEnv *env, jobject instance, jlong matAddr, jlong netAddr, jobjectArray stringArray) {
Java_com_aos_opencv_CameraActivity_Detect(JNIEnv *env, jobject instance, jlong matAddr) {

    cv::Mat& mat = *(cv::Mat*)matAddr;
//    cv::dnn::Net net = *(cv::dnn::Net*)netAddr;
//    std::vector<std::string> labels = getLabels(env, instance, stringArray);

    cv::dnn::Net net = LoadYolov8::net;
    std::vector<std::string> labels = LoadYolov8::labels;


    cv::Mat inputMat;
    cv::resize(mat, inputMat, cv::Size(INPUT_SIZE, INPUT_SIZE));
    cv::cvtColor(inputMat, inputMat, cv::COLOR_RGBA2RGB);
    inputMat.convertTo(inputMat, CV_32FC3);
    cv::Mat blob = cv::dnn::blobFromImage(inputMat, SCALE_FACTOR);
    net.setInput(blob);

    cv::Mat output0, output1;
    std::vector<cv::Mat> outputList = {output0, output1};
    std::vector<std::string> outputNameList = {OUTPUT_NAME_0, OUTPUT_NAME_1};

    net.forward(outputList, outputNameList);


    std::vector<Result> lists = postProcess(env, instance,outputList[0], outputList[1], labels.size(), mat.cols, mat.rows);

    blob.release();
    inputMat.release();
    output0.release();
    output1.release();

    cv::cvtColor(mat, mat, cv::COLOR_RGBA2RGB);

    LoadYolov8::lists = lists;
//    return lists;


//    jclass resultClass = env->FindClass("com/aos/opencv/Result");
//    jmethodID constructor = env->GetMethodID(resultClass, "<init>", "()V");
//
//    // Create an array of custom objects
//    jobjectArray resultArray = env->NewObjectArray(3, resultClass, NULL);
//    for (int i = 0; i < lists.size(); ++i) {
//        jobject obj = env->NewObject(resultClass, constructor);
//
//        obj = (jobject)&lists[i];
//
//        env->SetObjectArrayElement(resultArray, i, obj);
//        env->DeleteLocalRef(obj); // Release local reference
//    }
//
//    return resultArray;



//    Result * result = new Result();
//    jclass cls = env->FindClass("com/aos/opencv/Result");
//    jmethodID constructorID = env->GetMethodID(cls, "<init>", "()V");
//    jobjectArray resultArray = env->NewObjectArray(lists.size(), cls, NULL);
//
//    for (int i=0; i<lists.size(); i++) {
//        jobject object = env->NewObject(cls, constructorID);
//
//
//
//
//        env->SetObjectArrayElement(resultArray, i, object);
//    }
//


}