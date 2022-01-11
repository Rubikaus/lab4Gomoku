#include "mainwindow.h"
#include "ui_mainwindow.h"



Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    logic = new Logic(_size, 3);
    drawField();
    connecting();
}


Mainwindow::~Mainwindow()
{
    delete ui;
}


void Mainwindow::btnClicked()
{
    auto fromWho = sender();
    QPushButton *button = dynamic_cast<QPushButton*>(fromWho);
    auto coords = Core::str2indexes(button->objectName());
    logic -> putLabel(coords[0], coords[1]);
    int code =logic->checkWin();
    updateField();
    if (code != 0) {
        if (code == 1) {
            showWin("Крестики выиграли!");
        }
        else if (code == 2) {
            showWin("Нолики выиграли!");
        }
        else if (code == -1) {
            showWin("Ничья");
        }
        startNewGame(_size, _needToWin);
    }
}


void Mainwindow::connecting()
{
    for (auto button : _buttons) {
        connect(button, &QPushButton::clicked, this, &Mainwindow::btnClicked);
    }
}


void Mainwindow::clearField()
{
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            ui->field->itemAt(i*_size+j)->widget()->deleteLater();
        }
    }
    _buttons.clear();
}


void Mainwindow::startNewGame(int size, int needToWin)
{
    clearField();
    _size = size;
    _needToWin = needToWin;
    logic->changeValues(_size, _needToWin);
    drawField();
    connecting();
}


void Mainwindow::showWin(QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результат!");
    msgBox.setText(text);
    msgBox.exec();
}


void Mainwindow::drawField()
{
    QVector<QVector<int>> field = logic->getField();
    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(QSize(50, 50));
            button->setIcon(Core::getLabel(field[i][j]));
            button->setIconSize(QSize(32, 32));
            button->setObjectName(QString::number(i) + ";" + QString::number(j));
            button->setStyleSheet("font: bold;background-color: white;font-size: 36px;color:black;vertical-align: middle;");
            _buttons.append(button);
            ui->field->addWidget(button, i, j);
        }
    }
    this->adjustSize();
}


void Mainwindow::updateField()
{
    QVector<QVector<int>> field = logic->getField();
    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            _buttons[i*_size+j]->setIcon(Core::getLabel(field[i][j]));
        }
    }
}


QList<int> Core::str2indexes(QString str)
{
    QStringList indexes = str.split(";");
    return {indexes[0].toInt(), indexes[1].toInt()};
}


QIcon Core::getLabel(int code)
{
    QPixmap pixmap;
    if (code == 1) {
        pixmap.load("X.png");
    }
    else if (code == 2)
        pixmap.load("O.png");
    QIcon icon(pixmap);
    return icon;
}


void Mainwindow::on_pushButton_clicked()
{
    startNewGame(ui->sizeBox->value(), ui->needToWinBox->value());
    _size = ui->sizeBox->value();
    _needToWin = ui->needToWinBox->value();
}
