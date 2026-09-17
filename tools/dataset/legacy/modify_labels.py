import os

def modify_labels_in_folder(folder_path):
    label_map = {
        '0': '1', '1': '9', '2': '3', '3': '0', '4': '8',
        '5': '5', '6': '6', '7': '7', '8': '2', '9': '4'
    }
    
    for filename in os.listdir(folder_path):
        if filename.endswith(".txt"):  # 确保只处理 .txt 文件
            file_path = os.path.join(folder_path, filename)
            
            with open(file_path, 'r') as file:
                lines = file.readlines()
            
            modified_lines = []
            for line in lines:
                parts = line.strip().split()
                if parts and parts[0] in label_map:
                    parts[0] = label_map[parts[0]]  # 修改类别标签
                modified_lines.append(" ".join(parts))
            
            with open(file_path, 'w') as file:
                file.write("\n".join(modified_lines))
            
            print(f"Modified: {filename}")

# 调用函数，修改指定文件夹内的txt标签
folder_path = "D:/user/Desktop/dataset_3/labels"  # 请替换为你的文件夹路径

modify_labels_in_folder(folder_path)
