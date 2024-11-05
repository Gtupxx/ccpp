import cv2
import numpy as np

# 创建一个空白图像或加载一张图像
image = cv2.imread('example.jpg')

if image is None:
    image = np.zeros((500, 500, 3), dtype=np.uint8)  # 如果没有图像，则创建一个空白图像
def haha(img):

    # 圆的参数列表（圆心坐标、半径、颜色）
    circles = [
        ((100, 200), 50, (0, 255, 0)),
        ((200, 200), 75, (255, 0, 0)),
        ((300, 300), 60, (0, 0, 255)),
        ((400, 100), 40, (255, 255, 0))
    ]

    # 透明度
    alpha = 0.5

    # 循环绘制并叠加圆形
    for center, radius, color in circles:
        overlay = img.copy()  # 创建图像副本
        cv2.circle(overlay, center, radius, color, -1)  # 在副本上绘制圆形
        img = cv2.addWeighted(overlay, alpha, img, 1 - alpha, 0)  # 将副本叠加到原图像上

# 显示结果图像
haha(image)
cv2.imshow('Overlay Circles', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
