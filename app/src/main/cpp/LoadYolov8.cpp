#include <jni.h>
#include <opencv2/opencv.hpp>
#include "LoadYolov8.h"

using namespace cv;

cv::dnn::Net LoadYolov8::net;
std::vector<std::string> LoadYolov8::labels;

