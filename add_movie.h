#ifndef ADD_MOVIE_H
#define ADD_MOVIE_H
#include "QMessageBox"
#include <QMainWindow>
#include "QString"
#include "admin.h"
namespace Ui {
class add_movie;
}

class add_movie : public QMainWindow
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

	explicit add_movie(QWidget *parent = 0);
	~add_movie();
protected:
	void resizeEvent(QResizeEvent* evt) override;
private slots:
	void on_pushButton_clicked();

	void on_actionReset_triggered();

	void on_actionBack_triggered();

	void on_actionExit_triggered();

	void on_actionAddMovie_triggered();

private:
	Ui::add_movie *ui;
};

#endif // ADD_MOVIE_H
