# 辅助工具

## 图像测试

从仓库根目录执行，输入图片不会连接相机或 STM32：

```sh
python3 tools/vision/test.py --source datasets/local/test_images
```

需要提前准备图片和 [部署模型](../models/README.md)。也可通过 `--weights` 指定其他本地权重，默认输出为 `outputs/test_result/result_0.jpg` 等。

## 训练

```sh
python3 tools/vision/train.py --weights models/local/initial.pt --data datasets/local/data.yaml --epochs 500
```

示例中的文件需要自行准备。训练和图像测试入口已改为显式传参，不再依赖原电脑的绝对目录。默认输出位于根目录 `outputs/`，由 Git 忽略。`--help` 不加载模型或第三方依赖。

## 坐标标定

`calibration/main.py` 用最小二乘拟合二维映射；`main.c` 与 Excel 表为对应资料。程序中的标定点来自既有机构，必须在新机构上重新采集，见制作教程。

## 历史采集与标签工具

`dataset/legacy/` 中保存采集、改名、标签映射和数据拆分脚本，以及 `classes.txt`。这些脚本保留历史路径和修改行为，用于查看制作过程；不要直接批量运行，其中部分会原地改写标签或重命名图片。

历史类别合并有不同版本，必须与权重类别定义核对；完整数据仍在本地归档。本次没有对数据集重新划分或改写标签。
