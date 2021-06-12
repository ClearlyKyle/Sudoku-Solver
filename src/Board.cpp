
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QValidator>
//#include <QtGui/QIntValidator>
#include <QRegularExpressionValidator>
//#include <QRegExp>
#include <QTime>
#include <QCoreApplication>
#include <QApplication>
#include <QTextEdit>
#include <QMessageBox>

#include "Board.h"
#include "Solver.h"
#include "ui_board.h"

Board::Board(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::Board)
{
	ui->setupUi(this);

	// Solver *mSolver = new Solver(this);

	for (auto lineEdit : this->findChildren<QLineEdit *>())
	{
		// regexp: optional '-' followed by between 1 and 3 digits
		QRegularExpression rx("[1-9]");
		QValidator *validator = new QRegularExpressionValidator(rx, this);

		// connect lineEdit or change values
		lineEdit->setValidator(validator);
	}
	connect(ui->cmd_solve, SIGNAL(pressed()), this, SLOT(cmd_solve()));
	connect(ui->clear, SIGNAL(pressed()), this, SLOT(clear_screen()));
}

Board::~Board()
{
	delete ui;
}

void Board::set_solution(QVector<QVector<int>> bo)
{
	solution = bo;
}

QVector<QVector<int>> Board::get_values()
{
	int i = 0;

	QVector<QVector<int>> board;
	QVector<int> temp;

	for (auto lineEdit : this->findChildren<QLineEdit *>())
	{
		i++;

		if (!lineEdit->text().isEmpty())
		{
			lineEdit->setStyleSheet("color: #0000FF");
		}

		temp.push_back(QString(lineEdit->text()).toInt());

		// Making 2D vector of the values in the squares
		if (i % 9 == 0)
		{
			board.push_back(temp);
			temp.clear();
		}
	}
	return board;
}

void Board::add_solution()
{
	int i = 0, j = 0;

	QDebug dbg(QtDebugMsg);

	qDebug("ADD_SOLUTION");

	for (int k = 0; k < solution.size(); k++)
	{
		for (int l = 0; l < solution[k].size(); l++)
		{
			dbg.nospace() << solution[k][l] << " ";
		}
		dbg << "\n";
	}

	for (auto lineEdit : this->findChildren<QLineEdit *>())
	{

		lineEdit->setText(QString::number(solution[j][i]));
		lineEdit->update();
		QCoreApplication::processEvents();

		QTime dieTime = QTime::currentTime().addMSecs(40);
		while (QTime::currentTime() < dieTime)
			// QCoreApplication::processEvents();

			// delay();
			qDebug() << lineEdit << solution[j][i] << QString::number(solution[j][i]);
		/*if (lineEdit->text().isEmpty())
		{
			qDebug("Something here");
			lineEdit->setText(QString::number(solution[j][i]));
			lineEdit->repaint();
			delay();

		}
		*/
		i++;
		if (i % 9 == 0)
		{
			i = 0;
			j++;
		}
	}
}

void Board::cmd_solve()
{
	Solver *s = new Solver(this);
	s->set_board(get_values());
	connect(s, SIGNAL(valueChanged(QVector<QVector<int>>)), this, SLOT(board_update(QVector<QVector<int>>)));
	solution = s->solution();
	// add_solution();
}

void Board::clear_screen()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Boo", "Are you sure you want to clear all boxes?", QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{

		// yes clear the boxes
		qDebug() << "YES was clicked";

		for (auto lineEdit : this->findChildren<QLineEdit *>())
		{
			lineEdit->setText("");
		}
	}
	else
	{
		qDebug() << "NO was clicked";
	}
}

void Board::board_update(QVector<QVector<int>> bo)
{
	int i = 0, j = 0;

	QDebug dbg(QtDebugMsg);

	qDebug("ADD_SOLUTION");

	for (int k = 0; k < bo.size(); k++)
	{
		for (int l = 0; l < bo[k].size(); l++)
		{
			dbg.nospace() << bo[k][l] << " ";
		}
		dbg << "\n";
	}

	for (auto lineEdit : this->findChildren<QLineEdit *>())
	{

		lineEdit->setText(QString::number(bo[j][i]));
		lineEdit->update();

		QTime dieTime = QTime::currentTime().addMSecs(5);
		while (QTime::currentTime() < dieTime)
			QCoreApplication::processEvents();

		// qDebug() << lineEdit << bo[j][i] << QString::number(bo[j][i]);
		if (lineEdit->text().isEmpty())
		{
			qDebug("Something here");
			lineEdit->setText(QString::number(bo[j][i]));
			lineEdit->repaint();
		}
		i++;
		if (i % 9 == 0)
		{
			i = 0;
			j++;
		}
	}
}
