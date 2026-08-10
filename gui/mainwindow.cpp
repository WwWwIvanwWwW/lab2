#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define SHOWSTATUSBARTIME 2000

// onMaAppend<-onMutableArrayAppend...

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// connects
	connect(ui->maAppend, &QPushButton::clicked, this, &MainWindow::onMaAppend);
	connect(ui->maPrepend, &QPushButton::clicked, this,
			&MainWindow::onMaPrepend);
	connect(ui->maInsertAt, &QPushButton::clicked, this,
			&MainWindow::onMaInsertAt);
	connect(ui->maGet, &QPushButton::clicked, this, &MainWindow::onMaGet);
	connect(ui->maGetFirst, &QPushButton::clicked, this,
			&MainWindow::onMaGetFirst);
	connect(ui->maGetLast, &QPushButton::clicked, this,
			&MainWindow::onMaGetLast);
	connect(ui->maGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onMaGetSubsequence);
	connect(ui->maGetLength, &QPushButton::clicked, this,
			&MainWindow::onMaGetLength);
	connect(ui->maConcat, &QPushButton::clicked, this, &MainWindow::onMaConcat);
	connect(ui->maMap, &QPushButton::clicked, this, &MainWindow::onMaMap);
	connect(ui->maReduce, &QPushButton::clicked, this, &MainWindow::onMaReduce);
	connect(ui->maClear, &QPushButton::clicked, this, &MainWindow::onMaClear);
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::MatoQString(Sequence<int> *maSeq)
{
	QString text = "[ ";
	for (int i = 0; i < maSeq->GetLength(); ++i) {
		text += QString::number(maSeq->Get(i));
		if (i + 1 < maSeq->GetLength()) {
			text += ", ";
		}
	}
	text += " ]";
	return text;
}

void MainWindow::updateDisplay()
{
	QString text = MatoQString(&maSeq);
	text += "\n\nДлина: " + QString::number(maSeq.GetLength());

	ui->textEdit->setText(text);
}

QString MainWindow::InputSequence()
{
	bool ok;
	QString text = QInputDialog::getText(
		this, "Ввод новоmavalueдовательности",
		"Введите последовательность через запятую", QLineEdit::Normal, "", &ok);

	if (!ok) {
		return QString();
	}
	return text;
}

MutableArraySequence<int> MainWindow::QStringtoMa(QString text)
{
	MutableArraySequence<int> maSeq;
	bool ok;
	int num;
	QStringList parts = text.split(",", Qt::SkipEmptyParts);

	for (QString &part : parts) {
		num = part.trimmed().toInt(&ok);
		if (ok) {
			maSeq.Append(num);
		}
	}
	return maSeq;
};

// buttons
void MainWindow::onMaAppend()
{
	try {
		int value = ui->mavalue->value();
		maSeq.Append(value);

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ Append: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaPrepend()
{
	try {
		int value = ui->mavalue->value();
		maSeq.Prepend(value);

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ Prepend: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaInsertAt()
{
	try {
		int index = ui->maindex->value();
		int value = ui->mavalue->value();
		maSeq.InsertAt(value, index);

		updateDisplay();
		ui->statusbar->showMessage(
			QString("️✅ InsertAt: %1, index: %2").arg(value).arg(index),
			SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaGet()
{
	try {
		int index = ui->maindex->value();
		int value = maSeq.Get(index);

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ Get: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaGetFirst()
{
	try {
		int value = maSeq.GetFirst();

		updateDisplay();
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

void MainWindow::onMaGetLast()
{
	try {
		int value = maSeq.GetLast();

		updateDisplay();
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

void MainWindow::onMaGetSubsequence()
{
	try {
		int index = ui->maindex->value();
		int index2 = ui->maindex2->value();
		int value = ui->mavalue->value();
		auto maSeq1 = maSeq.GetSubsequence(index, index2);

		updateDisplay();
		ui->statusbar->showMessage(
			QString("️✅ GetSubsequence: %1").arg(MatoQString(maSeq1.get())),
			SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaGetLength()
{
	try {
		int value = maSeq.GetLength();

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ GetLength: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::out_of_range &e) {
		ui->statusbar->showMessage("❌ Ошибка: последовательность пуста",
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaConcat() {}

void MainWindow::onMaMap() {}

void MainWindow::onMaReduce() {}

void MainWindow::onMaClear()
{
	try {
		maSeq = MutableArraySequence<int>();

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ Clear"), SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}
