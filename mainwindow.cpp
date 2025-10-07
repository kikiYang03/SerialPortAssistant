#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 实例化页面
    p1 = new SerialPort;
    p2 = new Coordinate;
    p3 = new Params;

    // 添加子页面
    ui->stackedWidget->addWidget(p1);
    qDebug() << "current index:" << ui->stackedWidget->count();
    ui->stackedWidget->addWidget(p2);
    qDebug() << "current index:" << ui->stackedWidget->count();
    ui->stackedWidget->addWidget(p3);
    qDebug() << "current index:" << ui->stackedWidget->count();

    // 设置当前页面
    ui->stackedWidget->setCurrentWidget(p1);

    // 隐藏菜单栏上的右击菜单
    this->setContextMenuPolicy(Qt::NoContextMenu);


    // ----------------------------------------------------------
    // 创建menuBar组件
    // ----------------------------------------------------------
    // 创建基础顶部菜单并让其隐藏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu * fileMenu = bar->addMenu("Ptr");

    // 隐藏菜单
    bar->setVisible(false);

    // 添加子菜单
    QAction *NewAction = fileMenu->addAction("串口配置");
    QAction *OpenAction = fileMenu->addAction("坐标展示");
    QAction *ReadAction = fileMenu->addAction("参数设置");

    // 创建工具栏
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,toolBar);

    // 将菜单项依次添加到工具栏
    toolBar->addAction(NewAction);
    toolBar->addAction(OpenAction);
    toolBar->addAction(ReadAction);

    // 设置禁止移动属性,工具栏默认贴在上方
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // ----------------------------------------------------------
    // 绑定槽函数——显示页面
    // ----------------------------------------------------------
    connect(NewAction,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(OpenAction,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ReadAction,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
