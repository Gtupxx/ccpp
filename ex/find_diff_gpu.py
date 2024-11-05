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
    img_bgr = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)
    
    # 使用 UMat 进行 GPU 加速
    gpu_img = cv2.UMat(img_bgr)
    return gpu_img

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

    resized_diff = resize_image(thresholded_diff)
    cv2.imshow("Difference", resized_diff.get())  # 使用 get() 从 UMat 转换回普通 Mat

def main():
    window_title = "大家来找茬"

    print("按下 'q' 退出程序")

    while True:

        try:
            region = get_window_region(window_title)
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

        # 捕获并上传到 GPU
        gpu_image1 = capture_region(region1)
        gpu_image2 = capture_region(region2)

        # 显示两幅图片的差异（使用 GPU 加速）
        show_difference(gpu_image1, gpu_image2)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cv2.destroyAllWindows()
