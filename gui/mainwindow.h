#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BitSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "Vector.hpp"
#include <QInputDialog>
#include <QMainWindow>
#include <QSpinBox>
#include <QStatusBar>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

  private slots:
	void onMaAppend();
	void onMaPrepend();
	void onMaInsertAt();
	void onMaGet();
	void onMaGetFirst();
	void onMaGetLast();
	void onMaGetSubsequence();
	void onMaGetLength();
	void onMaConcat();
	void onMaMap();
	void onMaReduce();
	void onMaClear();

	void onIaAppend();
	void onIaPrepend();
	void onIaInsertAt();
	void onIaGet();
	void onIaGetFirst();
	void onIaGetLast();
	void onIaGetSubsequence();
	void onIaGetLength();
	void onIaConcat();
	void onIaMap();
	void onIaReduce();
	void onIaClear();

	void onMlAppend();
	void onMlPrepend();
	void onMlInsertAt();
	void onMlGet();
	void onMlGetFirst();
	void onMlGetLast();
	void onMlGetSubsequence();
	void onMlGetLength();
	void onMlConcat();
	void onMlMap();
	void onMlReduce();
	void onMlClear();

	void onIlAppend();
	void onIlPrepend();
	void onIlInsertAt();
	void onIlGet();
	void onIlGetFirst();
	void onIlGetLast();
	void onIlGetSubsequence();
	void onIlGetLength();
	void onIlConcat();
	void onIlMap();
	void onIlReduce();
	void onIlClear();

	void onBAppend();
	void onBPrepend();
	void onBInsertAt();
	void onBGet();
	void onBGetFirst();
	void onBGetLast();
	void onBGetSubsequence();
	void onBGetLength();
	void onBConcat();
	void onBMap();
	void onBReduce();
	void onBClear();

	void onVLineEdit1Enter();
	void onVLineEdit2Enter();
	void onVGetSize();
	void onVGet();
	void onVSet();
	void onVPlusEquals();
	void onVMinusEquals();
	void onVMultiplyEquals();
	void onVNorm();
	void onVScalarProduct();
	void onVClear();

  private:
	Ui::MainWindow *ui;

	MutableArraySequence<int> maSeq;
	ImmutableArraySequence<int> iaSeq;
	MutableListSequence<int> mlSeq;
	ImmutableListSequence<int> ilSeq;
	BitSequence bitSeq;
	Vector<int> vSeq1;
	Vector<int> vSeq2;

	// General methods
	template <typename SeqType>
	void updateDisplay(SeqType *seq, QTextEdit *display);
	QString InputSequence();
	template <typename SeqType> QString SeqtoQString(SeqType *seq);

	template <typename SeqType>
	void SAppend(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SPrepend(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SInsertAt(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SGet(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SGetFirst(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SGetLast(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SGetSubsequence(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SGetLength(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SConcat(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SMap(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	template <typename SeqType>
	void SReduce(SeqType *seq, QSpinBox *spinBox, QTextEdit *display);
	// Other methods
	QString MatoQString(Sequence<int> *maSeq);
	MutableArraySequence<int> QStringtoMa(QString text);

	// Vector methods
	void updateVDisplay();
	Vector<int> parseVector(const QString &text);
	Vector<int> &getCurrentVector();
	Vector<int> &getOtherVector();
};

#endif // MAINWINDOW_H
#include "mainwindow.tpp"