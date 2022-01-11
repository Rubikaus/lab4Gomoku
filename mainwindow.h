#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QStringList>
#include <QWidget>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

#include <logic.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
    void drawField();
    void updateField();
    void btnClicked();
    void connecting();
    void clearField();
    void startNewGame(int, int);
    void showWin(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Mainwindow *ui;
    Logic *logic;
    int flag = 0;
    int _size = 3;
    int _needToWin = 3;
    QList<QPushButton*> _buttons;
    QWidget *settings;
};

class Core {
public:
    static QList<int> str2indexes(QString);
    static QIcon getLabel(int);
};

#endif // MAINWINDOW_H
