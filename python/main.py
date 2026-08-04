#!/usr/bin/env python3
import sys
from PySide6.QtWidgets import *
from PySide6.QtCore import Qt
from PySide6.QtGui import QFont, QIntValidator, QRegularExpressionValidator
from PySide6.QtCore import QRegularExpression

from sequence_wrapper import MutableArraySequence, ImmutableArraySequence, MutableListSequence, BitSequence, VectorInt

MAX_INDEX=9999

class SequenceEditor(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Редактор последовательности")
        self.resize(400, 300)
        
        self.seq = MutableArraySequence()
        
        layout = QVBoxLayout(self)
        
        self.display = QTextEdit()
        self.display.setReadOnly(True)
        self.display.setFont(QFont("Courier", 11))
        layout.addWidget(self.display)
        
        input_layout = QHBoxLayout()
        self.value_edit = QLineEdit()
        self.value_edit.setPlaceholderText("Значение")
        self.value_edit.setValidator(QIntValidator())
        self.index_spin = QSpinBox()
        self.index_spin.setRange(0, MAX_INDEX)
        btn_append = QPushButton("Append")
        btn_clear = QPushButton("Clear")
        input_layout.addWidget(self.value_edit)
        input_layout.addWidget(self.index_spin)
        input_layout.addWidget(btn_append)
        input_layout.addWidget(btn_clear)
        layout.addLayout(input_layout)
        
        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Cancel)
        layout.addWidget(buttons)
        
        btn_append.clicked.connect(self._on_append)
        btn_clear.clicked.connect(self._on_clear)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        
        self._update_display()
    
    def _on_append(self):
        if self.value_edit.text():
            val = int(self.value_edit.text())
            self.seq.append(val)
            self.value_edit.clear()
            self._update_display()
    
    def _on_clear(self):
        self.seq = MutableArraySequence()
        self._update_display()
    
    def _update_display(self):
        text = "[ "
        for i in range(self.seq.get_length()):
            text += str(self.seq.get(i))
            if i + 1 < self.seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.seq.get_length()}"
        self.display.setText(text)
    
    def get_sequence(self):
        return self.seq


class BitSequenceEditor(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Редактор BitSequence")
        self.resize(400, 300)
        
        self.seq = BitSequence()
        
        layout = QVBoxLayout(self)
        
        self.display = QTextEdit()
        self.display.setReadOnly(True)
        self.display.setFont(QFont("Courier", 11))
        layout.addWidget(self.display)
        
        input_layout = QHBoxLayout()
        self.bit_edit = QLineEdit()
        self.bit_edit.setPlaceholderText("Бит (0/1)")
        self.bit_edit.setValidator(QRegularExpressionValidator(QRegularExpression("[01]")))
        self.index_spin = QSpinBox()
        self.index_spin.setRange(0, MAX_INDEX)
        btn_append = QPushButton("Append")
        btn_clear = QPushButton("Clear")
        input_layout.addWidget(self.bit_edit)
        input_layout.addWidget(self.index_spin)
        input_layout.addWidget(btn_append)
        input_layout.addWidget(btn_clear)
        layout.addLayout(input_layout)
        
        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Cancel)
        layout.addWidget(buttons)
        
        btn_append.clicked.connect(self._on_append)
        btn_clear.clicked.connect(self._on_clear)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        
        self._update_display()
    
    def _on_append(self):
        if self.bit_edit.text():
            val = int(self.bit_edit.text())
            self.seq.append(val)
            self.bit_edit.clear()
            self._update_display()
    
    def _on_clear(self):
        self.seq = BitSequence()
        self._update_display()
    
    def _update_display(self):
        text = "[ "
        for i in range(self.seq.get_length()):
            text += "1" if self.seq.get(i) else "0"
            if i + 1 < self.seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.seq.get_length()}"
        self.display.setText(text)
    
    def get_sequence(self):
        return self.seq


