#ifndef ADMIN_H
#define ADMIN_H
#include "admin_login.h"
#include <QMainWindow>
#include "add_movie.h"
#include "movie_list.h"

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
	Q_OBJECT

public:
	explicit Admin(QWidget *parent = 0);
	~Admin();

protected:
	void resizeEvent(QResizeEvent* evt) override;

private slots:
	void on_actionBack_triggered();

	void on_actionExit_triggered();

	void on_pushButton_Addmovie_clicked();

	void on_pushButton_MovieList_clicked();

	void on_actionMovieList_triggered();

	void on_actionAddMovie_triggered();

private:
	Ui::Admin *ui;
};

#endif // ADMIN_H
