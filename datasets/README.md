# 数据集与类别配置

完整训练数据留在本地 `.local-archive/original/代码/` 中。新增数据放在 `datasets/local/`，Git 默认忽略该目录。

- `data.example.yaml`：按历史 `classes.txt` 整理的十类模板，必须改路径并核对标签后使用。
- `config-history/`：三轮训练的四类名称和顺序快照；路径使用 `<DATASET_ROOT>` 占位，不能直接拿来训练。

不同轮次的类别编号顺序存在差异，不能仅因为都是四类就互换 YAML、标签和权重。省赛应用按具体物体名称映射到四大类，详见制作教程。

发布数据时应补充来源、类别定义及使用范围。各轮训练质量以实际测试结果为准。

## 补充资源下载

训练图片、标签、历史权重与结果、电机厂商完整资料、旧版工程及编译产物、省赛原始压缩包、展示视频和 `yolov8.zip` 已整理为 [GitHub Release 附件](https://github.com/CianZhang/smart-waste-sorting/releases/tag/resources-v1)。分类、还原方式与校验值见 [资源下载说明](../release-assets/README.md)。本地附件位于根目录可见的 `release-assets/` 文件夹，原始归档继续保留。部署权重 `software/raspberry-pi/yolo/best.pt` 已直接纳入源码仓库。
