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

  private:
	Ui::MainWindow *ui;

	MutableArraySequence<int> maSeq;
	ImmutableArraySequence<int> iaSeq;
	MutableListSequence<int> mlSeq;
	ImmutableListSequence<int> ilSeq;
	BitSequence bitSeq;
	Vector<int> vectorSeq;

	QString MatoQString(Sequence<int> *maSeq);
	void updateDisplay();
	QString InputSequence();
	MutableArraySequence<int> QStringtoMa(QString text);
};
#endif // MAINWINDOW_H
