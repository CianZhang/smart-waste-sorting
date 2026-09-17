# 智能垃圾分类机器人
> 2025 年全国大学生工程实践与创新能力大赛全国一等奖作品

**[▶ 项目演示视频（哔哩哔哩）](https://www.bilibili.com/video/BV18GobY2Efq/)**

项目于我大三期间完成，制作时间为 **2025 年 12 月至 2026 年 3 月**。我负责机械结构设计、STM32 程序编写，以及 YOLOv8 模型的训练与部署；队友 **ccy** 负责树莓派端程序，并在 **zsq** 学长已有 Qt 界面代码的基础上完成界面适配。

这个项目中，我投入最多时间的是机械结构的设计、装配和反复调整。本文既介绍制作方法，也保留实际遇到的问题，希望能为后续复刻和改进提供参考。

基于 **树莓派 5、YOLOv8、STM32F103RCT6 与 CoreXY** 的智能垃圾分类装置。通过视觉识别、托盘倾倒和机械爪抓取完成四类垃圾分拣，并提供触摸界面、投料检测及满载提示。

**[完整制作教程](docs/build-guide.md)** · **[STM32 工程](firmware/stm32/README.md)** · **[树莓派程序](software/raspberry-pi/README.md)** · **[机械模型](hardware/README.md)**

## 项目组成

- 2020 铝型材框架、CoreXY 双步进平台、四舵机机械爪。
- 双舵机托盘、四面同步挡板、红外光幕和四路超声波。
- STM32 控制运动、串口及传感器；树莓派执行 YOLOv8 推理和 Qt/QML 界面。
- 完整教程包含 70 张图片、28 个功能 IO 的接线表、动作参数与省赛程序详解。

## 目录

```text
.
├── README.md
├── docs/                       # 完整制作教程、结构和版本说明
│   ├── build-guide.md
│   └── assets/
├── firmware/stm32/             # 已解压的省赛 Keil 工程
├── software/raspberry-pi/       # 已解压的省赛 Python / QML 应用
├── hardware/mechanical/        # SolidWorks 零件、装配与 STL
├── tools/
│   ├── vision/                 # 图像推理和训练入口
│   ├── calibration/            # 坐标标定程序及采样表
│   └── dataset/legacy/         # 历史采集及标签处理脚本
├── datasets/                   # 配置模板和历史类别顺序
├── models/                     # 部署权重的位置及校验说明
├── references/                 # 厂商资料与机械参考设计索引
├── scripts/                    # 仓库结构检查
├── .github/ISSUE_TEMPLATE/      # 问题反馈模板
└── .local-archive/              # 本地原始资料，Git 忽略
```

## 树莓派环境配置

[SSH、Python 与 YOLOv8 安装命令](docs/raspberry-pi-yolov8-setup.md) · [完整 TXT](docs/搭建yolov8环境.txt)

## 从哪里开始

1. 按 [制作教程](docs/build-guide.md) 制作框架与机构，完成单模块接线和标定。
2. 在 Keil 中打开 `firmware/stm32/Project.uvprojx`，核对开发板时钟与引脚；已知修正点见教程。
3. 按 [模型说明](models/README.md) 准备 `software/raspberry-pi/yolo/best.pt`，核对类别名称。
4. 在树莓派准备应用依赖，检查摄像头、串口和显示环境，然后从仓库根目录启动：

   ```sh
   sh software/raspberry-pi/run.sh
   ```

5. 通过界面进入识别页完成串口解锁，确认回零与上电等待结束，再进行空载及投料测试。

脚本会切换到正确的应用目录，不需要修改应用中的 QML、模型及图片相对路径。依赖清单尚不是经过实机验证的版本锁定文件。

## 本地检查

```sh
python3 scripts/check_repository.py
```

检查教程图片、Markdown 相对链接、Python 语法和 Keil 工程文件引用，不连接硬件、不加载权重、不改写标签。

## 参与与致谢

提交改动时说明使用的硬件、软件及模型版本，记录实际测试结果；参见 [贡献说明](CONTRIBUTING.md)。

作者负责机械结构、STM32 及模型训练部署，队友 ccy 负责树莓派程序，Qt 界面基于 zsq 学长的工作。

使用的第三方资料与贡献者见 [第三方资料与致谢](THIRD_PARTY_NOTICES.md)。
