#include <stdio.h>

// 坐标转换函数
void transform_coordinates(double x_prime, double y_prime, double *x, double *y) {
    // 转换公式
    *x = -0.442060 * x_prime + -0.001511 * y_prime + 204.414347;
    *y = -0.002453 * x_prime + 0.447338 * y_prime + 18.974381;
}

int main() {
    // 测试数据
    double x_prime = 385, y_prime = 352; // 坐标2
    double x, y; // 转换后的坐标1

    // 调用转换函数
    transform_coordinates(x_prime, y_prime, &x, &y);

    // 输出结果
    printf("坐标2: (%.2f, %.2f)\n", x_prime, y_prime);
    printf("转换后的坐标1: (%.6f, %.6f)\n", x, y);

    return 0;
}