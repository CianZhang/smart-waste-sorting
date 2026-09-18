# 树莓派省赛应用

应用入口为本目录的 `main.py`。`qml/main.py` 是另一个界面入口，不作为完整系统启动入口。

## 环境配置命令

项目保存的 Ubuntu 24.04.1 LTS、Python 3.10.16 和 YOLOv8 配置命令已整理为 [环境配置文档](../../docs/raspberry-pi-yolov8-setup.md)，也可查看 [完整 TXT](../../docs/搭建yolov8环境.txt)。这份记录覆盖 YOLOv8 安装；Qt 应用依赖仍需按下文准备。

## 运行准备

需要 ultralytics、OpenCV、pyserial 和 PySide6，依赖名称列在 `requirements.txt`。操作系统、Python、PyTorch 和 Qt 的具体组合仍需在目标树莓派验证，没有把未核实的版本标为可复现环境。

确认以下条件后，从仓库根目录运行：

```sh
sh software/raspberry-pi/run.sh
```

可以通过 `PYTHON` 指定已经配置好的解释器。启动器只切换工作目录并准备结果图片目录，不自动安装软件、不自动修改硬件设置。

| 资源/配置 | 当前使用位置 |
| --- | --- |
| 模型 | `yolo/best.pt` |
| 摄像头 | `main.py` 中 `cv.VideoCapture(0)` |
| 串口 | `main.py` 中 `/dev/ttyAMA0`、115200 |
| 界面 | `qml/main.qml`，布局为 1280 × 800 |
| 推理图片 | `yolo/pics/`，Git 忽略 |
| 展示视频 | `qml/1.mp4`，Git 忽略 |

## 模型和视频

部署模型 `yolo/best.pt` 已纳入 Git 仓库。展示视频请从 [GitHub Release](https://github.com/CianZhang/smart-waste-sorting/releases/tag/resources-v1) 下载 `1.mp4`，放到本目录的 `qml/1.mp4`。

模型来源与校验值见 [模型说明](../../models/README.md)。展示页使用 `qml/1.mp4`，下载后保持文件名和位置一致；不使用展示页时可相应调整界面。没有视频不代表视觉识别代码或模型缺失。

省赛原始压缩包及历史结果图位于本地归档，具体位置见 [目录迁移说明](../../docs/repository-layout.md)。

## 已知行为

代码保留省赛识别和计数逻辑。首次未识别到目标时随机分类、识别前置计数、串口超时不足等问题已在 [完整教程](../../docs/build-guide.md) 中说明。运行前先做模块测试，不把桌面静态检查当作整机验证。
