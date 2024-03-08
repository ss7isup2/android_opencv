package com.aos.opencv

import org.opencv.core.Mat
import org.opencv.core.Rect

data class Result(var box: Rect, val confidence: Float, val index: Int, var maskMat: Mat, var maskMatAddr: Long)