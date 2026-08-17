#include "mainwindow.h"
#include "ui_mainwindow.h"

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

QString MainWindow::InputSequence()
{
	bool ok;
	QString text = QInputDialog::getText(
		this, "Ввод новоq mavalueдовательности",
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
void MainWindow::onMaAppend() { SAppend(&maSeq, ui->mavalue, ui->matextEdit); }
void MainWindow::onMaPrepend()
{
	SPrepend(&maSeq, ui->mavalue, ui->matextEdit);
}
void MainWindow::onMaInsertAt()
{
	SInsertAt(&maSeq, ui->mavalue, ui->matextEdit);
}
void MainWindow::onMaGet() { SGet(&maSeq, ui->mavalue, ui->matextEdit); }
void MainWindow::onMaGetFirst()
{
	SGetFirst(&maSeq, ui->mavalue, ui->matextEdit);
}
void MainWindow::onMaGetLast()
{
	SGetLast(&maSeq, ui->mavalue, ui->matextEdit);
}
void MainWindow::onMaGetSubsequence()
{
	SGetSubsequence(&maSeq, ui->mavalue, ui->matextEdit);
}
void MainWindow::onMaGetLength()
{
	SGetLength(&maSeq, ui->mavalue, ui->matextEdit);
}

void MainWindow::onMaConcat() {}

void MainWindow::onMaMap() {}

void MainWindow::onMaReduce() {}

void MainWindow::onMaClear()
{
	try {
		maSeq = MutableArraySequence<int>();
		updateDisplay(&maSeq, ui->matextEdit);
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onIaAppend() {}
void MainWindow::onIaPrepend() {}
void MainWindow::onIaInsertAt() {}
void MainWindow::onIaGet() {}
void MainWindow::onIaGetFirst() {}
void MainWindow::onIaGetLast() {}
void MainWindow::onIaGetSubsequence() {}
void MainWindow::onIaGetLength() {}
void MainWindow::onIaConcat() {}
void MainWindow::onIaMap() {}
void MainWindow::onIaReduce() {}
void MainWindow::onIaClear() {}

void MainWindow::onMlAppend() {}
void MainWindow::onMlPrepend() {}
void MainWindow::onMlInsertAt() {}
void MainWindow::onMlGet() {}
void MainWindow::onMlGetFirst() {}
void MainWindow::onMlGetLast() {}
void MainWindow::onMlGetSubsequence() {}
void MainWindow::onMlGetLength() {}
void MainWindow::onMlConcat() {}
void MainWindow::onMlMap() {}
void MainWindow::onMlReduce() {}
void MainWindow::onMlClear() {}

void MainWindow::onIlAppend() {}
void MainWindow::onIlPrepend() {}
void MainWindow::onIlInsertAt() {}
void MainWindow::onIlGet() {}
void MainWindow::onIlGetFirst() {}
void MainWindow::onIlGetLast() {}
void MainWindow::onIlGetSubsequence() {}
void MainWindow::onIlGetLength() {}
void MainWindow::onIlConcat() {}
void MainWindow::onIlMap() {}
void MainWindow::onIlReduce() {}
void MainWindow::onIlClear() {}

void MainWindow::onBAppend() {}
void MainWindow::onBPrepend() {}
void MainWindow::onBInsertAt() {}
void MainWindow::onBGet() {}
void MainWindow::onBGetFirst() {}
void MainWindow::onBGetLast() {}
void MainWindow::onBGetSubsequence() {}
void MainWindow::onBGetLength() {}
void MainWindow::onBConcat() {}
void MainWindow::onBMap() {}
void MainWindow::onBReduce() {}
void MainWindow::onBClear() {}

void MainWindow::onVAppend() {}
void MainWindow::onVPrepend() {}
void MainWindow::onVInsertAt() {}
void MainWindow::onVGet() {}
void MainWindow::onVGetFirst() {}
void MainWindow::onVGetLast() {}
void MainWindow::onVGetSubsequence() {}
void MainWindow::onVGetLength() {}
void MainWindow::onVConcat() {}
void MainWindow::onVMap() {}
void MainWindow::onVReduce() {}
void MainWindow::onVClear() {}
