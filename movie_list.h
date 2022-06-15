#ifndef MOVIE_LIST_H
#define MOVIE_LIST_H
#include <admin.h>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "QPixmap"
#include "QTableWidgetItem"
#include "QTableWidget"
namespace Ui {
class movie_list;
}

class movie_list : public QMainWindow
{
	Q_OBJECT

public:
	class Movie{
	public:
		QString Name ;
		QString Director;
		QString Movie_Cast;
		QString IMDB;
		QString Tickets;
		QString Release_date;
		QString Genre;
		QString Time;
		QString BookedTickets;
	};
	bool cell_check = false;
	explicit movie_list(QWidget *parent = 0);
	~movie_list();

protected:
	void resizeEvent(QResizeEvent* evt) override;

	void Refresh_TableWidget_Film();
private slots:
	void on_actionExit_triggered();

	void on_actionBack_triggered();

	void on_tableWidget_film_cellChanged(int row, int column);
	
	void on_actionSave_triggered();

	void on_actionRemove_triggered();

	void on_actionRefresh_triggered();

private:
	Ui::movie_list *ui;
};

#endif // MOVIE_LIST_H
