# 模型权重

部署模型位于 `software/raspberry-pi/yolo/best.pt`，已纳入 Git 仓库，克隆项目即可获得该部署权重。

| 项目 | 内容 |
| --- | --- |
| 来源 | 省赛 Python 3.19 压缩包中的 `yolo/best.pt` |
| 文件大小 | 22536814 字节 |
| SHA-256 | `0e9ade16c99730c9233939a2b89183e47f08c946b4a3c8519184833ff6c6b524` |

原压缩包留在本地 `.local-archive/original/代码/省赛代码/`。原始压缩包与历史训练资料同时提供于 [GitHub Release](https://github.com/CianZhang/smart-waste-sorting/releases/tag/resources-v1)，文件说明见 [资源下载说明](../release-assets/README.md)。

程序使用模型中的物体名称映射到四类垃圾，部署前核对 `model.names`。历史数据含不同类别体系，不能仅按文件名 `best.pt` 判断是否匹配。

自行训练的权重可以暂存于 `models/local/`，该目录由 Git 忽略。没有执行加载或推理验证，也没有从不可信的模型文件反序列化内容。
