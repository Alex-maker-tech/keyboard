from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice
# import sys
from time import sleep
from math import ceil

name_of_file = "program file.txt"
name_of_file_2 = "program file 2.txt"

# Инициализация графической части программы (графического интерфейса)
app = QtWidgets.QApplication([])
ui = uic.loadUi("main_design.ui")
ui.setWindowTitle("Keyboard Customizer")

# Работа с COM-портами: инициализация объекта COM-порта и выбор скорости; Добавление доступных COM-портов в графический интерфейс (точнее - в comboBox)
serial = QSerialPort()
serial.setBaudRate(115200)
portList = []
ports = QSerialPortInfo().availablePorts()
for port in ports:
	portList.append(port.portName())
ui.combo_box_ports.addItems(portList)

# Заполнение списка list_of_keys названиями служебных клавиш, арабскими цифрами, буквами латинского алфавита
list_of_keys = ["Select a key...", "L_Ctrl", "L_Shift", "L_Alt", "R_Ctrl", "R_Shift", "R_Alt", "CapsLock", "Win", "Tab", "Escape",
				"Delete", "Backspace", "Insert", "Home", "End", "PageUp", "PageDown", "Left_Arrow", "Right_Arrow", "Up_Arrow", "Down_Arrow"]
list_of_keys += [str("F" + str(val + 1)) for val in range(12)]
list_of_keys += [str(i) for i in range(10)]
list_of_keys += [str(" " + chr(i)) for i in range(65, 91)]

# Список из всех comboBox'ов
comboBoxes = [ui.comboBox,    ui.comboBox_2,  ui.comboBox_3,  ui.comboBox_4,
			  ui.comboBox_5,  ui.comboBox_6,  ui.comboBox_7,  ui.comboBox_8,
			  ui.comboBox_9,  ui.comboBox_10, ui.comboBox_11, ui.comboBox_12,
			  ui.comboBox_13, ui.comboBox_14, ui.comboBox_15, ui.comboBox_16,
			  ui.comboBox_17, ui.comboBox_18, ui.comboBox_19, ui.comboBox_20,
			  ui.comboBox_21, ui.comboBox_22, ui.comboBox_23, ui.comboBox_24,
			  ui.comboBox_25, ui.comboBox_26, ui.comboBox_27, ui.comboBox_28,
			  ui.comboBox_29, ui.comboBox_30, ui.comboBox_31, ui.comboBox_32,
			  ui.comboBox_33, ui.comboBox_34, ui.comboBox_35, ui.comboBox_36,
			  ui.comboBox_37, ui.comboBox_38, ui.comboBox_39, ui.comboBox_40,
			  ui.comboBox_41, ui.comboBox_42, ui.comboBox_43, ui.comboBox_44,
			  ui.comboBox_45, ui.comboBox_46, ui.comboBox_47, ui.comboBox_48,

			  ui.comboBox_49, ui.comboBox_50, ui.comboBox_51, ui.comboBox_52,
			  ui.comboBox_53, ui.comboBox_54, ui.comboBox_55, ui.comboBox_56,
			  ui.comboBox_57, ui.comboBox_58, ui.comboBox_59, ui.comboBox_60,
			  ui.comboBox_61, ui.comboBox_62, ui.comboBox_63, ui.comboBox_64,
			  ui.comboBox_65, ui.comboBox_66, ui.comboBox_67, ui.comboBox_68,
			  ui.comboBox_69, ui.comboBox_70, ui.comboBox_71, ui.comboBox_72,
			  ui.comboBox_73, ui.comboBox_74, ui.comboBox_75, ui.comboBox_76,
			  ui.comboBox_77, ui.comboBox_78, ui.comboBox_79, ui.comboBox_80,
			  ui.comboBox_81, ui.comboBox_82, ui.comboBox_83, ui.comboBox_84,
			  ui.comboBox_85, ui.comboBox_86, ui.comboBox_87, ui.comboBox_88,
			  ui.comboBox_89, ui.comboBox_90, ui.comboBox_91, ui.comboBox_92,
			  ui.comboBox_93, ui.comboBox_94, ui.comboBox_95, ui.comboBox_96,

			  ui.comboBox_97, ui.comboBox_98, ui.comboBox_99, ui.comboBox_100,
			  ui.comboBox_101, ui.comboBox_102, ui.comboBox_103, ui.comboBox_104,
			  ui.comboBox_105, ui.comboBox_106, ui.comboBox_107, ui.comboBox_108,
			  ui.comboBox_109, ui.comboBox_110, ui.comboBox_111, ui.comboBox_112,
			  ui.comboBox_113, ui.comboBox_114, ui.comboBox_115, ui.comboBox_116,
			  ui.comboBox_117, ui.comboBox_118, ui.comboBox_119, ui.comboBox_120,
			  ui.comboBox_121, ui.comboBox_122, ui.comboBox_123, ui.comboBox_124,
			  ui.comboBox_125, ui.comboBox_126, ui.comboBox_127, ui.comboBox_128,
			  ui.comboBox_129, ui.comboBox_130, ui.comboBox_131, ui.comboBox_132,
			  ui.comboBox_133, ui.comboBox_134, ui.comboBox_135, ui.comboBox_136,
			  ui.comboBox_137, ui.comboBox_138, ui.comboBox_139, ui.comboBox_140,
			  ui.comboBox_141, ui.comboBox_142, ui.comboBox_143, ui.comboBox_144 ]

