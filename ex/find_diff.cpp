#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <string>
#include <iostream>

// 捕获指定区域的屏幕截图并返回为 cv::Mat 格式
cv::Mat captureRegion(int x, int y, int width, int height) {
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    SelectObject(hDC, hBitmap);

    // 将屏幕内容复制到位图中
    BitBlt(hDC, 0, 0, width, height, hScreen, x, y, SRCCOPY);
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // 注意：负数表示自上而下的图像
    bi.biPlanes = 1;
    bi.biBitCount = 24;  // 每个像素24位
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    cv::Mat mat(height, width, CV_8UC3);  // 创建OpenCV图像矩阵
    GetDIBits(hDC, hBitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // 释放资源
    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);

    return mat;
}

// 调整图像尺寸
cv::Mat resizeImage(const cv::Mat& image, double scale = 1.5) {
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(), scale, scale, cv::INTER_AREA);
    return resized;
}

// 显示两幅图片的彩色差异
void showDifferenceRGB(const cv::Mat& image1, const cv::Mat& image2) {
    cv::Mat diff;
    cv::absdiff(image1, image2, diff);  // 计算RGB通道的绝对差异
    cv::Mat resizedDiff = resizeImage(diff);
    cv::imshow("Difference", resizedDiff);
}

int main() {
    std::string windowTitle = "大家来找茬";
    std::cout << "按下 'q' 退出程序" << std::endl;

    // 捕获区域参数
    int x1 = 6, y1 = 199, width = 502, height = 450;
    int x2 = 515, y2 = 199;

    while (true) {
        // 捕获两个区域的图像
        cv::Mat image1 = captureRegion(x1, y1, width, height);
        cv::Mat resizedImage1 = resizeImage(image1);
        cv::imshow("Image 1", resizedImage1);

        cv::Mat image2 = captureRegion(x2, y2, width, height);
        cv::Mat resizedImage2 = resizeImage(image2);
        cv::imshow("Image 2", resizedImage2);

        // 显示两幅图片的彩色差异
        showDifferenceRGB(image1, image2);

        // 按下 'q' 键退出程序
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
