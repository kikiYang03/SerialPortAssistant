#include "ROSVisualizer.h"
#include "ui_rosvisualizer.h"  // 注意：文件名应该小写
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QtMath>
#include <QPen>
#include <QDebug>

ROSVisualizer::ROSVisualizer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ROSVisualizer)  // 初始化ui指针
{
    ui->setupUi(this);  // 必须先调用setupUi
    setupUI();
}

ROSVisualizer::~ROSVisualizer()
{
    delete ui;  // 清理ui指针
}

void ROSVisualizer::setupUI()
{
    // 创建场景
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(-50, -50, 100, 100);  // 网格范围

    // 使用UI文件中的QGraphicsView，将其转换为ZoomableView
    // ZoomableView *zoomView = new ZoomableView(m_scene, ui->rosVisual);
    ui->rosVisual->setScene(m_scene);

    drawGrid();
    drawAxes();

    // ------------------ FLU 坐标系修正 ------------------
    // 初始缩放
    const double initialScale = 35.0;  // 根据地图调整
    ui->rosVisual->scale(initialScale, -initialScale); // Y 轴翻转，保证F+向上

    // 旋转视图 -90°
    ui->rosVisual->rotate(90);  // 顺时针旋转 90°

    // 居中
    ui->rosVisual->centerOn(0, 0);
}


// ====================== 数据更新 ======================
void ROSVisualizer::updateMap(const OccupancyGrid& map)
{
    m_currentMap = map;
    refreshMapPixmap();
}

void ROSVisualizer::updateScan(const LaserScan& scan)
{
    m_currentScan = scan;
    refreshScanOverlay();
}

void ROSVisualizer::updateTf(const TFMessage& tf)
{
    m_currentTf = tf;
    refreshTfOverlay();
}

// ====================== 绘制背景网格 ======================
void ROSVisualizer::drawGrid()
{
    const int gridCount = 50;
    QPen gridPen(QColor(220, 220, 220));
    gridPen.setWidthF(0.0);

    for (int i = -gridCount; i <= gridCount; ++i) {
        float pos = i * GRID_STEP;
        m_scene->addLine(-gridCount * GRID_STEP, pos, gridCount * GRID_STEP, pos, gridPen);
        m_scene->addLine(pos, -gridCount * GRID_STEP, pos, gridCount * GRID_STEP, gridPen);
    }
}

void ROSVisualizer::drawAxes()
{
    QPen axisPen(Qt::black, 0.05);
    m_scene->addLine(-50, 0, 50, 0, axisPen);
    m_scene->addLine(0, -50, 0, 50, axisPen);

    // FLU坐标系主轴线 - 长度为1米
    const double axisLength = 1.0; // 1米长度

    // F+轴 (Forward) - 红色
    QPen fAxisPen(Qt::red, 0.2);
    m_scene->addLine(0, 0, axisLength, 0, fAxisPen);

    // L+轴 (Left) - 蓝色
    QPen lAxisPen(Qt::blue, 0.2);
    m_scene->addLine(0, 0, 0, axisLength, lAxisPen);
}

// ====================== 实时刷新地图 ======================
void ROSVisualizer::refreshMapPixmap()
{
    if (m_currentMap.data.isEmpty()) return;

    int w = m_currentMap.width;
    int h = m_currentMap.height;
    float res = m_currentMap.resolution;

    QImage img(w, h, QImage::Format_RGB888);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int idx = y * w + x;
            float val = m_currentMap.data[idx];
            QColor color;
            if (val < 0)
                color = QColor(150,150,150);  // 未知
            else if (val == 0)
                color = Qt::white;             // 空闲
            else
                color = Qt::black;             // 占用
            img.setPixelColor(x, y, color);
        }
    }

    QPixmap pix = QPixmap::fromImage(img);

    if (!m_mapItem)
        m_mapItem = m_scene->addPixmap(pix);
    else
        m_mapItem->setPixmap(pix);

    m_mapItem->setZValue(-10);
    float scale = res / GRID_STEP;
    m_mapItem->setScale(scale);

    float origin_x = m_currentMap.origin_x / GRID_STEP;
    float origin_y = m_currentMap.origin_y / GRID_STEP;
    m_mapItem->setPos(origin_x, origin_y);
}

// ====================== 实时叠加 TF ======================
void ROSVisualizer::refreshTfOverlay()
{
    bool foundBaseLink = false;
    double base_x = 0.0, base_y = 0.0, base_yaw = 0.0;

    for (const auto &transform : m_currentTf.transforms) {
        if (transform.header.frame_id == "map" && transform.child_frame_id == "base_link") {
            base_x = transform.x;
            base_y = transform.y;
            base_yaw = transform.yaw;
            foundBaseLink = true;
            // 显示tf坐标
            QString textX = QString::number(transform.x, 'f', 2) + "m";

            QString textY = QString::number(transform.y, 'f', 2) + "m";
            QString textZ = QString::number(transform.z, 'f', 2) + "m";

            double yawDeg = fmod((transform.yaw * 180.0 / M_PI) + 360.0, 360.0);
            QString textYaw = QString::number(yawDeg, 'f', 2)+ "°";
            // 设置右对齐
            ui->robPosX->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->robPosY->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->robPosZ->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->robPosYaw->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            ui->robPosX->setText(textX);
            ui->robPosY->setText(textY);
            ui->robPosZ->setText(textZ);
            ui->robPosYaw->setText(textYaw);
            break;
        }
    }

    if (!foundBaseLink) return;

    QPointF currentPos(base_x / GRID_STEP, base_y / GRID_STEP);

    updateTrajectory(currentPos);
    updateRobotPose(currentPos, base_yaw * 180.0 / M_PI);

    refreshScanOverlay();
}