# Заполнение всех comboBox'ов значениями из list_of_keys
for i in range(len(comboBoxes)):
	comboBoxes[i].addItems(list_of_keys)

# Функция открытия выбранного COM-порта
def open_port():
	serial.setPortName(ui.combo_box_ports.currentText())
	serial.open(QIODevice.ReadWrite)


# Функция закрытия выбранного COM-порта
def close_port():
	serial.close()


# Функция изменения названия вкладки №1
def ch_name_layer1():
	ui.tabWidget.setTabText(0, ui.line_edit_l1.text())


# Функция изменения названия вкладки №2
def ch_name_layer2():
	ui.tabWidget.setTabText(1, ui.line_edit_l2.text())


# Функция изменения названия вкладки №3
def ch_name_layer3():
	ui.tabWidget.setTabText(2, ui.line_edit_l3.text())


# Создание словаря (массива ключ-значение) и наполнение значениями
dict_of_keys = {"L_Ctrl": 0x80, "R_Ctrl": 0x84, "L_Shift": 0x81, "R_Shift": 0x85,  "L_Alt": 0x82, "R_Alt": 0x86, "CapsLock": 0xC1, "Win": 0x83,  "Tab": 0xB3,
				"Escape": 0xB1, "Delete": 0xD4, "Backspace": 0xB2, "Insert": 0xD1, "Home": 0xD2, "End": 0xD5, "PageUp": 0xD3, "PageDown": 0xD6,  "Select a key...": 0x00,
				"Left_Arrow": 0xD8, "Right_Arrow": 0xD7,  "Up_Arrow": 0xDA, "Down_Arrow": 0xD9, "F1": 0xC2, "F2": 0xC3,  "F3": 0xC4,  "F4": 0xC5, "F5": 0xC6, "F6": 0xC7,
				"F7": 0xC8,  "F8": 0xC9, "F9": 0xCA, "F10": 0xCB, "F11": 0xCC, "F12": 0xCD}
for i in range(65, 91):
	dict_of_keys[str(" " + chr(i))] = i + 32
for i in range(10):
	dict_of_keys[str(i)] = ord(str(i))
for i in range(65, 69):
	dict_of_keys[str(chr(i))] = i
dict_of_keys['*'] = ord('*')
dict_of_keys['#'] = ord('#')


