#ifndef COORDINATE_H
#define COORDINATE_H

#include <QWidget>

namespace Ui {
class Coordinate;
}

class Coordinate : public QWidget
{
    Q_OBJECT

public:
    explicit Coordinate(QWidget *parent = nullptr);
    ~Coordinate();

private:
    Ui::Coordinate *ui;
};

#endif // COORDINATE_H
