# 树莓派 YOLOv8 环境配置

本项目的树莓派环境配置记录，包含 SSH 远程连接、Python 编译安装和 YOLOv8 相关依赖安装。

[查看完整命令 TXT](搭建yolov8环境.txt)

## 记录的环境

| 项目 | 版本或说明 |
| --- | --- |
| 操作系统 | Ubuntu 24.04.1 LTS 桌面版 |
| Python | 3.10.16 |
| PyTorch | torch 2.0.0 |
| torchvision | 0.15.1 |
| torchaudio | 2.0.1 |
| NumPy | 1.23.5 |
| ultralytics | 安装命令未固定版本 |

以下命令按项目保存的配置记录整理，尚未在目标树莓派上重新验证。这里记录的是 YOLOv8 环境；完整 Qt 应用还需要 PySide6、pyserial 等依赖，参见 [树莓派应用说明](../software/raspberry-pi/README.md)。

## 1. 启用 SSH

在树莓派上执行：

```sh
sudo apt update

sudo apt install openssh-server

sudo systemctl enable ssh

sudo systemctl start ssh

sudo systemctl status ssh
```

状态显示 `active (running)` 表示 SSH 已启动。查看树莓派 IP：

```sh
hostname -I
```

然后在电脑端通过 VS Code 的远程连接功能连接树莓派。

如果树莓派已重装系统，电脑上仍保存了该地址对应的旧主机密钥，在确认目标设备身份后，可在电脑终端移除旧记录：

```sh
ssh-keygen -R <树莓派的IP地址>
```

将占位符替换为实际 IP，再重新连接。

## 2. 编译安装 Python 3.10.16

在树莓派上执行：

```sh
sudo apt update

sudo apt upgrade -y

sudo apt install -y build-essential libssl-dev zlib1g-dev libbz2-dev \
                    libreadline-dev libsqlite3-dev wget curl llvm \
                    libncurses5-dev libncursesw5-dev libffi-dev \
                    liblzma-dev python3-openssl git

cd ~

wget https://www.python.org/ftp/python/3.10.16/Python-3.10.16.tgz

tar -xvzf Python-3.10.16.tgz

cd Python-3.10.16

./configure --enable-optimizations

make -j 4 

sudo make altinstall

sudo update-alternatives --install /usr/bin/python3 python3 /usr/local/bin/python3.10 1
```

上述记录包含通过 `update-alternatives` 改变 `python3` 指向的操作。检查解释器版本：

```sh
python3 --version
```

记录中的预期结果：

```text
Python 3.10.16
```

## 3. 安装 PyTorch、YOLOv8 和 NumPy

```sh
sudo apt-get update

sudo apt-get upgrade

sudo apt install python3-pip

sudo pip install torch==2.0.0 torchvision==0.15.1 torchaudio==2.0.1 --index-url https://download.pytorch.org/whl/cpu -i https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple --trusted-host=https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple

sudo pip install ultralytics -i https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple --trusted-host=https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple

sudo pip install numpy==1.23.5

python3 -m pip install numpy==1.23.5
```

这里保留了记录中的版本号、镜像参数和两种 NumPy 安装写法；它们不是已经锁定并重新验证过的依赖环境。最终使用的解释器、包版本和目标平台兼容性应通过实机验证记录下来。

## 4. 接入项目运行流程

准备好模型、串口和摄像头后，按 [树莓派应用说明](../software/raspberry-pi/README.md) 启动程序。机械接线、IO 表、标定及分拣流程见 [完整制作教程](build-guide.md)。