# Функция преобразования значений по ранее созданному словарю
def convert_data(data):
	for i in range(len(data)):
		data[i] = dict_of_keys[str(data[i])]
	return data


def save_data():
	global name_of_file
	global name_of_file_2
	memory_file = open(name_of_file, 'r+')
	mem_file = open(name_of_file_2, 'r+')
	progress = 0
	data = []
	symbols = [ '1', '2', '3', 'A', 
				'4', '5', '6', 'B', 
				'7', '8', '9', 'C', 
				'*', '0', '#', 'D' ]

	for i in range(3, 48, 3):
		temp = []
		if i < 16:
			temp.append(1)
		elif i > 15 and i < 32:
			temp.append(2)
		elif i > 31:
			temp.append(3)
		
		temp.append(symbols[i % 16])
		temp.append(comboBoxes[i - 3].currentText())
		temp.append(comboBoxes[i - 2].currentText())
		temp.append(comboBoxes[i - 1].currentText())

		data.append(temp)
	
	for i in range(48):
		out_str = ""
		# for j in range(2, 5):
		#     data[i][j] = dict_of_keys[str(data[i][j])]

		for k in range(5):
			out_str += str(data[i][k])
			out_str += ','

		out_str = out_str[:-1] + ';\n'
		# print(out_str, end='');
		memory_file.write(out_str); sleep(0.1); progress += 2.083; ui.progress_of_send.setValue(ceil(progress))
	# print("\n\n")
	mem_file.write("n1,"+str(ui.tabWidget.tabText(0))+";\n")
	mem_file.write("n2,"+str(ui.tabWidget.tabText(1))+";\n")
	mem_file.write("n3,"+str(ui.tabWidget.tabText(2))+";\n")

	mem_file.close(); memory_file.close()


def send_data_file(data_out, mode):
	memory_file = open(name_of_file, "w+")
	out_str = ""
	if mode == 0:
		for i in range(len(data_out)):
			data_out[i] = dict_of_keys[str(data_out[i])]

	for value in data_out:
		out_str += str(value)
		out_str += ','

	out_str = out_str[:-1] + ';'
	# print(out_str)
	memory_file.write(out_str.encode())


