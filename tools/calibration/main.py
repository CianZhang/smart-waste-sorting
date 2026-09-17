import numpy as np

# 源坐标系坐标 (坐标1)
src = [
    (110, 80), (60, 80), (65, 150), (43, 168), (34, 175),
    (26, 58), (20, 33), (56, 43), (62, 78), (89, 98),
    (150, 155), (142, 87), (118, 65), (97, 73),
    (37, 138), (49, 141), (39, 159), (18, 163), (7, 171)
]

# 目标坐标系坐标 (坐标2)
dst = [
    (213, 138), (327, 139), (313, 295), (365, 336), (385, 352),
    (403, 89), (416, 33), (336, 56), (321, 133), (262, 179),
    (121, 304), (141, 152), (194, 104), (244, 123), 
    (378, 268), (351, 274), (373, 314), (420, 324), (445, 342)
]

# 构造系数矩阵和观测向量
A = []
B_x, B_y = [], []
for (x, y), (tx, ty) in zip(src, dst):
    A.append([tx, ty, 1])
    B_x.append(x)
    B_y.append(y)

A = np.array(A)
B_x = np.array(B_x)
B_y = np.array(B_y)

# 最小二乘求解变换参数
params_x = np.linalg.lstsq(A, B_x, rcond=None)[0]
params_y = np.linalg.lstsq(A, B_y, rcond=None)[0]

a, b, c = params_x
d, e, f = params_y

print("坐标转换公式：")
print(f"x = {a:.6f}x' + {b:.6f}y' + {c:.6f}")
print(f"y = {d:.6f}x' + {e:.6f}y' + {f:.6f}\n")

# 转换函数
def inverse_coordinate_transform(x_prime, y_prime):
    return (
        a * x_prime + b * y_prime + c,
        d * x_prime + e * y_prime + f
    )

# 验证转换结果
print("验证转换结果（19个点）：")
for i in range(19):
    x_src, y_src = src[i]
    x_dst, y_dst = dst[i]
    x_pred, y_pred = inverse_coordinate_transform(x_dst, y_dst)
    print(f"目标坐标：({x_dst}, {y_dst})")
    print(f"预测坐标：({x_pred:.2f}, {y_pred:.2f})")
    print(f"实际坐标：({x_src}, {y_src})")
    print(f"误差：X {abs(x_pred-x_src):.2f}, Y {abs(y_pred-y_src):.2f}\n")