void ROSVisualizer::updateTrajectory(const QPointF& currentPos)
{
    m_trajectoryPoints.append(currentPos);
    const int MAX_TRAJECTORY_POINTS = 1000;
    if (m_trajectoryPoints.size() > MAX_TRAJECTORY_POINTS)
        m_trajectoryPoints.removeFirst();

    if (!m_trajectoryGroup) {
        m_trajectoryGroup = new QGraphicsItemGroup();
        m_trajectoryGroup->setZValue(10);
        m_scene->addItem(m_trajectoryGroup);
    }

    if (m_trajectoryPoints.size() >= 2) {
        QPointF p1 = m_trajectoryPoints[m_trajectoryPoints.size() - 2];
        QPointF p2 = m_trajectoryPoints[m_trajectoryPoints.size() - 1];
        auto line = m_scene->addLine(p1.x(), p1.y(), p2.x(), p2.y(),
                                     QPen(Qt::blue, 0));
        m_trajectoryGroup->addToGroup(line);
    }
}

// ====================== 更新机器人姿态 ======================
void ROSVisualizer::updateRobotPose(const QPointF& position, double yaw_deg)
{
    if (!m_tfGroup) {
        m_tfGroup = new QGraphicsItemGroup();
        m_tfGroup->setZValue(20);
        m_scene->addItem(m_tfGroup);

        QGraphicsPixmapItem* arrowItem = new QGraphicsPixmapItem(QPixmap(":/images/arrow.png"));
        arrowItem->setOffset(-arrowItem->pixmap().width()/2, -arrowItem->pixmap().height()/2);
        arrowItem->setScale(0.003);
        m_tfGroup->addToGroup(arrowItem);
    }

    auto arrowItem = dynamic_cast<QGraphicsPixmapItem*>(m_tfGroup->childItems().first());
    arrowItem->setPos(position);
    arrowItem->setRotation(yaw_deg + 90.0);  // FLU修正
}

// ====================== 实时叠加激光 ======================
void ROSVisualizer::refreshScanOverlay()
{
    if (m_currentScan.ranges.isEmpty() || m_currentTf.transforms.isEmpty()) return;

    if (m_scanGroup) {
        m_scene->removeItem(m_scanGroup);
        delete m_scanGroup;
        m_scanGroup = nullptr;
    }

    m_scanGroup = new QGraphicsItemGroup();
    m_scanGroup->setZValue(5);

    QPen pen(Qt::red, 0);

    double base_x = 0.0, base_y = 0.0, base_yaw = 0.0;
    for (const auto &transform : m_currentTf.transforms) {
        if (transform.header.frame_id == "map" && transform.child_frame_id == "base_link") {
            base_x = transform.x;
            base_y = transform.y;
            base_yaw = transform.yaw;
            break;
        }
    }

    float angle = m_currentScan.angle_min;
    float inc = m_currentScan.angle_increment;

    for (float range : m_currentScan.ranges) {
        if (range >= m_currentScan.range_min && range <= m_currentScan.range_max) {
            float x_rel = range * cos(angle);
            float y_rel = range * sin(angle);

            float x_map = base_x + (x_rel * cos(base_yaw) - y_rel * sin(base_yaw));
            float y_map = base_y + (x_rel * sin(base_yaw) + y_rel * cos(base_yaw));

            const float pointSize = 0.05;  // 缩小为原本0.5
            QGraphicsEllipseItem* point = new QGraphicsEllipseItem(
                x_map / GRID_STEP - pointSize/2,
                y_map / GRID_STEP - pointSize/2,
                pointSize, pointSize);
            point->setPen(pen);
            point->setBrush(Qt::red);
            m_scanGroup->addToGroup(point);
        }
        angle += inc;
    }

    m_scene->addItem(m_scanGroup);
}


void ROSVisualizer::on_clearBtn_clicked()
{
    // 清空场景的所有元素
    m_scene->clear();

    // 重新绘制背景网格和坐标轴
    drawGrid();
    drawAxes();

    // 清空所有数据
    m_currentMap = OccupancyGrid();
    m_currentScan = LaserScan();
    m_currentTf = TFMessage();
    m_trajectoryPoints.clear();

    // 清空图元引用
    m_mapItem = nullptr;
    m_scanGroup = nullptr;
    m_tfGroup = nullptr;
    m_trajectoryGroup = nullptr;

    // 清空界面显示的位姿信息
    ui->robPosX->clear();
    ui->robPosY->clear();
    ui->robPosZ->clear();
    ui->robPosYaw->clear();

    qDebug() << "Visualization cleared.";
}


void ROSVisualizer::on_locateBtn_clicked()
{
    if (!m_tfGroup) {
        qDebug() << "No robot pose available to locate.";
        return;
    }

    // 获取机器人箭头图元（m_tfGroup 内的 QGraphicsPixmapItem）
    if (m_tfGroup->childItems().isEmpty()) {
        qDebug() << "Robot arrow not found.";
        return;
    }

    auto arrowItem = dynamic_cast<QGraphicsPixmapItem*>(m_tfGroup->childItems().first());
    if (!arrowItem) return;

    QPointF robotPos = arrowItem->pos();

    // 将视图居中到箭头位置
    ui->rosVisual->centerOn(robotPos);

    qDebug() << "View centered on robot at:" << robotPos;
}