def caller_of_send_data():
	progress = 0
	data = [[1, 1,   ui.comboBox.currentText(),     ui.comboBox_2.currentText(),   ui.comboBox_3.currentText()],
			[1, 2,   ui.comboBox_4.currentText(),   ui.comboBox_5.currentText(),   ui.comboBox_6.currentText()],
			[1, 3,   ui.comboBox_7.currentText(),   ui.comboBox_8.currentText(),   ui.comboBox_9.currentText()],
			[1, 'A', ui.comboBox_10.currentText(),  ui.comboBox_11.currentText(),  ui.comboBox_12.currentText()],
			[1, 4,   ui.comboBox_13.currentText(),  ui.comboBox_14.currentText(),  ui.comboBox_15.currentText()],
			[1, 5,   ui.comboBox_16.currentText(),  ui.comboBox_17.currentText(),  ui.comboBox_18.currentText()],
			[1, 6,   ui.comboBox_19.currentText(),  ui.comboBox_20.currentText(),  ui.comboBox_21.currentText()],
			[1, 'B', ui.comboBox_22.currentText(),  ui.comboBox_23.currentText(),  ui.comboBox_24.currentText()],
			[1, 7,   ui.comboBox_25.currentText(),  ui.comboBox_26.currentText(),  ui.comboBox_27.currentText()],
			[1, 8,   ui.comboBox_28.currentText(),  ui.comboBox_29.currentText(),  ui.comboBox_30.currentText()],
			[1, 9,   ui.comboBox_31.currentText(),  ui.comboBox_32.currentText(),  ui.comboBox_33.currentText()],
			[1, 'C', ui.comboBox_34.currentText(),  ui.comboBox_35.currentText(),  ui.comboBox_36.currentText()],
			[1, '*', ui.comboBox_37.currentText(),  ui.comboBox_38.currentText(),  ui.comboBox_39.currentText()],
			[1, 0,   ui.comboBox_40.currentText(),  ui.comboBox_41.currentText(),  ui.comboBox_42.currentText()],
			[1, '#', ui.comboBox_43.currentText(),  ui.comboBox_44.currentText(),  ui.comboBox_45.currentText()],
			[1, 'D', ui.comboBox_46.currentText(),  ui.comboBox_47.currentText(),  ui.comboBox_48.currentText()],

			[2, 1,   ui.comboBox_49.currentText(),  ui.comboBox_50.currentText(),  ui.comboBox_51.currentText()],
			[2, 2,   ui.comboBox_52.currentText(),  ui.comboBox_53.currentText(),  ui.comboBox_54.currentText()],
			[2, 3,   ui.comboBox_55.currentText(),  ui.comboBox_56.currentText(),  ui.comboBox_57.currentText()],
			[2, 'A', ui.comboBox_58.currentText(),  ui.comboBox_59.currentText(),  ui.comboBox_60.currentText()],
			[2, 4,   ui.comboBox_61.currentText(),  ui.comboBox_62.currentText(),  ui.comboBox_63.currentText()],
			[2, 5,   ui.comboBox_64.currentText(),  ui.comboBox_65.currentText(),  ui.comboBox_66.currentText()],
			[2, 6,   ui.comboBox_67.currentText(),  ui.comboBox_68.currentText(),  ui.comboBox_69.currentText()],
			[2, 'B', ui.comboBox_70.currentText(),  ui.comboBox_71.currentText(),  ui.comboBox_72.currentText()],
			[2, 7,   ui.comboBox_73.currentText(),  ui.comboBox_74.currentText(),  ui.comboBox_75.currentText()],
			[2, 8,   ui.comboBox_76.currentText(),  ui.comboBox_77.currentText(),  ui.comboBox_78.currentText()],
			[2, 9,   ui.comboBox_79.currentText(),  ui.comboBox_80.currentText(),  ui.comboBox_81.currentText()],
			[2, 'C', ui.comboBox_82.currentText(),  ui.comboBox_83.currentText(),  ui.comboBox_84.currentText()],
			[2, '*', ui.comboBox_85.currentText(),  ui.comboBox_86.currentText(),  ui.comboBox_87.currentText()],
			[2, 0,   ui.comboBox_88.currentText(),  ui.comboBox_89.currentText(),  ui.comboBox_90.currentText()],
			[2, '#', ui.comboBox_91.currentText(),  ui.comboBox_92.currentText(),  ui.comboBox_93.currentText()],
			[2, 'D', ui.comboBox_94.currentText(),  ui.comboBox_95.currentText(),  ui.comboBox_96.currentText()],

			[3, 1,   ui.comboBox_97.currentText(),  ui.comboBox_98.currentText(),  ui.comboBox_99.currentText()],
			[3, 2,   ui.comboBox_100.currentText(), ui.comboBox_101.currentText(), ui.comboBox_102.currentText()],
			[3, 3,   ui.comboBox_103.currentText(), ui.comboBox_104.currentText(), ui.comboBox_105.currentText()],
			[3, 'A', ui.comboBox_106.currentText(), ui.comboBox_107.currentText(), ui.comboBox_108.currentText()],
			[3, 4,   ui.comboBox_109.currentText(), ui.comboBox_110.currentText(), ui.comboBox_111.currentText()],
			[3, 5,   ui.comboBox_112.currentText(), ui.comboBox_113.currentText(), ui.comboBox_114.currentText()],
			[3, 6,   ui.comboBox_115.currentText(), ui.comboBox_116.currentText(), ui.comboBox_117.currentText()],
			[3, 'B', ui.comboBox_118.currentText(), ui.comboBox_119.currentText(), ui.comboBox_120.currentText()],
			[3, 7,   ui.comboBox_121.currentText(), ui.comboBox_122.currentText(), ui.comboBox_123.currentText()],
			[3, 8,   ui.comboBox_124.currentText(), ui.comboBox_125.currentText(), ui.comboBox_126.currentText()],
			[3, 9,   ui.comboBox_127.currentText(), ui.comboBox_128.currentText(), ui.comboBox_129.currentText()],
			[3, 'C', ui.comboBox_130.currentText(), ui.comboBox_131.currentText(), ui.comboBox_132.currentText()],
			[3, '*', ui.comboBox_133.currentText(), ui.comboBox_134.currentText(), ui.comboBox_135.currentText()],
			[3, 0,   ui.comboBox_136.currentText(), ui.comboBox_137.currentText(), ui.comboBox_138.currentText()],
			[3, '#', ui.comboBox_139.currentText(), ui.comboBox_140.currentText(), ui.comboBox_141.currentText()],
			[3, 'D', ui.comboBox_142.currentText(), ui.comboBox_143.currentText(), ui.comboBox_144.currentText()]]

	for i in range(48):
		send_data_serial(data[i], 0); sleep(0.1); progress += 2.083;  ui.progress_of_send.setValue(ceil(progress))
	# print("\n\n")


