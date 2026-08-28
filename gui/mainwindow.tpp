#ifndef MAINWINDOW_TPP
#define MAINWINDOW_TPP
#include "ui_mainwindow.h"

#define SHOWSTATUSBARTIME 2000

template <> inline QString MainWindow::SeqtoQString(BitSequence *seq)
{
	if (!seq)
		return "nullptr";
	QString text = "[ ";
	for (int i = 0; i < seq->GetLength(); ++i) {
		text += seq->Get(i).GetValue() ? "1" : "0";
		if (i + 1 < seq->GetLength())
			text += ", ";
	}
	text += " ]";
	return text;
}
template <typename SeqType> QString MainWindow::SeqtoQString(SeqType *seq)
{
	QString text = "[ ";
	for (int i = 0; i < seq->GetLength(); ++i) {
		text += QString::number(seq->Get(i));
		if (i + 1 < seq->GetLength()) {
			text += ", ";
		}
	}
	text += " ]";
	return text;
}

template <> inline QString MainWindow::SeqtoQString(LazySequence<int> *seq)
{
	if (!seq)
		return "nullptr";

	QString text = "[ ";
	int len = seq->GetMaterializedCount();
	for (int i = 0; i < len; ++i) {
		try {
			text += QString::number(seq->Get(i));
			if (i + 1 < len)
				text += ", ";
		} catch (const std::exception &) {
			text += "?";
		}
	}
	text += " ]";
	return text;
}

template <typename SeqType>
void MainWindow::updateDisplay(SeqType *seq, QTextEdit *display)
{
	QString text = SeqtoQString(seq);
	text += "\n\nДлина: " + QString::number(seq->GetLength());

	display->setText(text);
}

template <typename SeqType>
inline void MainWindow::SAppend(SeqType *seq, QSpinBox *spinBox,
								QTextEdit *display)
{
	try {
		int value = spinBox->value();
		seq->Append(value);

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ Append: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SPrepend(SeqType *seq, QSpinBox *spinBox,
								 QTextEdit *display)
{
	try {
		int value = spinBox->value();
		seq->Prepend(value);

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ Prepend: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SInsertAt(SeqType *seq, QSpinBox *spinBox,
								  QTextEdit *display)
{
	try {
		int index = ui->maindex->value();
		int value = spinBox->value();
		seq->InsertAt(value, index);

		updateDisplay(seq, display);
		ui->statusbar->showMessage(
			QString("️✅ InsertAt: %1, index: %2").arg(value).arg(index),
			SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SGet(SeqType *seq, QSpinBox *spinBox,
							 QTextEdit *display)
{
	try {
		int index = ui->maindex->value();
		int value = seq->Get(index);

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ Get: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SGetFirst(SeqType *seq, QSpinBox *spinBox,
								  QTextEdit *display)
{
	try {
		int value = seq->GetFirst();

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ GetFirst: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::out_of_range &e) {
		ui->statusbar->showMessage("❌ Ошибка: последовательность пуста",
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SGetLast(SeqType *seq, QSpinBox *spinBox,
								 QTextEdit *display)
{
	try {
		int value = seq->GetLast();

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ GetLast: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::out_of_range &e) {
		ui->statusbar->showMessage("❌ Ошибка: последовательность пуста",
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

template <typename SeqType>
inline void MainWindow::SGetSubsequence(SeqType *seq, QSpinBox *spinBox,
										QTextEdit *display)
{
	try {
		int index = ui->maindex->value();
		int index2 = ui->maindex2->value();
		auto seq1 = seq->GetSubsequence(index, index2);

		updateDisplay(seq, display);
		ui->statusbar->showMessage(
			QString("️✅ GetSubsequence: %1").arg(SeqtoQString(seq1.get())),
			SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}
template <typename SeqType>
inline void MainWindow::SGetLength(SeqType *seq, QSpinBox *spinBox,
								   QTextEdit *display)
{
	try {
		int value = seq->GetLength();

		updateDisplay(seq, display);
		ui->statusbar->showMessage(QString("️✅ GetLength: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}
template <typename SeqType>
inline void MainWindow::SConcat(SeqType *seq, QSpinBox *spinBox,
								QTextEdit *display)
{
}
template <typename SeqType>
inline void MainWindow::SMap(SeqType *seq, QSpinBox *spinBox,
							 QTextEdit *display)
{
}

template <typename SeqType>
inline void MainWindow::SReduce(SeqType *seq, QSpinBox *spinBox,
								QTextEdit *display)
{
}
#endif // MAINWINDOW_TPP