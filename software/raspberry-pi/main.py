import sys
import time
import cv2 as cv
from ultralytics import YOLO
import serial
import random

from PySide6.QtGui import QGuiApplication,QImage,QPixmap
from PySide6.QtQuick import QQuickImageProvider
from PySide6.QtWidgets import QWidget,QLabel
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import QThread,Slot,Signal,QObject

class VideoFrameProvider(QQuickImageProvider):
	def __init__(self):
		super().__init__(QQuickImageProvider.Image)
		self.image = QImage()

	def requestImage(self, id, size, requestedSize):
		return self.image

	def update_image(self, image):
		self.image = image

class TestSystem(QObject):
	frame_ready = Signal()
	find_trash = Signal(int, str)
	is_full = Signal(int, int, int, int)

	def __init__(self, image_provider):
		super().__init__()

		self.model = YOLO("yolo/best.pt")

		self.ser = serial.Serial("/dev/ttyAMA0", 115200)

		self.counter = 0# 拍摄照片张数
		self.total = 0# 检测到的垃圾数量
		self.number = 0# 投入垃圾序号
		self.itemClass = 0# 垃圾种类
		self.trashDict = self.trash_dict()

		# 满溢检测标志
		self.one = 0
		self.two = 0
		self.three = 0
		self.four = 0

		self.image_provider = image_provider


		self.button_thread = QThread(self)
		self.button_thread.run = self.serial_receive
		self.button_thread.start()

	def test_send(self, frame):
		results = self.model.predict(frame, conf=0.7, verbose=False)
		img_result = results[0].plot()
		img_path = f"yolo/pics/test_{self.counter}.jpg"
		cv.imwrite(img_path, img_result)
		print("已拍摄图片%d" %self.counter)

		Qframe = cv.cvtColor(img_result, cv.COLOR_BGR2RGB)
		h, w, ch = Qframe.shape
		bytes_per_line = ch * w
		img_qml = QImage(Qframe.data, w, h, bytes_per_line, QImage.Format_RGB888)
		self.image_provider.update_image(img_qml)
		self.frame_ready.emit()
		for result in results:
			boxes = result.boxes
			classes = []
			positions = []
			for box in boxes:
				self.total += 1
				item = self.trashDict.get(self.model.names[box.cls.item()], "Unknown")
				if item == "harmful":
					classes.append(item)
					positions.append(box.xywh)
				else:
					classes.insert(0, item)
					positions.insert(0, box.xywh)

				#if box.conf > conf:
				#	conf = box.conf
				#	self.itemClass = box.cls.item()
				#	position = box.xywh
			if len(classes) == 0:# 如果没有检测到物体
				break
			else:# 检测到物体
				self.itemClass = classes[0]
				position = positions[0]
				if self.total > 1:# 检测到大于一个物体
					same_flag = 1
					for other in classes:
						if self.itemClass != other:
							same_flag = 0
							break
					if same_flag == 1:# 物体全相同
						for item in classes:
							self.number += 1
							self.find_trash.emit(self.number, item)
						if self.itemClass == 'harmful':
							self.ser.write(b"1")
						elif self.itemClass == 'recycle':
							self.ser.write(b"3")
						elif self.itemClass == 'kitchen':
							self.ser.write(b"2")
						elif self.itemClass == 'others':
							self.ser.write(b"4")
					else:# 物体不全相同
						self.number += 1
						self.find_trash.emit(self.number, self.itemClass)
						sendbyte = 0
						if self.itemClass == 'harmful':
							sendbyte = 1
						elif self.itemClass == 'recycle':
							sendbyte = 3
						elif self.itemClass == 'kitchen':
							sendbyte = 2
						elif self.itemClass == 'others':
							sendbyte = 4
						pos_x = int(position[0][0])
						pos_y = int(position[0][1])
						mes = f"{pos_x:03d}" + f"{pos_y:03d}" + f"{sendbyte}"
						self.ser.write(b"5" + bytes(mes, encoding = "ascii") + b"\n")
				else:# 只检测到一个物体
					self.number += 1
					self.itemClass = classes[0]
					self.find_trash.emit(self.number, self.itemClass)
					if self.itemClass == 'harmful':
						self.ser.write(b"1")
					elif self.itemClass == 'recycle':
						self.ser.write(b"3")
					elif self.itemClass == 'kitchen':
						self.ser.write(b"2")
					elif self.itemClass == 'others':
						self.ser.write(b"4")
		if len(classes) == 0:# 没有检测到物体的处理
			self.number += 1
			randnum = random.randint(0, 9)
			print(randnum)
			self.itemClass = self.trashDict.get(self.model.names[randnum], "Unknown")
			self.find_trash.emit(self.number, self.itemClass)
			if self.itemClass == 'harmful':
				self.ser.write(b"1")
			elif self.itemClass == 'recycle':
				self.ser.write(b"3")
			elif self.itemClass == 'kitchen':
				self.ser.write(b"2")
			elif self.itemClass == 'others':
				self.ser.write(b"4")
		self.total = 0

	def check(self, frame):
		results = self.model.predict(frame, conf=0.7, verbose=False)
		img_result = results[0].plot()
		img_path = f"yolo/pics/test_{self.counter}.jpg"
		cv.imwrite(img_path, img_result)
		print("已拍摄图片%d" %self.counter)

		Qframe = cv.cvtColor(img_result, cv.COLOR_BGR2RGB)
		h, w, ch = Qframe.shape
		bytes_per_line = ch * w
		img_qml = QImage(Qframe.data, w, h, bytes_per_line, QImage.Format_RGB888)
		self.image_provider.update_image(img_qml)
		self.frame_ready.emit()
		for result in results:
			boxes = result.boxes
			classes = []
			positions = []
			for box in boxes:
				self.total += 1
				item = self.trashDict.get(self.model.names[box.cls.item()], "Unknown")
