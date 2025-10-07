#include "coordinate.h"
#include "ui_coordinate.h"

Coordinate::Coordinate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Coordinate)
{
    ui->setupUi(this);
}

Coordinate::~Coordinate()
{
    delete ui;
}
