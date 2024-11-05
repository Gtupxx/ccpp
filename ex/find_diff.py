import cv2
import numpy as np
from PIL import ImageGrab
import pygetwindow as gw
import time


def get_window_region(window_title):
    """获取指定窗口的位置和大小"""
    windows = gw.getWindowsWithTitle(window_title)
    if not windows:
        raise ValueError(f"未找到标题为 '{window_title}' 的窗口")
    window = windows[0]
    return (window.left, window.top, window.right, window.bottom)


def capture_region(region):
    """捕获指定区域的截图"""
    screenshot = ImageGrab.grab(bbox=region)
    return cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)


def resize_image(image, scale=1.5):
    """将图像按比例缩放"""
    width = int(image.shape[1] * scale)
    height = int(image.shape[0] * scale)
    return cv2.resize(image, (width, height), interpolation=cv2.INTER_AREA)


def show_difference(image1, image2):
    """计算并显示两幅图片的差异"""
    diff = cv2.absdiff(image1, image2)
    gray_diff = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)
    _, thresholded_diff = cv2.threshold(gray_diff, 30, 255, cv2.THRESH_BINARY)

    # 缩小差异图像
    resized_diff = resize_image(thresholded_diff)
    cv2.imshow("Difference", resized_diff)


def show_difference_RGB(image1, image2):
    """计算并显示两幅图片的彩色差异"""
    # 计算RGB通道的绝对差异
    diff = cv2.absdiff(image1, image2)

    # 将差异图像按比例缩小
    resized_diff = resize_image(diff)

    # 显示彩色差异图像
    cv2.imshow("Difference", resized_diff)

def main():
    window_title = "大家来找茬"

    print("按下 'q' 退出程序")

    while True:

        try:
            region = get_window_region(window_title)
            # print(f"捕捉区域：{region}")
        except ValueError as e:
            time.sleep(0.5)
            continue

        region1 = (
            region[0] + 6,
            region[1] + 199,
            region[0] + 6 + 502,
            region[1] + 199 + 450,
        )
        region2 = (
            region[0] + 515,
            region[1] + 199,
            region[0] + 515 + 502,
            region[1] + 199 + 450,
        )

        image1 = capture_region(region1)
        image2 = capture_region(region2)
        
        # 缩小图像
        resized_image1 = resize_image(image1)
        resized_image2 = resize_image(image2)

        # 显示两幅图片的差异
        show_difference_RGB(image1, image2)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
