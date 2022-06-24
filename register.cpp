#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent, dbutil *db) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->db = db;
}

Register::~Register()
{
    delete ui;
}

void Register::on_signupBtn_clicked()
{
    QString user = ui->username->text();
    QString pass = ui->password->text();
    User userobj{user, pass};
    bool res = db->CreateUser(userobj);
    if (res) {
        QMessageBox::information(this, "Successfull", "You are registered successfully.");
        this->destroy();
        ((QWidget *) parent())->show();
    } else {
        QMessageBox::warning(this, "failed", "Register failed.");
    }
}


void Register::on_Register_rejected()
{
    this->destroy();
    ((QWidget *) parent())->show();
}

