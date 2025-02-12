import cv2
import numpy as np
import matplotlib.pyplot as plt
image = cv2.imread('D:/SEM_6/IVPL/Assignment_02_IVP/girl.jpg', cv2.IMREAD_GRAYSCALE)
blurred = cv2.GaussianBlur(image, (5, 5), 0)
sharpening_kernel = np.array([[0, -1, 0],
                               [-1, 5, -1],
                               [0, -1, 0]])
sharpened = cv2.filter2D(image, -1, sharpening_kernel)
sobelx = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
sobely = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
edges = cv2.magnitude(sobelx, sobely)
edges = np.uint8(edges)
_, thresholded = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)
fig, axes = plt.subplots(1, 5, figsize=(15, 5))
axes[0].imshow(image, cmap='gray'); axes[0].set_title("Original")
axes[1].imshow(blurred, cmap='gray'); axes[1].set_title("Blurred")
axes[2].imshow(sharpened, cmap='gray'); axes[2].set_title("Sharpened")
axes[3].imshow(edges, cmap='gray'); axes[3].set_title("Edges")
axes[4].imshow(thresholded, cmap='gray'); axes[4].set_title("Thresholded")
for ax in axes:
    ax.axis("off")
plt.show()
