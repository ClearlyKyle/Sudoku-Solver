#include <QTimer>
#include <QThread>

#include "Solver.h"
#include "ui_board.h"


Solver::Solver(QObject *parent): QObject(parent)
{

}

int Solver::valid(QVector<QVector<int>> bo, int num, QVector<int> pos)
{
	// check row
	for (int i = 0; i < 9; i++)
	{
		if (bo[pos[0]][i] == num && pos[1] != i)
		{
			return 0;
		}
	}

	// check column
	for (int i = 0; i < 9; i++)
	{
		if (bo[i][pos[1]] == num && pos[0] != i)
		{
			return 0;
		}
	}

	// check 3x3 box
	int box_x = static_cast<int>(qFloor(pos[1] / 3));
	int box_y = static_cast<int>(qFloor(pos[0] / 3));

	for (int i = (box_y * 3); i < (box_y * 3 + 3); i++)
	{
		for (int j = (box_x * 3); j < (box_x * 3 + 3); j++)
		{
			if (bo[i][j] == num && pos[0] != i && pos[1] != j)
			{
				return 0;
			}
		}
	}

	return 1;
}


QVector<int> Solver::find_empty(QVector<QVector<int>> bo)
{
	QVector<int> ret;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (bo[i][j] == 0)
			{
				ret.push_back(i);
				ret.push_back(j);

				return ret;
			}
		}
	}
	return QVector<int>();
}

void Solver::print_board()
{
	QDebug dbg(QtDebugMsg);

	for (int k = 0 ; k < board.size() ; k++) {
		for (int l = 0 ; l < board[k].size() ; l++) {
			dbg.nospace() << board[k][l] << " ";
		}
		dbg << "\n";
	}
}

int Solver::solve(QVector<QVector<int>> &bo)
{
	QVector<int> find = find_empty(bo);

	if (find.empty())
	{
		return 1;
	}


	for (int i = 1; i < 10; i++)
	{
		if (valid(bo, i, find))
		{
			bo[find[0]][find[1]] = i;

			emit valueChanged(bo);

			if (solve(bo))
			{
				return 1;
			}
			bo[find[0]][find[1]] = 0;
		}
	}

	return 0;
}

QVector<QVector<int>> Solver::solution()
{
	print_board();
	solve(board);
	return board;
}

void Solver::set_board(QVector<QVector<int>> bo)
{
	board = bo;
	intitial_values = bo;
}
