#ifndef ADD_MOVIE_H
#define ADD_MOVIE_H
#include "QMessageBox"
#include <QMainWindow>
#include "QString"
#include "Admin_Menu.h"
#include "Models.h"
#include "dbutil.h"
namespace Ui {
class add_movie;
}

class add_movie : public QMainWindow
{
	Q_OBJECT

public:
	explicit add_movie(QWidget *parent = 0, dbutil *db = nullptr);
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
	dbutil* db;
};

#endif // ADD_MOVIE_H
