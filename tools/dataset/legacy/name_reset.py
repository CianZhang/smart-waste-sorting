import os

def rename_images(folder_path):
    # 获取文件夹内所有 .jpg 文件
    files = [f for f in os.listdir(folder_path) if f.lower().endswith('.jpg')]
    
    # 按文件创建时间排序
    files.sort(key=lambda f: os.path.getctime(os.path.join(folder_path, f)))
    
    # 遍历文件并按 1, 2, 3, 4... 重命名
    for index, filename in enumerate(files, start=1):
        old_path = os.path.join(folder_path, filename)
        new_path = os.path.join(folder_path, f"{index}.jpg")
        
        try:
            os.rename(old_path, new_path)
            print(f"重命名: {filename} → {index}.jpg")
        except Exception as e:
            print(f"重命名失败 {filename}: {e}")

# 设置要重命名的文件夹路径
folder_path = r"D:\user\Desktop\dataset_3\images"  # 你需要修改为你的文件夹路径
rename_images(folder_path)