# Функция одиночной отправки данных в выбранный COM-порт
def send_data_serial(data_out, mode):

	out_str = ""
	if mode == 0:
		for i in range(len(data_out)):
			data_out[i] = dict_of_keys[str(data_out[i])]
		for value in data_out:
			out_str += str(value)
			out_str += ','

	out_str = out_str[:-1] + ';'
	# print(out_str)
	serial.write(out_str.encode())


def load_data():
	global name_of_file
	global name_of_file_2
	memory_file = open(name_of_file, 'r')
	mem_file = open(name_of_file_2, 'r')
	progress = 0

	data2 = mem_file.readlines()
	for i in range(len(data2)):
		data2[i] = data2[i].split(',')
		data2[i][1] = data2[i][1].replace(";\n", "")
	ui.tabWidget.setTabText(0, data2[0][1]); ui.tabWidget.setTabText(1, data2[1][1]); ui.tabWidget.setTabText(2, data2[2][1])
	ui.line_edit_l1.setText(data2[0][1]);    ui.line_edit_l2.setText(data2[1][1]);    ui.line_edit_l3.setText(data2[2][1])

	data = memory_file.readlines()
	for i in range(len(data)):
		data[i] = data[i].split(',')
		data[i][4] = data[i][4].replace(";\n", "")

	# print(data)
	ui.comboBox.setCurrentText(data[0][2]); ui.comboBox_2.setCurrentText(data[0][3]); ui.comboBox_3.setCurrentText(data[0][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_4.setCurrentText(data[1][2]); ui.comboBox_5.setCurrentText(data[1][3]); ui.comboBox_6.setCurrentText(data[1][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_7.setCurrentText(data[2][2]); ui.comboBox_8.setCurrentText(data[2][3]); ui.comboBox_9.setCurrentText(data[2][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_10.setCurrentText(data[3][2]); ui.comboBox_11.setCurrentText(data[3][3]); ui.comboBox_12.setCurrentText(data[3][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_13.setCurrentText(data[4][2]); ui.comboBox_14.setCurrentText(data[4][3]); ui.comboBox_15.setCurrentText(data[4][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_16.setCurrentText(data[5][2]); ui.comboBox_17.setCurrentText(data[5][3]); ui.comboBox_18.setCurrentText(data[5][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_19.setCurrentText(data[6][2]); ui.comboBox_20.setCurrentText(data[6][3]); ui.comboBox_21.setCurrentText(data[6][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_22.setCurrentText(data[7][2]); ui.comboBox_23.setCurrentText(data[7][3]); ui.comboBox_24.setCurrentText(data[7][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_25.setCurrentText(data[8][2]); ui.comboBox_26.setCurrentText(data[8][3]); ui.comboBox_27.setCurrentText(data[8][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_28.setCurrentText(data[9][2]); ui.comboBox_29.setCurrentText(data[9][3]); ui.comboBox_30.setCurrentText(data[9][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_31.setCurrentText(data[10][2]); ui.comboBox_32.setCurrentText(data[10][3]); ui.comboBox_33.setCurrentText(data[10][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_34.setCurrentText(data[11][2]); ui.comboBox_35.setCurrentText(data[11][3]); ui.comboBox_36.setCurrentText(data[11][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_37.setCurrentText(data[12][2]); ui.comboBox_38.setCurrentText(data[12][3]); ui.comboBox_39.setCurrentText(data[12][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_40.setCurrentText(data[13][2]); ui.comboBox_41.setCurrentText(data[13][3]); ui.comboBox_42.setCurrentText(data[13][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_43.setCurrentText(data[14][2]); ui.comboBox_44.setCurrentText(data[14][3]); ui.comboBox_45.setCurrentText(data[14][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_46.setCurrentText(data[15][2]); ui.comboBox_47.setCurrentText(data[15][3]); ui.comboBox_48.setCurrentText(data[15][4]); progress += 2.083; display_progress(progress)

	ui.comboBox_49.setCurrentText(data[16][2]); ui.comboBox_50.setCurrentText(data[16][3]); ui.comboBox_51.setCurrentText(data[16][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_52.setCurrentText(data[17][2]); ui.comboBox_53.setCurrentText(data[17][3]); ui.comboBox_54.setCurrentText(data[17][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_55.setCurrentText(data[18][2]); ui.comboBox_56.setCurrentText(data[18][3]); ui.comboBox_57.setCurrentText(data[18][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_58.setCurrentText(data[19][2]); ui.comboBox_59.setCurrentText(data[19][3]); ui.comboBox_60.setCurrentText(data[19][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_61.setCurrentText(data[20][2]); ui.comboBox_62.setCurrentText(data[20][3]); ui.comboBox_63.setCurrentText(data[20][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_64.setCurrentText(data[21][2]); ui.comboBox_65.setCurrentText(data[21][3]); ui.comboBox_66.setCurrentText(data[21][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_67.setCurrentText(data[22][2]); ui.comboBox_68.setCurrentText(data[22][3]); ui.comboBox_69.setCurrentText(data[22][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_70.setCurrentText(data[23][2]); ui.comboBox_71.setCurrentText(data[23][3]); ui.comboBox_72.setCurrentText(data[23][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_73.setCurrentText(data[24][2]); ui.comboBox_74.setCurrentText(data[24][3]); ui.comboBox_75.setCurrentText(data[24][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_76.setCurrentText(data[25][2]); ui.comboBox_77.setCurrentText(data[25][3]); ui.comboBox_78.setCurrentText(data[25][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_79.setCurrentText(data[26][2]); ui.comboBox_80.setCurrentText(data[26][3]); ui.comboBox_81.setCurrentText(data[26][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_82.setCurrentText(data[27][2]); ui.comboBox_83.setCurrentText(data[27][3]); ui.comboBox_84.setCurrentText(data[27][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_85.setCurrentText(data[28][2]); ui.comboBox_86.setCurrentText(data[28][3]); ui.comboBox_87.setCurrentText(data[28][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_88.setCurrentText(data[29][2]); ui.comboBox_89.setCurrentText(data[29][3]); ui.comboBox_90.setCurrentText(data[29][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_91.setCurrentText(data[30][2]); ui.comboBox_92.setCurrentText(data[30][3]); ui.comboBox_93.setCurrentText(data[30][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_94.setCurrentText(data[31][2]); ui.comboBox_95.setCurrentText(data[31][3]); ui.comboBox_96.setCurrentText(data[31][4]); progress += 2.083; display_progress(progress)

	ui.comboBox_97.setCurrentText(data[32][2]); ui.comboBox_98.setCurrentText(data[32][3]); ui.comboBox_99.setCurrentText(data[32][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_100.setCurrentText(data[33][2]); ui.comboBox_101.setCurrentText(data[33][3]); ui.comboBox_102.setCurrentText(data[33][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_103.setCurrentText(data[34][2]); ui.comboBox_104.setCurrentText(data[34][3]); ui.comboBox_105.setCurrentText(data[34][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_106.setCurrentText(data[35][2]); ui.comboBox_107.setCurrentText(data[35][3]); ui.comboBox_108.setCurrentText(data[35][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_109.setCurrentText(data[36][2]); ui.comboBox_110.setCurrentText(data[36][3]); ui.comboBox_111.setCurrentText(data[36][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_112.setCurrentText(data[37][2]); ui.comboBox_113.setCurrentText(data[37][3]); ui.comboBox_114.setCurrentText(data[37][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_115.setCurrentText(data[38][2]); ui.comboBox_116.setCurrentText(data[38][3]); ui.comboBox_117.setCurrentText(data[38][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_118.setCurrentText(data[39][2]); ui.comboBox_119.setCurrentText(data[39][3]); ui.comboBox_120.setCurrentText(data[39][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_121.setCurrentText(data[40][2]); ui.comboBox_122.setCurrentText(data[40][3]); ui.comboBox_123.setCurrentText(data[40][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_124.setCurrentText(data[41][2]); ui.comboBox_125.setCurrentText(data[41][3]); ui.comboBox_126.setCurrentText(data[41][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_127.setCurrentText(data[42][2]); ui.comboBox_128.setCurrentText(data[42][3]); ui.comboBox_129.setCurrentText(data[42][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_130.setCurrentText(data[43][2]); ui.comboBox_131.setCurrentText(data[43][3]); ui.comboBox_132.setCurrentText(data[43][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_133.setCurrentText(data[44][2]); ui.comboBox_134.setCurrentText(data[44][3]); ui.comboBox_135.setCurrentText(data[44][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_136.setCurrentText(data[45][2]); ui.comboBox_137.setCurrentText(data[45][3]); ui.comboBox_138.setCurrentText(data[45][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_139.setCurrentText(data[46][2]); ui.comboBox_140.setCurrentText(data[46][3]); ui.comboBox_141.setCurrentText(data[46][4]); progress += 2.083; display_progress(progress)
	ui.comboBox_142.setCurrentText(data[47][2]); ui.comboBox_143.setCurrentText(data[47][3]); ui.comboBox_144.setCurrentText(data[47][4]); progress += 2.083; display_progress(progress)

	mem_file.close(); memory_file.close()


def display_progress(progress):
	sleep(0.05); ui.progress_of_send.setValue(ceil(progress))


def open_info_window():
	window = QtWidgets.QMessageBox()
	window.setText('''It's an app that can help you to configure your additional keyboard.\n\nFor use this app you must follow manual. Firstly, select a port in Serial Box and press "Open" Button.''')
	window.setWindowTitle("Information about app")
	window.exec_()


# Присвоение к определенному действию определенной функции, которая будет вызываться при совершении этого действия
ui.button_open.clicked.connect(open_port)
ui.button_close.clicked.connect(close_port)

ui.button_name_l1.clicked.connect(ch_name_layer1)
ui.button_name_l1_2.clicked.connect(ch_name_layer2)
ui.button_name_l1_3.clicked.connect(ch_name_layer3)

ui.button_load.clicked.connect(load_data)
ui.button_save.clicked.connect(save_data)
ui.button_send.clicked.connect(caller_of_send_data)
ui.button_info.clicked.connect(open_info_window)

# Отображение графического интерфейса и основной цикл программы
ui.show()
app.exec()
