import cv2
import os

def ensure_directory(directory):
    """ 确保目录存在 """
    if not os.path.exists(directory):
        os.makedirs(directory)

def get_next_filename(directory):
    """ 获取下一个可用的顺序编号文件名 """
    existing_files = [f for f in os.listdir(directory) if f.endswith(".jpg")]
    numbers = [int(f.split(".")[0]) for f in existing_files if f.split(".")[0].isdigit()]
    next_number = max(numbers) + 1 if numbers else 1
    return os.path.join(directory, f"{next_number}.jpg")

def capture_photos():
    save_dir = "D:/user/Desktop/dataset_3/images"  # 存储照片的文件夹
    ensure_directory(save_dir)
    
    cap = cv2.VideoCapture(0)  # 0 代表默认摄像头
    if not cap.isOpened():
        print("无法打开摄像头")
        return
    
    print("按 Enter 拍照，按 ESC 退出")
    while True:
        ret, frame = cap.read()
        if not ret:
            print("无法读取摄像头画面")
            break
        
        cv2.imshow("Press Enter to Capture", frame)
        key = cv2.waitKey(1) & 0xFF
        
        if key == 13:  # Enter 键
            filename = get_next_filename(save_dir)
            cv2.imwrite(filename, frame)
            print(f"照片已保存: {filename}")
        elif key == 27:  # ESC 键退出
            break
    
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    capture_photos()
