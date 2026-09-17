import os
import random
import shutil

def split_yolo_dataset(dataset_path, output_path, split_ratio=0.8):
    """
    按照 8:2 的比例随机拆分 YOLO 数据集。
    :param dataset_path: YOLO 数据集路径，包含 images 和 labels 文件夹。
    :param output_path: 输出的训练集和验证集路径。
    :param split_ratio: 训练集比例，默认为 0.8。
    """
    images_path = os.path.join(dataset_path, "images")
    labels_path = os.path.join(dataset_path, "labels")
    
    train_images_path = os.path.join(output_path, "train/images")
    train_labels_path = os.path.join(output_path, "train/labels")
    val_images_path = os.path.join(output_path, "val/images")
    val_labels_path = os.path.join(output_path, "val/labels")
    
    os.makedirs(train_images_path, exist_ok=True)
    os.makedirs(train_labels_path, exist_ok=True)
    os.makedirs(val_images_path, exist_ok=True)
    os.makedirs(val_labels_path, exist_ok=True)
    
    image_files = [f for f in os.listdir(images_path) if f.endswith(".jpg") or f.endswith(".png")]
    random.shuffle(image_files)
    
    split_index = int(len(image_files) * split_ratio)
    train_files = image_files[:split_index]
    val_files = image_files[split_index:]
    
    def move_files(files, src_img_path, src_lbl_path, dest_img_path, dest_lbl_path):
        for file in files:
            img_src = os.path.join(src_img_path, file)
            lbl_src = os.path.join(src_lbl_path, file.replace(os.path.splitext(file)[1], ".txt"))
            
            img_dest = os.path.join(dest_img_path, file)
            lbl_dest = os.path.join(dest_lbl_path, file.replace(os.path.splitext(file)[1], ".txt"))
            
            if os.path.exists(img_src):
                shutil.copy(img_src, img_dest)
            if os.path.exists(lbl_src):
                shutil.copy(lbl_src, lbl_dest)
    
    move_files(train_files, images_path, labels_path, train_images_path, train_labels_path)
    move_files(val_files, images_path, labels_path, val_images_path, val_labels_path)
    
    print(f"数据集拆分完成：训练集 {len(train_files)} 张，验证集 {len(val_files)} 张。")

# 调用函数，传入你的数据集路径和输出路径
dataset_path = "D:/user/Desktop/dataset_3"  # 替换为你的 YOLO 数据集路径
output_path = "D:/user/Desktop/dataset"  # 替换为拆分后数据集的存放路径
split_yolo_dataset(dataset_path, output_path)
