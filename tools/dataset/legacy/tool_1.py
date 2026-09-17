# 80%的数据用于训练，20%用于验证，随机抽样
import os
import shutil
import random

# 设置文件夹路径
images_dir = "/home/ipeas/yolov8/ultralytics-main/DATA/images"  # 替换为你的images文件夹路径
labels_dir = "/home/ipeas/yolov8/ultralytics-main/DATA/labels"  # 替换为你的labels文件夹路径

# 设置目标目录
train_images_dir = "/home/ipeas/yolov8/ultralytics-main/dataset/images/train"
val_images_dir = "/home/ipeas/yolov8/ultralytics-main/dataset/images/val"
train_labels_dir = "/home/ipeas/yolov8/ultralytics-main/dataset/labels/train"
val_labels_dir = "/home/ipeas/yolov8/ultralytics-main/dataset/labels/val"

# 创建目标目录（如果不存在）
os.makedirs(train_images_dir, exist_ok=True)
os.makedirs(val_images_dir, exist_ok=True)
os.makedirs(train_labels_dir, exist_ok=True)
os.makedirs(val_labels_dir, exist_ok=True)

# 获取所有图片文件名
image_files = [f for f in os.listdir(images_dir) if f.endswith('.jpg') or f.endswith('.png')]  # 根据图片格式调整

# 打乱图片文件列表
random.shuffle(image_files)

# 设定训练集和验证集的比例，80%训练集，20%验证集
train_size = int(0.8 * len(image_files))
train_files = image_files[:train_size]
val_files = image_files[train_size:]

# 复制训练集和验证集的图片及标签
for file in train_files:
    # 复制图片
    shutil.copy(os.path.join(images_dir, file), os.path.join(train_images_dir, file))
    # 复制标签
    label_file = file.replace('.jpg', '.txt').replace('.png', '.txt')  # 假设标签是txt格式
    shutil.copy(os.path.join(labels_dir, label_file), os.path.join(train_labels_dir, label_file))

for file in val_files:
    # 复制图片
    shutil.copy(os.path.join(images_dir, file), os.path.join(val_images_dir, file))
    # 复制标签
    label_file = file.replace('.jpg', '.txt').replace('.png', '.txt')
    shutil.copy(os.path.join(labels_dir, label_file), os.path.join(val_labels_dir, label_file))

print("Data split completed.")
