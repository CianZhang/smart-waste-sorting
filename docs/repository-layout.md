# 目录迁移说明

项目根目录仍为原来的“工训赛”文件夹。制作资料组织为公开项目内容和本地原始归档两部分。

## 主要入口

| 内容 | 新位置 |
| --- | --- |
| 项目首页 | [README](../README.md) |
| 详细制作教程 | [build-guide.md](build-guide.md) |
| 教程图片 | `docs/assets/` |
| STM32 工程 | [固件说明](../firmware/stm32/README.md) |
| 树莓派应用 | [应用说明](../software/raspberry-pi/README.md) |
| 机械模型 | [模型目录说明](../hardware/README.md) |
| 训练、测试与标定 | [工具说明](../tools/README.md) |

## 环境配置资料

树莓派 YOLOv8 安装记录已纳入公开目录：[环境配置文档](raspberry-pi-yolov8-setup.md) 与 [完整 TXT](搭建yolov8环境.txt)。TXT 与本地归档文件内容一致。

## 原资料保留位置

所有整理前的根目录项目整体移入 `.local-archive/original/`，保持其原有子目录关系。没有删除原文件，系统镜像和数据也没有重复复制到公开项目。

| 整理前位置 | 原始副本位置 | 提供的公开入口 |
| --- | --- | --- |
| `工训赛-智能垃圾分类.md` | `.local-archive/original/工训赛-智能垃圾分类.md` | `docs/build-guide.md` |
| `工训赛-智能垃圾分类.assets/` | `.local-archive/original/工训赛-智能垃圾分类.assets/` | `docs/assets/` |
| `建模/` | `.local-archive/original/建模/` | `hardware/mechanical/`，独立参考包除外 |
| `代码/省赛代码/` | `.local-archive/original/代码/省赛代码/` | 已解压到固件和应用目录 |
| `代码/坐标映射/` | `.local-archive/original/代码/坐标映射/` | `tools/calibration/` |
| `代码/get_photo/` | `.local-archive/original/代码/get_photo/` | `tools/dataset/legacy/` |
| `代码/树莓派/` | `.local-archive/original/代码/树莓派/` | 可移植入口位于 `tools/vision/` |
| 旧工程、训练数据、镜像、安装包 | `.local-archive/original/代码/` | 本地归档，Git 忽略 |
| `张大头步进电机资料/` | `.local-archive/original/张大头步进电机资料/` | `references/README.md` 提供索引 |

`.local-archive/inventory-before.json` 记录迁移前的相对路径、大小和修改时间；`migration-report.json` 记录整理时的验证结果。两者只保存在本地归档。

## 提交范围

`.gitignore` 排除本地归档、模型、展示视频、推理图片、构建缓存和个人环境文件。权重与视频留在应用原位置，源码克隆时需要另外准备。

公开仓库只包含上述整理后的项目内容；本地原始归档不随 Git 提交上传。
