#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QtCore/QCoreApplication>

#include "Solver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board: public QMainWindow
{
	Q_OBJECT

private:
	Ui::Board *ui;
	QVector<QVector<int>> solution;


public:
	Board(QWidget *parent = nullptr);
	~Board();
	Solver *s;

	void set_solution(QVector<QVector<int>>);

	QVector<QVector<int>> get_values();
	void add_solution();

private slots:
	void cmd_solve();
	void clear_screen();

public slots:
	void board_update(QVector<QVector<int>>);
};

#endif // BOARD_H
