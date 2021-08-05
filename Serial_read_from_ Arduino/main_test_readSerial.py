from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice

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


def on_read():
    if not serial.canReadLine():
        return
    rx = serial.readLine()
    data_out = str(rx, 'utf-8').strip().split(',')
    if data_out[0] == '0':
        ui.line_edit.setText(data_out[1])
    else:
        ui.line_edit.setText('Nothing!')


def on_close():
    serial.close()


serial.readyRead.connect(on_read)
ui.button_open_serial.clicked.connect(on_open)
ui.button_close_serial.clicked.connect(on_close)

ui.show()
app.exec()
