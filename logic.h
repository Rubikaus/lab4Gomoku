#ifndef LOGIC_H
#define LOGIC_H

#include <QVector>
#include <QString>
#include <QList>

class Logic
{
public:
    Logic();
    Logic(int);
    Logic(int, int);
    int putLabel(int, int);
    QVector<QVector<int>> getField();
    int checkWin();
    void changeValues(int, int);

private:
    QVector<QVector<int>> _field;
    void allocate(int);
    int _step = 0;
    int _size = 3;
    int _needToWin = _size;
};

#endif // LOGIC_H