class SequenceTester(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Sequence Tester")
        self.resize(1920, 1080)
        
        self.mutable_array_seq = MutableArraySequence()
        self.immutable_array_seq = ImmutableArraySequence()
        self.mutable_list_seq = MutableListSequence()
        self.bit_seq = BitSequence()
        self.v_seq = VectorInt()
        self.v_second_seq = VectorInt()
        
        self._setup_ui()
        self._update_mutable_array_display()
        self._update_immutable_array_display()
        self._update_mutable_list_display()
        self._update_bit_display()
        self._update_vector_display()

    
    def _setup_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
                
        self.tabs = QTabWidget()
        layout.addWidget(self.tabs)
        
        self._setup_mutable_array_tab()
        self._setup_immutable_array_tab()
        self._setup_mutable_list_tab()
        self._setup_bit_tab()
        self._setup_vector_tab()
        
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        self.status_bar.showMessage("Готов")
    
    def _show_status(self, msg, error=False):
        prefix = "❌ " if error else "️✅ "
        self.status_bar.showMessage(prefix + msg, 3000)
    
    def _show_message(self, title, msg):
        QMessageBox.information(self, title, msg)
    
    def _get_second_int_sequence(self):
        dialog = SequenceEditor(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            return dialog.get_sequence()
        return None
    
    def _get_second_bit_sequence(self):
        dialog = BitSequenceEditor(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            return dialog.get_sequence()
        return None
    
    def _setup_mutable_array_tab(self):
        tab = QWidget()
        self.tabs.addTab(tab, "MutableArraySequence")
        layout = QVBoxLayout(tab)
        
        self.ma_display = QTextEdit()
        self.ma_display.setReadOnly(True)
        self.ma_display.setFont(QFont("Courier", 11))
        layout.addWidget(self.ma_display)
        
        input_layout = QHBoxLayout()
        input_layout.addWidget(QLabel("Значение:"))
        self.ma_value_edit = QLineEdit()
        self.ma_value_edit.setPlaceholderText("0")
        self.ma_value_edit.setValidator(QIntValidator())
        input_layout.addWidget(self.ma_value_edit)
        
        input_layout.addWidget(QLabel("Индекс:"))
        self.ma_index_spin = QSpinBox()
        self.ma_index_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.ma_index_spin)
        
        input_layout.addWidget(QLabel("Начало:"))
        self.ma_start_spin = QSpinBox()
        self.ma_start_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.ma_start_spin)
        
        input_layout.addWidget(QLabel("Конец:"))
        self.ma_end_spin = QSpinBox()
        self.ma_end_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.ma_end_spin)
        layout.addLayout(input_layout)
        
        grid = QGridLayout()
        btns = [
            ("Append", self._ma_append),
            ("Prepend", self._ma_prepend),
            ("InsertAt", self._ma_insert),
            ("Get", self._ma_get),
            ("GetFirst", self._ma_get_first),
            ("GetLast", self._ma_get_last),
            ("GetSubsequence", self._ma_get_subseq),
            ("Concat", self._ma_concat),
            ("Clear", self._ma_clear),
            ("Map", self._ma_map),
            ("Reduce", self._ma_reduce)
        ]
        for i, (text, slot) in enumerate(btns):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            grid.addWidget(btn, i // 4, i % 4)
        layout.addLayout(grid)
    
    def _update_mutable_array_display(self):
        text = "[ "
        for i in range(self.mutable_array_seq.get_length()):
            text += str(self.mutable_array_seq.get(i))
            if i + 1 < self.mutable_array_seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.mutable_array_seq.get_length()}"
        self.ma_display.setText(text)
    
    def _ma_append(self):
        if not self.ma_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ma_value_edit.text())
        self.mutable_array_seq.append(val)
        self.ma_value_edit.clear()
        self._update_mutable_array_display()
        self._show_status(f"Append({val}) выполнен")
    
    def _ma_prepend(self):
        if not self.ma_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ma_value_edit.text())
        self.mutable_array_seq.prepend(val)
        self.ma_value_edit.clear()
        self._update_mutable_array_display()
        self._show_status(f"Prepend({val}) выполнен")
    
    def _ma_insert(self):
        if not self.ma_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ma_value_edit.text())
        idx = self.ma_index_spin.value()
        try:
            self.mutable_array_seq.insert_at(idx, val)
            self.ma_value_edit.clear()
            self._update_mutable_array_display()
            self._show_status(f"InsertAt({idx}, {val}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_get(self):
        idx = self.ma_index_spin.value()
        try:
            val = self.mutable_array_seq.get(idx)
            self._show_message("Get", f"Значение по индексу {idx}: {val}")
            self._show_status(f"Get({idx}) = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_get_first(self):
        try:
            val = self.mutable_array_seq.get_first()
            self._show_message("GetFirst", f"Первый элемент: {val}")
            self._show_status(f"GetFirst() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_get_last(self):
        try:
            val = self.mutable_array_seq.get_last()
            self._show_message("GetLast", f"Последний элемент: {val}")
            self._show_status(f"GetLast() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_get_subseq(self):
        start = self.ma_start_spin.value()
        end = self.ma_end_spin.value()
        try:
            sub = self.mutable_array_seq.get_subsequence(start, end)
            text = "[ "
            for i in range(sub.get_length()):
                text += str(sub.get(i))
                if i + 1 < sub.get_length():
                    text += ", "
            text += " ]"
            self._show_message("GetSubsequence", f"Подпоследовательность [{start}, {end}]:\n{text}")
            self._show_status(f"GetSubsequence({start}, {end}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_concat(self):
        second = self._get_second_int_sequence()
        if second is None:
            return
        try:
            result = self.mutable_array_seq.concat(second)
            text = "[ "
            for i in range(result.get_length()):
                text += str(result.get(i))
                if i + 1 < result.get_length():
                    text += ", "
            text += " ]"
            self._show_message("Concat", f"Результат слияния:\n{text}")
            self._show_status("Concat выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ma_clear(self):
        self.mutable_array_seq = MutableArraySequence()
        self._update_mutable_array_display()
        self._show_status("Последовательность очищена")
    
    def _ma_map(self):
        pass
        
    def _ma_reduce(self):
        pass
    
    def _setup_immutable_array_tab(self):
        tab = QWidget()
        self.tabs.addTab(tab, "ImmutableArraySequence")
        layout = QVBoxLayout(tab)
        
        self.ia_display = QTextEdit()
        self.ia_display.setReadOnly(True)
        self.ia_display.setFont(QFont("Courier", 11))
        layout.addWidget(self.ia_display)
        
        input_layout = QHBoxLayout()
        
        input_layout.addWidget(QLabel("Значение:"))
        self.ia_value_edit = QLineEdit()
        self.ia_value_edit.setPlaceholderText("0")
        self.ia_value_edit.setValidator(QIntValidator())
        input_layout.addWidget(self.ia_value_edit)
        
        input_layout.addWidget(QLabel("Индекс:"))
        self.ia_index_spin = QSpinBox()
        self.ia_index_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.ia_index_spin)
        layout.addLayout(input_layout)
        
        grid = QGridLayout()
        btns = [
            ("Append (копия)", self._ia_append),
            ("Prepend (копия)", self._ia_prepend),
            ("InsertAt (копия)", self._ia_insert),
            ("Get", self._ia_get),
            ("GetFirst", self._ia_get_first),
            ("GetLast", self._ia_get_last),
            ("GetSubsequence", self._ia_get_subseq),
            ("Concat", self._ia_concat),
            ("Clear (новый объект)", self._ia_clear),
            ("Map", self._ia_map), 
            ("Reduce", self._ia_reduce)
        ]
        for i, (text, slot) in enumerate(btns):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            grid.addWidget(btn, i // 4, i % 4)
        layout.addLayout(grid)
    
    def _update_immutable_array_display(self):
        text = "[ "
        for i in range(self.immutable_array_seq.get_length()):
            text += str(self.immutable_array_seq.get(i))
            if i + 1 < self.immutable_array_seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.immutable_array_seq.get_length()}"
        self.ia_display.setText(text)
    
    def _ia_append(self):
        if not self.ia_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ia_value_edit.text())
        self.immutable_array_seq.append(val)
        self.ia_value_edit.clear()
        self._update_immutable_array_display()
        self._show_status(f"Append({val}) выполнен (создана копия)")
    
    def _ia_prepend(self):
        if not self.ia_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ia_value_edit.text())
        self.immutable_array_seq.prepend(val)
        self.ia_value_edit.clear()
        self._update_immutable_array_display()
        self._show_status(f"Prepend({val}) выполнен (создана копия)")
    
    def _ia_insert(self):
        if not self.ia_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ia_value_edit.text())
        idx = self.ia_index_spin.value()
        try:
            self.immutable_array_seq.insert_at(idx, val)
            self.ia_value_edit.clear()
            self._update_immutable_array_display()
            self._show_status(f"InsertAt({idx}, {val}) выполнен (создана копия)")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_get(self):
        idx = self.ia_index_spin.value()
        try:
            val = self.immutable_array_seq.get(idx)
            self._show_message("Get", f"Значение по индексу {idx}: {val}")
            self._show_status(f"Get({idx}) = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_get_first(self):
        try:
            val = self.immutable_array_seq.get_first()
            self._show_message("GetFirst", f"Первый элемент: {val}")
            self._show_status(f"GetFirst() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_get_last(self):
        try:
            val = self.immutable_array_seq.get_last()
            self._show_message("GetLast", f"Последний элемент: {val}")
            self._show_status(f"GetLast() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_get_subseq(self):
        start = self.ma_start_spin.value()
        end = self.ma_end_spin.value()
        try:
            sub = self.immutable_array_seq.get_subsequence(start, end)
            text = "[ "
            for i in range(sub.get_length()):
                text += str(sub.get(i))
                if i + 1 < sub.get_length():
                    text += ", "
            text += " ]"
            self._show_message("GetSubsequence", f"Подпоследовательность [{start}, {end}]:\n{text}")
            self._show_status(f"GetSubsequence({start}, {end}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_concat(self):
        second = self._get_second_int_sequence()
        if second is None:
            return
        imm_second = ImmutableArraySequence()
        for i in range(second.get_length()):
            imm_second.append(second.get(i))
        try:
            result = self.immutable_array_seq.concat(imm_second)
            text = "[ "
            for i in range(result.get_length()):
                text += str(result.get(i))
                if i + 1 < result.get_length():
                    text += ", "
            text += " ]"
            self._show_message("Concat", f"Результат слияния:\n{text}")
            self._show_status("Concat выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ia_clear(self):
        self.immutable_array_seq = ImmutableArraySequence()
        self._update_immutable_array_display()
        self._show_status("Создан новый пустой ImmutableArraySequence")
        
    def _ia_map(self):
        pass

    def _ia_reduce(self):
        pass
    
    def _setup_mutable_list_tab(self):
        tab = QWidget()
        self.tabs.addTab(tab, "MutableListSequence")
        layout = QVBoxLayout(tab)
        
        self.ml_display = QTextEdit()
        self.ml_display.setReadOnly(True)
        self.ml_display.setFont(QFont("Courier", 11))
        layout.addWidget(self.ml_display)
        
        input_layout = QHBoxLayout()
        input_layout.addWidget(QLabel("Значение:"))
        self.ml_value_edit = QLineEdit()
        self.ml_value_edit.setPlaceholderText("0")
        self.ml_value_edit.setValidator(QIntValidator())
        input_layout.addWidget(self.ml_value_edit)
        
        input_layout.addWidget(QLabel("Индекс:"))
        self.ml_index_spin = QSpinBox()
        self.ml_index_spin.setRange(0, MAX_INDEX)
        self.ml_index_spin.setValue(0)
        input_layout.addWidget(self.ml_index_spin)
        
        input_layout.addWidget(QLabel("Начало:"))
        self.ml_start_spin = QSpinBox()
        self.ml_start_spin.setRange(0, MAX_INDEX)
        self.ml_start_spin.setValue(0)
        input_layout.addWidget(self.ml_start_spin)
        
        input_layout.addWidget(QLabel("Конец:"))
        self.ml_end_spin = QSpinBox()
        self.ml_end_spin.setRange(0, MAX_INDEX)
        self.ml_end_spin.setValue(0)
        input_layout.addWidget(self.ml_end_spin)
        layout.addLayout(input_layout)
        
        grid = QGridLayout()
        btns = [
            ("Append", self._ml_append),
            ("Prepend", self._ml_prepend),
            ("InsertAt", self._ml_insert),
            ("Get", self._ml_get),
            ("GetFirst", self._ml_get_first),
            ("GetLast", self._ml_get_last),
            ("GetSubsequence", self._ml_get_subseq),
            ("Concat", self._ml_concat),
            ("Clear", self._ml_clear),
            ("Map", self._ml_map), 
            ("Reduce", self._ml_reduce)
        ]
        for i, (text, slot) in enumerate(btns):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            grid.addWidget(btn, i // 4, i % 4)
        layout.addLayout(grid)
    
    def _update_mutable_list_display(self):
        text = "[ "
        for i in range(self.mutable_list_seq.get_length()):
            text += str(self.mutable_list_seq.get(i))
            if i + 1 < self.mutable_list_seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.mutable_list_seq.get_length()}"
        self.ml_display.setText(text)
    
    def _ml_append(self):
        if not self.ml_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ml_value_edit.text())
        self.mutable_list_seq.append(val)
        self.ml_value_edit.clear()
        self._update_mutable_list_display()
        self._show_status(f"Append({val}) выполнен")
    
    def _ml_prepend(self):
        if not self.ml_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ml_value_edit.text())
        self.mutable_list_seq.prepend(val)
        self.ml_value_edit.clear()
        self._update_mutable_list_display()
        self._show_status(f"Prepend({val}) выполнен")
    
    def _ml_insert(self):
        if not self.ml_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.ml_value_edit.text())
        idx = self.ml_index_spin.value()
        try:
            self.mutable_list_seq.insert_at(idx, val)
            self.ml_value_edit.clear()
            self._update_mutable_list_display()
            self._show_status(f"InsertAt({idx}, {val}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_get(self):
        idx = self.ml_index_spin.value()
        try:
            val = self.mutable_list_seq.get(idx)
            self._show_message("Get", f"Значение по индексу {idx}: {val}")
            self._show_status(f"Get({idx}) = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_get_first(self):
        try:
            val = self.mutable_list_seq.get_first()
            self._show_message("GetFirst", f"Первый элемент: {val}")
            self._show_status(f"GetFirst() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_get_last(self):
        try:
            val = self.mutable_list_seq.get_last()
            self._show_message("GetLast", f"Последний элемент: {val}")
            self._show_status(f"GetLast() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_get_subseq(self):
        start = self.ml_start_spin.value()
        end = self.ml_end_spin.value()
        try:
            sub = self.mutable_list_seq.get_subsequence(start, end)
            text = "[ "
            for i in range(sub.get_length()):
                text += str(sub.get(i))
                if i + 1 < sub.get_length():
                    text += ", "
            text += " ]"
            self._show_message("GetSubsequence", f"Подпоследовательность [{start}, {end}]:\n{text}")
            self._show_status(f"GetSubsequence({start}, {end}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_concat(self):
        second = self._get_second_int_sequence()
        if second is None:
            return
        list_second = MutableListSequence()
        for i in range(second.get_length()):
            list_second.append(second.get(i))
        try:
            result = self.mutable_list_seq.concat(list_second)
            text = "[ "
            for i in range(result.get_length()):
                text += str(result.get(i))
                if i + 1 < result.get_length():
                    text += ", "
            text += " ]"
            self._show_message("Concat", f"Результат слияния:\n{text}")
            self._show_status("Concat выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _ml_clear(self):
        self.mutable_list_seq = MutableListSequence()
        self._update_mutable_list_display()
        self._show_status("Список очищен")
    
    def _ml_map(self):
        pass
        
    def _ml_reduce(self):
        pass
    
    def _setup_bit_tab(self):
        tab = QWidget()
        self.tabs.addTab(tab, "BitSequence")
        layout = QVBoxLayout(tab)
        
        self.bit_display = QTextEdit()
        self.bit_display.setReadOnly(True)
        self.bit_display.setFont(QFont("Courier", 11))
        layout.addWidget(self.bit_display)
        
        input_layout = QHBoxLayout()
        
        input_layout.addWidget(QLabel("Бит (0/1):"))
        self.bit_value_edit = QLineEdit()
        self.bit_value_edit.setPlaceholderText("0")
        self.bit_value_edit.setValidator(QRegularExpressionValidator(QRegularExpression("[01]")))
        input_layout.addWidget(self.bit_value_edit)
        
        input_layout.addWidget(QLabel("Индекс:"))
        self.bit_index_spin = QSpinBox()
        self.bit_index_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.bit_index_spin)
        
        input_layout.addWidget(QLabel("Начало:"))
        self.bit_start_spin = QSpinBox()
        self.bit_start_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.bit_start_spin)
        
        input_layout.addWidget(QLabel("Конец:"))
        self.bit_end_spin = QSpinBox()
        self.bit_end_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.bit_end_spin)
        layout.addLayout(input_layout)
        
        grid = QGridLayout()
        btns = [
            ("Append", self._bit_append),
            ("Prepend", self._bit_prepend),
            ("InsertAt", self._bit_insert),
            ("Get", self._bit_get),
            ("GetFirst", self._bit_get_first),
            ("GetLast", self._bit_get_last),
            ("GetSubsequence", self._bit_get_subseq),
            ("AND", self._bit_and),
            ("OR", self._bit_or),
            ("XOR", self._bit_xor),
            ("NOT", self._bit_not),
            ("Concat", self._bit_concat),
            ("Clear", self._bit_clear),
            ("Map", self._bit_map), 
            ("Reduce", self._bit_reduce)
        ]
        for i, (text, slot) in enumerate(btns):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            grid.addWidget(btn, i // 4, i % 4)
        layout.addLayout(grid)
    def _setup_vector_tab(self):
        tab = QWidget()
        self.tabs.addTab(tab, "Vector<int>")
        layout = QVBoxLayout(tab)
        
        self.v_display = QTextEdit()
        self.v_display.setReadOnly(True)
        self.v_display.setFont(QFont("Courier", 11))
        layout.addWidget(self.v_display)
        
        input_layout = QHBoxLayout()
        
        input_layout.addWidget(QLabel("Значение:"))
        self.v_value_edit = QLineEdit()
        self.v_value_edit.setPlaceholderText("0")
        self.v_value_edit.setValidator(QIntValidator())
        input_layout.addWidget(self.v_value_edit)
        
        input_layout.addWidget(QLabel("Индекс:"))
        self.v_index_spin = QSpinBox()
        self.v_index_spin.setRange(0, MAX_INDEX)
        input_layout.addWidget(self.v_index_spin)
        
        input_layout.addWidget(QLabel("Скаляр:"))
        self.v_scalar_edit = QLineEdit()
        self.v_scalar_edit.setPlaceholderText("2")
        self.v_scalar_edit.setValidator(QIntValidator())
        input_layout.addWidget(self.v_scalar_edit)
        
        layout.addLayout(input_layout)
        
        self.v_second_display = QTextEdit()
        self.v_second_display.setReadOnly(True)
        self.v_second_display.setFont(QFont("Courier", 11))
        self.v_second_display.setMaximumHeight(60)
        layout.addWidget(QLabel("Второй вектор:"))
        layout.addWidget(self.v_second_display)
        
        grid = QGridLayout()
        btns = [
            ("Get", self._v_get),
            ("Set", self._v_set),
            ("Clear", self._v_clear),
            ("+ (Add)", self._v_add),
            ("- (Sub)", self._v_sub),
            ("* (Scalar)", self._v_mul),
            ("Norm", self._v_norm),
            ("Dot Product", self._v_dot),
        ]
        for i, (text, slot) in enumerate(btns):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            grid.addWidget(btn, i // 4, i % 4)
        layout.addLayout(grid)
        
        load_layout = QHBoxLayout()
        load_layout.addWidget(QLabel("Загрузить вектор (через запятую):"))
        self.v_load_edit = QLineEdit()
        self.v_load_edit.setPlaceholderText("1,2,3,4,5")
        load_layout.addWidget(self.v_load_edit)
        btn_v_load = QPushButton("Загрузить")
        btn_v_load.clicked.connect(self._v_load)
        load_layout.addWidget(btn_v_load)
        layout.addLayout(load_layout)

        load_layout2 = QHBoxLayout()
        load_layout2.addWidget(QLabel("Второй вектор (через запятую):"))
        self.v_load_edit2 = QLineEdit()
        self.v_load_edit2.setPlaceholderText("1,2,3")
        load_layout2.addWidget(self.v_load_edit2)
        btn_v_load2 = QPushButton("Загрузить")
        btn_v_load2.clicked.connect(self._v_load2)
        load_layout2.addWidget(btn_v_load2)
        layout.addLayout(load_layout2)

        btn_v_clear2 = QPushButton("Очистить второй вектор")
        btn_v_clear2.clicked.connect(self._v_clear2)
        layout.addWidget(btn_v_clear2)
    def _update_bit_display(self):
        text = "[ "
        for i in range(self.bit_seq.get_length()):
            text += "1" if self.bit_seq.get(i) else "0"
            if i + 1 < self.bit_seq.get_length():
                text += ", "
        text += f" ]\n\nДлина: {self.bit_seq.get_length()}"
        self.bit_display.setText(text)
    def _update_vector_display(self):
        self.v_display.setText(self.v_seq.to_string())
        self.v_second_display.setText(self.v_second_seq.to_string())
    def _v_get(self):
        idx = self.v_index_spin.value()
        try:
            val = self.v_seq.get(idx)
            self._show_message("Get", f"Значение по индексу {idx}: {val}")
            self._show_status(f"Get({idx}) = {val}")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_set(self):
        if not self.v_value_edit.text():
            self._show_status("Введите значение", True)
            return
        val = int(self.v_value_edit.text())
        idx = self.v_index_spin.value()
        try:
            self.v_seq.set(idx, val)
            self.v_value_edit.clear()
            self._update_vector_display()
            self._show_status(f"Set({idx}, {val}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_clear(self):
        self.v_seq = VectorInt()
        self.v_second_seq = VectorInt()
        self._update_vector_display()
        self._show_status("Векторы очищены")

    def _v_add(self):
        try:
            result = self.v_seq.add(self.v_second_seq)
            self._show_message("Add", f"Результат сложения:\n{result.to_string()}")
            self._show_status("Сложение выполнено")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_sub(self):
        try:
            result = self.v_seq.sub(self.v_second_seq)
            self._show_message("Sub", f"Результат вычитания:\n{result.to_string()}")
            self._show_status("Вычитание выполнено")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_mul(self):
        if not self.v_scalar_edit.text():
            self._show_status("Введите скаляр", True)
            return
        scalar = int(self.v_scalar_edit.text())
        try:
            result = self.v_seq.mul(scalar)
            self._show_message("Mul", f"Результат умножения на {scalar}:\n{result.to_string()}")
            self._show_status(f"Умножение на {scalar} выполнено")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_norm(self):
        try:
            norm = self.v_seq.norm()
            self._show_message("Norm", f"Норма вектора: {norm:.6f}")
            self._show_status(f"Norm = {norm:.6f}")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_dot(self):
        try:
            result = self.v_seq.dot(self.v_second_seq)
            self._show_message("Dot Product", f"Скалярное произведение: {result}")
            self._show_status(f"Dot product = {result}")
        except Exception as e:
            self._show_status(str(e), True)
    def _v_second_clear(self):
        self.v_second_seq = VectorInt()
        self._update_vector_display()
        self._show_status("Второй вектор очищен")
    def _v_load(self):
        text = self.v_load_edit.text()
        if not text:
            self._show_status("Введите числа через запятую", True)
            return
        try:
            values = [int(x.strip()) for x in text.split(",")]
            self.v_seq = VectorInt(len(values))
            for i, val in enumerate(values):
                self.v_seq.set(i, val)
            self._update_vector_display()
            self._show_status(f"Загружен вектор: [{', '.join(map(str, values))}]")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_load2(self):
        text = self.v_load_edit2.text()
        if not text:
            self._show_status("Введите числа через запятую", True)
            return
        try:
            values = [int(x.strip()) for x in text.split(",")]
            self.v_second_seq = VectorInt(len(values))
            for i, val in enumerate(values):
                self.v_second_seq.set(i, val)
            self._update_vector_display()
            self._show_status(f"Загружен второй вектор: [{', '.join(map(str, values))}]")
        except Exception as e:
            self._show_status(str(e), True)

    def _v_clear2(self):
        self.v_second_seq = VectorInt()
        self._update_vector_display()
        self._show_status("Второй вектор очищен")
    def _bit_append(self):
        if not self.bit_value_edit.text():
            self._show_status("Введите бит (0 или 1)", True)
            return
        val = int(self.bit_value_edit.text())
        self.bit_seq.append(val)
        self.bit_value_edit.clear()
        self._update_bit_display()
        self._show_status(f"Bit Append({val}) выполнен")
    
    def _bit_prepend(self):
        if not self.bit_value_edit.text():
            self._show_status("Введите бит (0 или 1)", True)
            return
        val = int(self.bit_value_edit.text())
        self.bit_seq.prepend(val)
        self.bit_value_edit.clear()
        self._update_bit_display()
        self._show_status(f"Bit Prepend({val}) выполнен")
    
    def _bit_insert(self):
        if not self.bit_value_edit.text():
            self._show_status("Введите бит (0 или 1)", True)
            return
        val = int(self.bit_value_edit.text())
        idx = self.bit_index_spin.value()
        try:
            self.bit_seq.insert_at(idx, val)
            self.bit_value_edit.clear()
            self._update_bit_display()
            self._show_status(f"Bit InsertAt({idx}, {val}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_get(self):
        idx = self.bit_index_spin.value()
        try:
            val = self.bit_seq.get(idx)
            self._show_message("Get", f"Бит по индексу {idx}: {val}")
            self._show_status(f"Bit Get({idx}) = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_get_first(self):
        try:
            val = self.bit_seq.get_first()
            self._show_message("GetFirst", f"Первый бит: {val}")
            self._show_status(f"Bit GetFirst() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_get_last(self):
        try:
            val = self.bit_seq.get_last()
            self._show_message("GetLast", f"Последний бит: {val}")
            self._show_status(f"Bit GetLast() = {val}")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_get_subseq(self):
        start = self.bit_start_spin.value()
        end = self.bit_end_spin.value()
        try:
            sub = self.bit_seq.get_subsequence(start, end)
            text = "[ "
            for i in range(sub.get_length()):
                text += "1" if sub.get(i) else "0"
                if i + 1 < sub.get_length():
                    text += ", "
            text += " ]"
            self._show_message("GetSubsequence", f"Подпоследовательность [{start}, {end}]:\n{text}")
            self._show_status(f"Bit GetSubsequence({start}, {end}) выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_and(self):
        second = self._get_second_bit_sequence()
        if second is None:
            return
        try:
            res = self.bit_seq.bitwise_and(second)
            text = "[ "
            for i in range(res.get_length()):
                text += "1" if res.get(i) else "0"
                if i + 1 < res.get_length():
                    text += ", "
            text += " ]"
            self._show_message("AND", f"Результат AND:\n{text}")
            self._show_status("AND выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_or(self):
        second = self._get_second_bit_sequence()
        if second is None:
            return
        try:
            res = self.bit_seq.bitwise_or(second)
            text = "[ "
            for i in range(res.get_length()):
                text += "1" if res.get(i) else "0"
                if i + 1 < res.get_length():
                    text += ", "
            text += " ]"
            self._show_message("OR", f"Результат OR:\n{text}")
            self._show_status("OR выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_xor(self):
        second = self._get_second_bit_sequence()
        if second is None:
            return
        try:
            res = self.bit_seq.bitwise_xor(second)
            text = "[ "
            for i in range(res.get_length()):
                text += "1" if res.get(i) else "0"
                if i + 1 < res.get_length():
                    text += ", "
            text += " ]"
            self._show_message("XOR", f"Результат XOR:\n{text}")
            self._show_status("XOR выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_not(self):
        try:
            res = self.bit_seq.bitwise_not()
            text = "[ "
            for i in range(res.get_length()):
                text += "1" if res.get(i) else "0"
                if i + 1 < res.get_length():
                    text += ", "
            text += " ]"
            self._show_message("NOT", f"Результат NOT:\n{text}")
            self._show_status("NOT выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_concat(self):
        second = self._get_second_bit_sequence()
        if second is None:
            return
        try:
            result = self.bit_seq.concat(second)
            text = "[ "
            for i in range(result.get_length()):
                text += "1" if result.get(i) else "0"
                if i + 1 < result.get_length():
                    text += ", "
            text += " ]"
            self._show_message("Concat", f"Результат слияния:\n{text}")
            self._show_status("Bit Concat выполнен")
        except Exception as e:
            self._show_status(str(e), True)
    
    def _bit_clear(self):
        self.bit_seq = BitSequence()
        self._update_bit_display()
        self._show_status("BitSequence очищена")
        
    def _bit_map(self):
        pass
        
    def _bit_reduce(self):
        pass
    
def main():
    app = QApplication(sys.argv)
    window = SequenceTester()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()