#				if item == "harmful":
#					classes.append(item)
#					positions.append(box.xywh)
#				else:
				classes.insert(0, item)
				positions.insert(0, box.xywh)
				#if box.conf > conf:
				#	conf = box.conf
				#	self.itemClass = box.cls.item()
				#	position = box.xywh
			if len(classes) == 0:# 如果没有检测到物体
				break
			else:# 检测到物体
				self.itemClass = classes[0]
				position = positions[0]
				sendbyte = 0
				if self.itemClass == 'harmful':
					sendbyte = 1
				elif self.itemClass == 'recycle':
					sendbyte = 3
				elif self.itemClass == 'kitchen':
					sendbyte = 2
				elif self.itemClass == 'others':
					sendbyte = 4
				pos_x = int(position[0][0])
				pos_y = int(position[0][1])
				mes = f"{pos_x:03d}" + f"{pos_y:03d}" + f"{sendbyte}"
				self.ser.write(b"5" + bytes(mes, encoding = "ascii") + b"\n")
		if len(classes) == 0:# 没有检测到物体的处理
			self.ser.write(b"9")
		self.total = 0

	def serial_receive(self):
		while True:
			if self.ser.in_waiting > 0:
				data = self.ser.readline().decode('utf-8').strip()
				if data == "Start":
					self.cap = cv.VideoCapture(0)
					if not self.cap.isOpened():
						print("错误：无法访问摄像头")
						exit()
					ret, frame = self.cap.read()
					if not ret:
						print("错误：无法获取画面")
						exit()
					self.counter += 1
					self.test_send(frame)
					self.cap.release()
				if data == "Check":
					self.cap = cv.VideoCapture(0)
					if not self.cap.isOpened():
						print("错误：无法访问摄像头")
						exit()
					ret, frame = self.cap.read()
					if not ret:
						print("错误：无法获取画面")
						exit()
					self.counter += 1
					self.check(frame)
					self.cap.release()
				if data == "One":
					self.one = 1
				if data == "Two":
					self.two = 1
				if data == "Three":
					self.three = 1
				if data == "Four":
					self.four = 1
				if data == "Oempty":
					self.one = 0
				if data == "Tempty":
					self.two = 0
				if data == "Rempty":
					self.three = 0
				if data == "Fempty":
					self.four = 0
				self.is_full.emit(self.one, self.two, self.three, self.four)
	def trash_dict(self):
		return {
			'battery': 'harmful',
			'drug': 'harmful',
			'plastic': 'recycle',
			'metal': 'recycle',
			'potato': 'kitchen',
			'carrot': 'kitchen',
			'daikon': 'kitchen',
			'brick': 'others',
			'cobblestone': 'others',
			'cup': 'recycle',
			'porcelain': 'others',
		}

	@Slot()
	def condense(self):
		self.ser.write(b"7")

	@Slot()
	def checkFull(self):
		self.ser.write(b"8")

	@Slot()
	def unlock(self):
		self.ser.write(b"6")

if __name__ == "__main__":
	#qml模块初始化
	app = QGuiApplication()
	view = QQmlApplicationEngine()

	image_provider = VideoFrameProvider()
	view.addImageProvider("videoFrameProvider", image_provider)

	test = TestSystem(image_provider)
	view.rootContext().setContextProperty("videoCapture", test)

	qml_file =  "qml/main.qml"
	view.load(qml_file)
	sys.exit(app.exec())

