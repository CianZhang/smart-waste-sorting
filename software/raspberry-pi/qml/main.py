import sys
from PySide6.QtGui import QGuiApplication,QImage,QPixmap
from PySide6.QtQuick import QQuickImageProvider
from PySide6.QtWidgets import QWidget,QLabel
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import QThread,Slot,Signal,QObject

if __name__ == "__main__":
    app = QGuiApplication()
    view = QQmlApplicationEngine()
    
    qml_file =  "main.qml"
    view.load(qml_file)
    sys.exit(app.exec())
