# STM32 省赛工程

使用 `Project.uvprojx`，目标器件为 STM32F103RC，控制板按 STM32F103RCT6 接线。工程记录的编译器为 ARMCC V5.06 update 5（build 528）。

- `User/main.c`：完整分拣入口。
- `Hardware/`：舵机、CoreXY、传感器、串口及动作组合。
- `System/`：延时与 TIM7 配置。
- `Start/`：启动文件及系统时钟。
- `Library/`：随工程保留的 STM32 标准外设库，版权头保留。

完整 IO 表、回零时序、角度、坐标及已知问题见 [制作教程](../../docs/build-guide.md)。目录中的文件不一定都参与编译，以工程文件列表为准；不要把同名 PWM 实现重复加入工程。

本目录按省赛源码保存，未自动应用教程里的控制逻辑修正。特别是第四路 Echo PB15 的初始化需要按教程处理。编译缓存和个人 Keil 窗口状态不纳入 Git。
