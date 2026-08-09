#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define SHOWSTATUSBARTIME 2000

// onMaAppend<-onMutableArrayAppend...

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// connects
	connect(ui->Append, &QPushButton::clicked, this, &MainWindow::onMaAppend);
	connect(ui->Prepend, &QPushButton::clicked, this, &MainWindow::onMaPrepend);
	connect(ui->InsertAt, &QPushButton::clicked, this,
			&MainWindow::onMaInsertAt);
	connect(ui->Get, &QPushButton::clicked, this, &MainWindow::onMaGet);
	connect(ui->GetFirst, &QPushButton::clicked, this,
			&MainWindow::onMaGetFirst);
	connect(ui->GetLast, &QPushButton::clicked, this, &MainWindow::onMaGetLast);
	connect(ui->GetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onMaGetSubsequence);
	connect(ui->GetLength, &QPushButton::clicked, this,
			&MainWindow::onMaGetLength);
	connect(ui->Concat, &QPushButton::clicked, this, &MainWindow::onMaConcat);
	connect(ui->Map, &QPushButton::clicked, this, &MainWindow::onMaMap);
	connect(ui->Reduce, &QPushButton::clicked, this, &MainWindow::onMaReduce);
	connect(ui->Clear, &QPushButton::clicked, this, &MainWindow::onMaClear);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateDisplay()
{
	QString text = "[ ";
	for (int i = 0; i < maSeq.GetLength(); ++i) {
		text += QString::number(maSeq.Get(i));
		if (i + 1 < maSeq.GetLength()) {
			text += ", ";
		}
	}
	text += " ]\n\nДлина: " + QString::number(maSeq.GetLength());

	ui->textEdit->setText(text);
}

// buttons
void MainWindow::onMaAppend()
{
	try {
		int value = ui->spinBox->value();
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
		int value = ui->spinBox->value();
		maSeq.Prepend(value);

		updateDisplay();
		ui->statusbar->showMessage(QString("️✅ Prepend: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMaInsertAt() {}

void MainWindow::onMaGet() {}

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

void MainWindow::onMaGetSubsequence() {}

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
