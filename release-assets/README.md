# 完整资源下载

[GitHub Release](https://github.com/CianZhang/smart-waste-sorting/releases/tag/resources-v1)

部署权重已随源码仓库提供。以下大型附件需要从 Release 单独下载，源码 ZIP 不包含这些附件。

| 附件 | 大小 |
| --- | ---: |
| [training-data-and-history.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/training-data-and-history.zip) | 1483.67 MB |
| [stepper-motor-vendor-resources.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/stepper-motor-vendor-resources.zip) | 458.77 MB |
| [legacy-projects-and-provincial-originals.zip](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/legacy-projects-and-provincial-originals.zip) | 202.93 MB |
| [1.mp4](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/1.mp4) | 158.4 MB |
| [yolov8.zip.part001](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part001) | 1500.0 MB |
| [yolov8.zip.part002](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part002) | 1500.0 MB |
| [yolov8.zip.part003](https://github.com/CianZhang/smart-waste-sorting/releases/download/resources-v1/yolov8.zip.part003) | 978.8 MB |

## 附件用途

- `1.mp4`: 下载后放入 `software/raspberry-pi/qml/1.mp4`.
- `training-data-and-history.zip`: 训练图片、标签、历史权重、训练结果与训练工程，保留原始目录结构。不同轮次的类别顺序不可直接混用。
- `stepper-motor-vendor-resources.zip`: 张大头步进电机完整说明书、工具、例程和演示视频。
- `legacy-projects-and-provincial-originals.zip`: 旧版 STM32 工程（含编译产物）及省赛原始压缩包。
- `yolov8.zip.part001` 至 `part003`：原始 yolov8.zip 的字节分卷，必须全部下载后合并，不能单独解压。

## 合并 yolov8.zip

macOS / Linux:

```sh
cat yolov8.zip.part001 yolov8.zip.part002 yolov8.zip.part003 > yolov8.zip
```

Windows CMD:

```bat
copy /b yolov8.zip.part001+yolov8.zip.part002+yolov8.zip.part003 yolov8.zip
```

合并完成后可解压。完整文件的 SHA-256：

```text
67cd5b0eae3dfe495bd9983304eb3f1da0dc6049562c12e1c48cc26f418390c0  yolov8.zip
```

附件校验值见 [SHA256SUMS.txt](SHA256SUMS.txt)，来源、文件数量与大小见 [manifest.json](manifest.json)。macOS 使用 `shasum -a 256 -c SHA256SUMS.txt`，Linux 使用 `sha256sum -c SHA256SUMS.txt`。

本地附件实体保存在可见的 `release-assets/` 文件夹，Git 只记录说明与校验清单。原始资料保留在 `.local-archive/original/`。系统镜像与个人初始化资料不在本次发布范围内。历史代码和模型按原样提供，未执行程序或加载模型。
