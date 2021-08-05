from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice

from random import *

app = QtWidgets.QApplication([])
ui = uic.loadUi("test_design.ui")
ui.setWindowTitle("Serial Test")

serial = QSerialPort()
serial.setBaudRate(115200)
portList = []
ports = QSerialPortInfo().availablePorts()
for port in ports:
    portList.append(port.portName())
ui.port_names.addItems(portList)


def on_open():
    serial.setPortName(ui.port_names.currentText())
    serial.open(QIODevice.ReadWrite)


def serial_send_data(data_out):
    out_str = ""
    for value in data_out:
        out_str += str(value)
        out_str += ','
    out_str = out_str[:-1]
    out_str += ';'
    serial.write(out_str.encode())


def on_close():
    serial.close()


serial.readyRead.connect(serial_send_data([0, ui.slider.value(), randint(0, 255)]))
ui.button_open_serial.clicked.connect(on_open)
ui.button_close_serial.clicked.connect(on_close)

ui.show()
app.exec()
