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

	connect(ui->iaAppend, &QPushButton::clicked, this, &MainWindow::onIaAppend);
	connect(ui->iaPrepend, &QPushButton::clicked, this,
			&MainWindow::onIaPrepend);
	connect(ui->iaInsertAt, &QPushButton::clicked, this,
			&MainWindow::onIaInsertAt);
	connect(ui->iaGet, &QPushButton::clicked, this, &MainWindow::onIaGet);
	connect(ui->iaGetFirst, &QPushButton::clicked, this,
			&MainWindow::onIaGetFirst);
	connect(ui->iaGetLast, &QPushButton::clicked, this,
			&MainWindow::onIaGetLast);
	connect(ui->iaGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onIaGetSubsequence);
	connect(ui->iaGetLength, &QPushButton::clicked, this,
			&MainWindow::onIaGetLength);
	connect(ui->iaConcat, &QPushButton::clicked, this, &MainWindow::onIaConcat);
	connect(ui->iaMap, &QPushButton::clicked, this, &MainWindow::onIaMap);
	connect(ui->iaReduce, &QPushButton::clicked, this, &MainWindow::onIaReduce);
	connect(ui->iaClear, &QPushButton::clicked, this, &MainWindow::onIaClear);

	connect(ui->mlAppend, &QPushButton::clicked, this, &MainWindow::onMlAppend);
	connect(ui->mlPrepend, &QPushButton::clicked, this,
			&MainWindow::onMlPrepend);
	connect(ui->mlInsertAt, &QPushButton::clicked, this,
			&MainWindow::onMlInsertAt);
	connect(ui->mlGet, &QPushButton::clicked, this, &MainWindow::onMlGet);
	connect(ui->mlGetFirst, &QPushButton::clicked, this,
			&MainWindow::onMlGetFirst);
	connect(ui->mlGetLast, &QPushButton::clicked, this,
			&MainWindow::onMlGetLast);
	connect(ui->mlGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onMlGetSubsequence);
	connect(ui->mlGetLength, &QPushButton::clicked, this,
			&MainWindow::onMlGetLength);
	connect(ui->mlConcat, &QPushButton::clicked, this, &MainWindow::onMlConcat);
	connect(ui->mlMap, &QPushButton::clicked, this, &MainWindow::onMlMap);
	connect(ui->mlReduce, &QPushButton::clicked, this, &MainWindow::onMlReduce);
	connect(ui->mlClear, &QPushButton::clicked, this, &MainWindow::onMlClear);

	connect(ui->ilAppend, &QPushButton::clicked, this, &MainWindow::onIlAppend);
	connect(ui->ilPrepend, &QPushButton::clicked, this,
			&MainWindow::onIlPrepend);
	connect(ui->ilInsertAt, &QPushButton::clicked, this,
			&MainWindow::onIlInsertAt);
	connect(ui->ilGet, &QPushButton::clicked, this, &MainWindow::onIlGet);
	connect(ui->ilGetFirst, &QPushButton::clicked, this,
			&MainWindow::onIlGetFirst);
	connect(ui->ilGetLast, &QPushButton::clicked, this,
			&MainWindow::onIlGetLast);
	connect(ui->ilGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onIlGetSubsequence);
	connect(ui->ilGetLength, &QPushButton::clicked, this,
			&MainWindow::onIlGetLength);
	connect(ui->ilConcat, &QPushButton::clicked, this, &MainWindow::onIlConcat);
	connect(ui->ilMap, &QPushButton::clicked, this, &MainWindow::onIlMap);
	connect(ui->ilReduce, &QPushButton::clicked, this, &MainWindow::onIlReduce);
	connect(ui->ilClear, &QPushButton::clicked, this, &MainWindow::onIlClear);

	connect(ui->bAppend, &QPushButton::clicked, this, &MainWindow::onBAppend);
	connect(ui->bPrepend, &QPushButton::clicked, this, &MainWindow::onBPrepend);
	connect(ui->bInsertAt, &QPushButton::clicked, this,
			&MainWindow::onBInsertAt);
	connect(ui->bGet, &QPushButton::clicked, this, &MainWindow::onBGet);
	connect(ui->bGetFirst, &QPushButton::clicked, this,
			&MainWindow::onBGetFirst);
	connect(ui->bGetLast, &QPushButton::clicked, this, &MainWindow::onBGetLast);
	connect(ui->bGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onBGetSubsequence);
	connect(ui->bGetLength, &QPushButton::clicked, this,
			&MainWindow::onBGetLength);
	connect(ui->bConcat, &QPushButton::clicked, this, &MainWindow::onBConcat);
	connect(ui->bMap, &QPushButton::clicked, this, &MainWindow::onBMap);
	connect(ui->bReduce, &QPushButton::clicked, this, &MainWindow::onBReduce);
	connect(ui->bClear, &QPushButton::clicked, this, &MainWindow::onBClear);

	connect(ui->vlineEdit1, &QLineEdit::returnPressed, this,
			&MainWindow::onVLineEdit1Enter);
	connect(ui->vlineEdit2, &QLineEdit::returnPressed, this,
			&MainWindow::onVLineEdit2Enter);
	connect(ui->vGetSize, &QPushButton::clicked, this, &MainWindow::onVGetSize);
	connect(ui->vGet, &QPushButton::clicked, this, &MainWindow::onVGet);
	connect(ui->vSet, &QPushButton::clicked, this, &MainWindow::onVSet);
	connect(ui->vPlusEquals, &QPushButton::clicked, this,
			&MainWindow::onVPlusEquals);
	connect(ui->vMinusEquals, &QPushButton::clicked, this,
			&MainWindow::onVMinusEquals);
	connect(ui->vMultiplyEquals, &QPushButton::clicked, this,
			&MainWindow::onVMultiplyEquals);
	connect(ui->vNorm, &QPushButton::clicked, this, &MainWindow::onVNorm);
	connect(ui->vScalarProduct, &QPushButton::clicked, this,
			&MainWindow::onVScalarProduct);

	connect(ui->lGenerate, &QPushButton::clicked, this,
			&MainWindow::onLazyGenerate);
	connect(ui->lAppend, &QPushButton::clicked, this,
			&MainWindow::onLazyAppend);
	connect(ui->lPrepend, &QPushButton::clicked, this,
			&MainWindow::onLazyPrepend);
	connect(ui->lInsertAt, &QPushButton::clicked, this,
			&MainWindow::onLazyInsertAt);
	connect(ui->lGet, &QPushButton::clicked, this, &MainWindow::onLazyGet);
	connect(ui->lGetFirst, &QPushButton::clicked, this,
			&MainWindow::onLazyGetFirst);
	connect(ui->lGetLast, &QPushButton::clicked, this,
			&MainWindow::onLazyGetLast);
	connect(ui->lGetSubsequence, &QPushButton::clicked, this,
			&MainWindow::onLazyGetSubsequence);
	connect(ui->lGetLength, &QPushButton::clicked, this,
			&MainWindow::onLazyGetLength);
	connect(ui->lConcat, &QPushButton::clicked, this,
			&MainWindow::onLazyConcat);
	connect(ui->lMap, &QPushButton::clicked, this, &MainWindow::onLazyMap);
	connect(ui->lReduce, &QPushButton::clicked, this,
			&MainWindow::onLazyReduce);
	connect(ui->lClear, &QPushButton::clicked, this, &MainWindow::onLazyClear);

	connect(ui->stLoad, &QPushButton::clicked, this, &MainWindow::onStLoad);
	connect(ui->stRead, &QPushButton::clicked, this, &MainWindow::onStRead);
	connect(ui->stWrite, &QPushButton::clicked, this, &MainWindow::onStWrite);

	connect(ui->statsLoad, &QPushButton::clicked, this,
			&MainWindow::onStatsLoad);
	connect(ui->statsCollect, &QPushButton::clicked, this,
			&MainWindow::onStatsCollect);
	connect(ui->statsReset, &QPushButton::clicked, this,
			&MainWindow::onStatsReset);
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::InputSequence()
{
	bool ok;
	QString text = QInputDialog::getText(
		this, "Ввод новоq послeдовательности",
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

void MainWindow::onIaAppend() { SAppend(&iaSeq, ui->iavalue, ui->iatextEdit); }
void MainWindow::onIaPrepend()
{
	SPrepend(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaInsertAt()
{
	SInsertAt(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaGet() { SGet(&iaSeq, ui->iavalue, ui->iatextEdit); }
void MainWindow::onIaGetFirst()
{
	SGetFirst(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaGetLast()
{
	SGetLast(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaGetSubsequence()
{
	SGetSubsequence(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaGetLength()
{
	SGetLength(&iaSeq, ui->iavalue, ui->iatextEdit);
}
void MainWindow::onIaConcat() { SConcat(&iaSeq, ui->iavalue, ui->iatextEdit); }
void MainWindow::onIaMap() { SMap(&iaSeq, ui->iavalue, ui->iatextEdit); }
void MainWindow::onIaReduce() { SReduce(&iaSeq, ui->iavalue, ui->iatextEdit); }
void MainWindow::onIaClear()
{
	try {
		iaSeq = ImmutableArraySequence<int>();
		updateDisplay(&maSeq, ui->iatextEdit);
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onMlAppend() { SAppend(&mlSeq, ui->mlvalue, ui->mltextEdit); }
void MainWindow::onMlPrepend()
{
	SPrepend(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlInsertAt()
{
	SInsertAt(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlGet() { SGet(&mlSeq, ui->mlvalue, ui->mltextEdit); }
void MainWindow::onMlGetFirst()
{
	SGetFirst(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlGetLast()
{
	SGetLast(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlGetSubsequence()
{
	SGetSubsequence(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlGetLength()
{
	SGetLength(&mlSeq, ui->mlvalue, ui->mltextEdit);
}
void MainWindow::onMlConcat() { SConcat(&mlSeq, ui->mlvalue, ui->mltextEdit); }
void MainWindow::onMlMap() { SMap(&mlSeq, ui->mlvalue, ui->mltextEdit); }
void MainWindow::onMlReduce() { SReduce(&mlSeq, ui->mlvalue, ui->mltextEdit); }
void MainWindow::onMlClear()
{
	try {
		mlSeq = MutableListSequence<int>();
		updateDisplay(&maSeq, ui->mltextEdit);
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onIlAppend() { SAppend(&ilSeq, ui->ilvalue, ui->iltextEdit); }
void MainWindow::onIlPrepend()
{
	SPrepend(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlInsertAt()
{
	SInsertAt(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlGet() { SGet(&ilSeq, ui->ilvalue, ui->iltextEdit); }
void MainWindow::onIlGetFirst()
{
	SGetFirst(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlGetLast()
{
	SGetLast(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlGetSubsequence()
{
	SGetSubsequence(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlGetLength()
{
	SGetLength(&ilSeq, ui->ilvalue, ui->iltextEdit);
}
void MainWindow::onIlConcat() { SConcat(&ilSeq, ui->ilvalue, ui->iltextEdit); }
void MainWindow::onIlMap() { SMap(&ilSeq, ui->ilvalue, ui->iltextEdit); }
void MainWindow::onIlReduce() { SReduce(&ilSeq, ui->ilvalue, ui->iltextEdit); }
void MainWindow::onIlClear()
{
	try {
		ilSeq = ImmutableListSequence<int>();
		updateDisplay(&maSeq, ui->iltextEdit);
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

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
void MainWindow::onBClear()
{
	try {
		bitSeq = BitSequence();
		updateDisplay(&maSeq, ui->btextEdit);
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::updateVDisplay()
{
	QString text = "Вектор 1: " + QString::fromStdString(vSeq1.ToString()) +
				   "\n"
				   "Вектор 2: " +
				   QString::fromStdString(vSeq2.ToString());
	ui->vtextEdit->setText(text);
}

Vector<int> MainWindow::parseVector(const QString &text)
{
	QStringList parts = text.split(',', Qt::SkipEmptyParts);
	Vector<int> vec(parts.size());
	for (int i = 0; i < parts.size(); ++i) {
		bool ok;
		int val = parts[i].trimmed().toInt(&ok);
		if (ok) {
			vec.Set(i, val);
		} else {
			throw std::invalid_argument("Неверное число: " +
										parts[i].toStdString());
		}
	}
	return vec;
}

Vector<int> &MainWindow::getCurrentVector()
{
	int idx = ui->vindex2->value();
	if (idx == 1)
		return vSeq1;
	else if (idx == 2)
		return vSeq2;
	else
		throw std::out_of_range("IndexOutOfRange");
}

Vector<int> &MainWindow::getOtherVector()
{
	int idx = ui->vindex2->value();
	if (idx == 1)
		return vSeq2;
	else if (idx == 2)
		return vSeq1;
	else
		throw std::out_of_range("IndexOutOfRange");
}

void MainWindow::onVLineEdit1Enter()
{
	try {
		QString text = ui->vlineEdit1->text();
		vSeq1 = parseVector(text);
		updateVDisplay();
		ui->statusbar->showMessage("✅ Вектор 1 загружен", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVLineEdit2Enter()
{
	try {
		QString text = ui->vlineEdit2->text();
		vSeq2 = parseVector(text);
		updateVDisplay();
		ui->statusbar->showMessage("✅ Вектор 2 загружен", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVGetSize()
{
	try {
		Vector<int> &vec = getCurrentVector();
		int size = vec.GetSize();
		ui->statusbar->showMessage(QString("✅ GetSize: %1").arg(size),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVGet()
{
	try {
		Vector<int> &vec = getCurrentVector();
		int index = ui->vindex->value();
		int value = vec.Get(index);
		ui->statusbar->showMessage(QString("✅ Get: %1").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVSet()
{
	try {
		Vector<int> &vec = getCurrentVector();
		int index = ui->vindex->value();
		int value = ui->vvalue->value();
		vec.Set(index, value);
		updateVDisplay();
		ui->statusbar->showMessage(QString("✅ Set: ").arg(value),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVPlusEquals()
{
	try {
		Vector<int> &current = getCurrentVector();
		Vector<int> &other = getOtherVector();
		current += other;
		updateVDisplay();
		ui->statusbar->showMessage("✅ +=", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVMinusEquals()
{
	try {
		Vector<int> &current = getCurrentVector();
		Vector<int> &other = getOtherVector();
		current -= other;
		updateVDisplay();
		ui->statusbar->showMessage("✅ -=", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVMultiplyEquals()
{
	try {
		Vector<int> &current = getCurrentVector();
		int scalar = ui->vvalue->value();
		current *= scalar;
		updateVDisplay();
		ui->statusbar->showMessage(QString("✅ *= %1").arg(scalar),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVNorm()
{
	try {
		Vector<int> &vec = getCurrentVector();
		double norm = vec.Norm();
		ui->statusbar->showMessage(QString("✅ Norm: %1").arg(norm),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVScalarProduct()
{
	try {
		int result = vSeq1.ScalarProduct(vSeq2);
		ui->statusbar->showMessage(QString("✅ ScalarProduct: %1").arg(result),
								   SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::onVClear()
{
	try {
		vSeq1 = Vector<int>();
		vSeq2 = Vector<int>();
		updateVDisplay();
		ui->statusbar->showMessage("✅ Clear", SHOWSTATUSBARTIME);
	} catch (const std::exception &e) {
		ui->statusbar->showMessage(QString("❌ Ошибка: %1").arg(e.what()),
								   SHOWSTATUSBARTIME);
	}
}

void MainWindow::updateLazyDisplay()
{
	if (!lazySeq) {
		ui->ltextEdit->setText("Последовательность не создана");
		return;
	}

	QString text = SeqtoQString(lazySeq.get());
	text += "\n\n";

	Cardinal card = lazySeq->GetCardinalLength();
	if (card.IsInfinite()) {
		text += "Длина: бесконечная\n";
		text += "Cardinal: ∞\n";
	} else {
		text += "Длина: " + QString::number(lazySeq->GetLength()) + "\n";
		text += "Cardinal: " + QString::number(card.GetValue()) + "\n";
	}

	text +=
		"Материализовано: " + QString::number(lazySeq->GetMaterializedCount());

	ui->ltextEdit->setText(text);
}

void MainWindow::onLazyGenerate()
{
	int type = ui->lType->currentIndex();
	int count = ui->lspinBox->value();

	if (count <= 0) {
		showStatus("❌ Количество элементов должно быть > 0", true);
		return;
	}

	try {
		std::function<int(Sequence<int> *)> generator;

		switch (type) {
		case 0: { // Fibbonacci
			generator = [](Sequence<int> *seq) -> int {
				auto *lazy = dynamic_cast<LazySequence<int> *>(seq);
				if (!lazy)
					throw std::runtime_error("Invalid context");
				int len = lazy->GetMaterializedCount();
				if (len == 0)
					return 1;
				if (len == 1)
					return 1;
				int a = lazy->Get(len - 2);
				int b = lazy->Get(len - 1);
				if (b > std::numeric_limits<int>::max() - a) {
					throw std::overflow_error("Fibonacci overflow at index " +
											  std::to_string(len));
				}
				return a + b;
			};
			int initial[] = {1, 1};
			MutableArraySequence<int> init(initial, 2);
			lazySeq = std::make_unique<LazySequence<int>>(generator, &init);
			break;
		}
		case 1: { // Naturals
			generator = [](Sequence<int> *seq) -> int {
				auto *lazy = dynamic_cast<LazySequence<int> *>(seq);
				if (!lazy)
					throw std::runtime_error("Invalid context");
				return lazy->GetMaterializedCount() + 1;
			};
			lazySeq = std::make_unique<LazySequence<int>>(generator, nullptr);
			break;
		}
		case 2: { // Factorials
			generator = [](Sequence<int> *seq) -> int {
				auto *lazy = dynamic_cast<LazySequence<int> *>(seq);
				if (!lazy)
					throw std::runtime_error("Invalid context");
				int len = lazy->GetMaterializedCount();
				if (len == 0)
					return 1;
				int prev = lazy->Get(len - 1);
				if (prev > std::numeric_limits<int>::max() / (len + 1)) {
					throw std::overflow_error("Factorial overflow at index " +
											  std::to_string(len));
				}
				return prev * (len + 1);
			};
			lazySeq = std::make_unique<LazySequence<int>>(generator, nullptr);
			break;
		}
		case 3: { // Custom
			QString input = ui->lUserInput->text();
			if (input.isEmpty()) {
				showStatus("❌ Введите числа через запятую", true);
				return;
			}
			QStringList parts = input.split(',', Qt::SkipEmptyParts);
			MutableArraySequence<int> init;
			for (const QString &part : parts) {
				bool ok;
				int val = part.trimmed().toInt(&ok);
				if (ok)
					init.Append(val);
			}
			if (init.GetLength() == 0) {
				showStatus("❌ Нет корректных чисел", true);
				return;
			}
			lazySeq = std::make_unique<LazySequence<int>>(&init);
			break;
		}
		default:
			showStatus("❌ Неизвестный тип", true);
			return;
		}
		if (lazySeq->GetCardinalLength().IsInfinite()) {
			for (int i = 0; i < count; ++i) {
				lazySeq->Get(i);
			}
		} else {
			lazySeq->GetLength();
		}

		updateLazyDisplay();
		showStatus("✅ Последовательность сгенерирована");
	} catch (const std::overflow_error &e) {
		showStatus(QString("❌ Переполнение: %1").arg(e.what()), true);
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyAppend()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	int value = ui->lvalue->value();
	try {
		lazySeq->Append(value);
		updateLazyDisplay();
		showStatus(QString("✅ Append(%1) выполнен").arg(value));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyPrepend()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	int value = ui->lvalue->value();
	try {
		lazySeq->Prepend(value);
		updateLazyDisplay();
		showStatus(QString("✅ Prepend(%1) выполнен").arg(value));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyInsertAt()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	int value = ui->lvalue->value();
	int index = ui->lindex->value();
	try {
		lazySeq->InsertAt(value, index);
		updateLazyDisplay();
		showStatus(
			QString("✅ InsertAt(%1, %2) выполнен").arg(value).arg(index));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyGet()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	int index = ui->lindex->value();
	try {
		int value = lazySeq->Get(index);
		QMessageBox::information(
			this, "Get",
			QString("Значение по индексу %1: %2").arg(index).arg(value));
		showStatus(QString("✅ Get(%1) = %2").arg(index).arg(value));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyGetFirst()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	try {
		int value = lazySeq->GetFirst();
		QMessageBox::information(this, "GetFirst",
								 QString("Первый элемент: %1").arg(value));
		showStatus(QString("✅ GetFirst = %1").arg(value));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyGetLast()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	try {
		int value = lazySeq->GetLast();
		QMessageBox::information(this, "GetLast",
								 QString("Последний элемент: %1").arg(value));
		showStatus(QString("✅ GetLast = %1").arg(value));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyGetSubsequence()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	int start = ui->lindex->value();
	int end = ui->lindex2->value();
	try {
		auto sub = lazySeq->GetSubsequence(start, end);
		QString text = SeqtoQString(sub.get());
		QMessageBox::information(this, "GetSubsequence",
								 QString("Подпоследовательность [%1, %2]:\n%3")
									 .arg(start)
									 .arg(end)
									 .arg(text));
		showStatus(
			QString("✅ GetSubsequence(%1, %2) выполнен").arg(start).arg(end));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyGetLength()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	try {
		Cardinal card = lazySeq->GetCardinalLength();
		QString msg;
		if (card.IsInfinite()) {
			msg = "Длина: бесконечная\nCardinal: ∞";
		} else {
			msg = "Длина: " + QString::number(lazySeq->GetLength()) +
				  "\nCardinal: " + QString::number(card.GetValue());
		}
		QMessageBox::information(this, "GetLength", msg);
		showStatus("✅ GetLength выполнен");
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyConcat()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	QString input = InputSequence();
	if (input.isEmpty())
		return;

	MutableArraySequence<int> other = QStringtoMa(input);
	try {
		auto result = lazySeq->Concat(&other);
		lazySeq = std::unique_ptr<LazySequence<int>>(
			dynamic_cast<LazySequence<int> *>(result.release()));
		updateLazyDisplay();
		showStatus("✅ Concat выполнен");
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyMap()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	try {
		auto result = lazySeq->Map([](const int &x) { return x * 2; });
		lazySeq = std::unique_ptr<LazySequence<int>>(
			dynamic_cast<LazySequence<int> *>(result.release()));
		updateLazyDisplay();
		showStatus("✅ Map (x * 2) выполнен");
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyReduce()
{
	if (!lazySeq) {
		showStatus("❌ Сначала сгенерируйте последовательность", true);
		return;
	}
	try {
		int result = lazySeq->Reduce(
			[](const int &x, const int &acc) { return x + acc; }, 0);
		QMessageBox::information(this, "Reduce",
								 QString("Сумма элементов: %1").arg(result));
		showStatus(QString("✅ Reduce = %1").arg(result));
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onLazyClear()
{
	lazySeq.reset();
	ui->ltextEdit->setText("Последовательность очищена");
	showStatus("✅ LazySequence очищена");
}

void MainWindow::showStatus(const QString &msg, bool error)
{
	QString prefix = error ? "❌ " : "✅ ";
	ui->statusbar->showMessage(prefix + msg, 3000);
}

void MainWindow::onStLoad()
{
	QString input = ui->stlineEdit->text();
	if (input.isEmpty()) {
		showStatus("❌ Введите данные через запятую", true);
		return;
	}

	try {
		auto seq = std::make_unique<MutableArraySequence<int>>();
		QStringList parts = input.split(',', Qt::SkipEmptyParts);
		for (const QString &part : parts) {
			bool ok;
			int val = part.trimmed().toInt(&ok);
			if (ok)
				seq->Append(val);
		}

		stream = std::make_unique<ReadWriteStream<int>>(seq.get());
		updateStreamDisplay();
		showStatus("✅ Поток загружен");
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onStRead()
{
	if (!stream) {
		showStatus("❌ Сначала загрузите поток", true);
		return;
	}

	try {
		if (stream->IsEndOfStream()) {
			showStatus("❌ Конец потока", true);
			return;
		}
		int value = stream->Read();
		showStatus(QString("✅ Прочитано: %1").arg(value));
		updateStreamDisplay();
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onStWrite()
{
	if (!stream) {
		showStatus("❌ Сначала загрузите поток", true);
		return;
	}

	bool ok;
	int value = ui->stlineEdit->text().toInt(&ok);
	if (!ok) {
		showStatus("❌ Введите целое число", true);
		return;
	}

	try {
		stream->Write(value);
		showStatus(QString("✅ Записано: %1").arg(value));
		updateStreamDisplay();
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::updateStreamDisplay()
{
	if (!stream) {
		ui->sttextEdit->setText("Поток не загружен");
		return;
	}

	QString text = "Поток:\n";
	text += "Позиция чтения: " + QString::number(stream->GetPosition()) + "\n";
	text += "Конец: " + QString(stream->IsEndOfStream() ? "true" : "false");

	ui->sttextEdit->setText(text);
}

void MainWindow::onStatsLoad()
{
	QString input = ui->statsInput->text();
	if (input.isEmpty()) {
		showStatus("❌ Введите числа через запятую", true);
		return;
	}

	stats.Reset();
	QStringList parts = input.split(',', Qt::SkipEmptyParts);
	for (const QString &part : parts) {
		bool ok;
		int val = part.trimmed().toInt(&ok);
		if (ok)
			stats.Add(val);
	}

	updateStatsDisplay();
	showStatus("✅ Данные загружены");
}

void MainWindow::onStatsCollect()
{
	if (stats.GetCount() == 0) {
		showStatus("❌ Нет данных для анализа", true);
		return;
	}

	try {
		updateStatsDisplay();
		showStatus("✅ Статистика собрана");
	} catch (const std::exception &e) {
		showStatus(QString("❌ Ошибка: %1").arg(e.what()), true);
	}
}

void MainWindow::onStatsReset()
{
	stats.Reset();
	ui->statsDisplay->clear();
	ui->statsInput->clear();
	showStatus("✅ Статистика сброшена");
}

void MainWindow::updateStatsDisplay()
{
	if (stats.GetCount() == 0) {
		ui->statsDisplay->setText("Нет данных");
		return;
	}

	QString text;
	text += "Количество: " + QString::number(stats.GetCount()) + "\n";
	text += "Сумма: " + QString::number(stats.GetSum()) + "\n";
	text += "Среднее: " + QString::number(stats.GetMean(), 'f', 4) + "\n";
	text += "Минимум: " + QString::number(stats.GetMin()) + "\n";
	text += "Максимум: " + QString::number(stats.GetMax()) + "\n";
	if (stats.GetCount() >= 2) {
		text +=
			"Дисперсия: " + QString::number(stats.GetVariance(), 'f', 4) + "\n";
		text += "Стандартное отклонение: " +
				QString::number(stats.GetStdDev(), 'f', 4) + "\n";
	}

	ui->statsDisplay->setText(text);
}