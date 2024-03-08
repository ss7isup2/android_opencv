//
// Created by khc on 2024/03/08.
//

#ifndef OPENCV_LOADYOLOV8_H
#define OPENCV_LOADYOLOV8_H

#include "../../../../sdk/native/jni/include/opencv2/dnn/dnn.hpp"

class LoadYolov8 {
public:
    static cv::dnn::Net net;
    static std::vector<std::string> labels;
};


#endif //OPENCV_LOADYOLOV8_H

//#ifndef MY_APPLICATION_JUSTCLASS_H
//#define MY_APPLICATION_JUSTCLASS_H
//
//#include "cutemodel/CuteModel.hpp"
//
//
//
//#endif //MY_APPLICATION_JUSTCLASS_H