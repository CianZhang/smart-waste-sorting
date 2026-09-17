import os

# 标签映射规则
label_mapping = {
    '2': '0',  # 将 2、3、9 改为 0
    '3': '0',
    '9': '0',
    '4': '1',  # 将 4、5、6 改为 1
    '5': '1',
    '6': '1',
    '0': '2',  # 将 0、1 改为 2
    '1': '2',
    '7': '3',  # 将 7、8 改为 3
    '8': '3'
}

# 修改标签的函数
def modify_labels(txt_file_path):
    with open(txt_file_path, 'r') as file:
        lines = file.readlines()

    with open(txt_file_path, 'w') as file:
        for line in lines:
            parts = line.split()
            label = parts[0]

            if label in label_mapping:
                parts[0] = label_mapping[label]  # 替换标签

            file.write(' '.join(parts) + '\n')

# 遍历文件夹中的所有 txt 文件
def modify_labels_in_directory(directory_path):
    for filename in os.listdir(directory_path):
        if filename.endswith('.txt'):
            file_path = os.path.join(directory_path, filename)
            modify_labels(file_path)
            print(f'标签已修改: {filename}')

# 指定要修改标签的文件夹路径
directory_path = '/home/ipeas/yolov8/ultralytics-main/dataset/labels/val'  # 修改为你的文件夹路径
modify_labels_in_directory(directory_path)
