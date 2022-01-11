#include "logic.h"
#include <QDebug>



Logic::Logic(int size) : _size(size)
{
    allocate(size);
}


Logic::Logic(int size, int needToWin) : _size(size), _needToWin(needToWin)
{
    allocate(size);
}


void Logic::allocate(int size)
{
    _field.resize(size);
    for(int i = 0; i < size; i++) {
        _field[i].resize(size);
    }
}


int Logic::putLabel(int i, int j)
{
    if (_field[i][j] == 0) {
        if (_step % 2 == 0) {
            _field[i][j] = 1;
        }
        else {
            _field[i][j] = 2;
        }
        _step++;
        return 0;
    }
    else {
        return -1;
    }
}


QVector<QVector<int>> Logic::getField()
{
    return _field;
}


int Logic::checkWin()
{
    int truth = 0;
    int all_steps = 0;
    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            if (_field[i][j] != 0) {
                truth = 0;
                for (int x = 1; x < _needToWin; x++) {
                    if (i + x < _size) {
                        if (_field[i + x][j] == _field[i][j])
                            truth++;
                        else
                            break;
                        if (truth == _needToWin - 1)
                            return _field[i][j];
                    }
                    else
                        break;
                }
                truth = 0;
                for (int x = 1; x < _needToWin; x++) {
                    if (j + x < _size) {
                        if (_field[i][j+x] == _field[i][j])
                            truth++;
                        else
                            break;
                        if (truth == _needToWin - 1)
                            return _field[i][j];
                    }
                    else
                        break;
                }
                truth = 0;
                for (int x = 1; x < _needToWin; x++) {
                    if (i + x < _size && j + x < _size) {
                        if (_field[i + x][j + x] == _field[i][j])
                            truth++;
                        else
                            break;
                        if (truth == _needToWin - 1)
                            return _field[i][j];
                    }
                    else
                        break;
                }
                truth = 0;
                for (int x = 1; x <= _needToWin; x++) {
                    if (i + x < _size && j - x >= 0) {
                        if (_field[i + x][j - x] == _field[i][j])
                            truth++;
                        else
                            break;
                        if (truth == _needToWin - 1)
                            return _field[i][j];
                    }
                    else
                        break;
                }
            }
            else
                all_steps++;
        }
    }
    if (all_steps == 0)
        return -1;
    return 0;
}


void Logic::changeValues(int size, int needToWin)
{
    _size = size;
    _needToWin = needToWin;
    _field.clear();
    allocate(size);
    _step = 0;
}
