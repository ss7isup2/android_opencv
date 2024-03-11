//
// Created by khc on 2024/03/11.
//

#ifndef OPENCV_RESULT_H
#define OPENCV_RESULT_H

class Result {
    public: cv::Rect box;
    public: float confidence;
    public: int index;
    public: cv::Mat maskMat;
    public: long maskMatAddr;
};

#endif //OPENCV_RESULT_H
