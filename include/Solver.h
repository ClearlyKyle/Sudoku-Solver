#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QObject>

// #include "Board.h"

class Solver: public QObject
{
	Q_OBJECT

private:

	QVector<QVector<QVector <int>>> vis_sol;
	QVector<QVector <int>> board;

public:
	explicit Solver(QObject *parent = nullptr);

	int valid(QVector<QVector<int>>, int, QVector<int>);
	QVector<int> find_empty(QVector<QVector<int>> bo);
	int solve(QVector<QVector<int>> &bo);

	QVector<QVector<int>> solution();
	void set_board(QVector<QVector<int>>);
	void print_board();

signals:
	void valueChanged(QVector<QVector<int>>);

};

#endif // SOLVER_H
