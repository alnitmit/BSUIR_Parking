#include "ParkingLotView.h"
#include <QPainter>
#include <QLinearGradient>
#include <QFontMetrics>
#include <cmath>

ParkingLotView::ParkingLotView(QWidget *parent)
    : QWidget(parent)  // Исправлено: удалены инициализации из списка
{
    setMinimumSize(800, 600);
    setStyleSheet("background-color: #2b2f3a;");
}

void ParkingLotView::setSpots(const QVector<ParkingSpotVisual>& spots) {
    spots_ = spots;
    calculateLayout();
    update();
}

void ParkingLotView::setParkingName(const QString& name) {
    parkingName_ = name;
    update();
}

void ParkingLotView::calculateLayout() {
    if (spots_.isEmpty()) return;

    int availableWidth = width() - 2 * margin_;
    columns_ = std::max(2, availableWidth / (spotWidth_ + horizontalSpacing_));

    int rows = (spots_.size() + columns_ - 1) / columns_;
    int requiredHeight = 2 * margin_ + rows * (spotHeight_ + verticalSpacing_);

    setMinimumHeight(requiredHeight);
}

QRect ParkingLotView::getSpotRect(int index) const {
    if (spots_.isEmpty() || index < 0 || index >= spots_.size())
        return QRect();

    int row = index / columns_;
    int col = index % columns_;

    int x = margin_ + col * (spotWidth_ + horizontalSpacing_);
    int y = margin_ + 40 + row * (spotHeight_ + verticalSpacing_);

    return QRect(x, y, spotWidth_, spotHeight_);
}

void ParkingLotView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(43, 47, 58));

    QLinearGradient titleGradient(0, 0, width(), 0);
    titleGradient.setColorAt(0, QColor(52, 152, 219));
    titleGradient.setColorAt(1, QColor(155, 89, 182));

    painter.setPen(Qt::NoPen);
    painter.setBrush(titleGradient);
    painter.drawRoundedRect(10, 10, width() - 20, 30, 8, 8);

    painter.setPen(QColor(255, 255, 255));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(QRect(10, 10, width() - 20, 30), Qt::AlignCenter, parkingName_.isEmpty() ? "Парковка" : parkingName_);

    for (int i = 0; i < spots_.size(); ++i) {
        QRect spotRect = getSpotRect(i);
        if (spotRect.isValid()) {
            drawSpot(painter, spots_[i], spotRect);
        }
    }

    drawParkingLayout(painter);
}

void ParkingLotView::drawSpot(QPainter &painter, const ParkingSpotVisual &spot, const QRect &rect) const {  // Исправлено: const
    QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());

    if (spot.occupied) {
        gradient.setColorAt(0, QColor(231, 76, 60));
        gradient.setColorAt(1, QColor(192, 57, 43));
    } else {
        gradient.setColorAt(0, QColor(46, 204, 113));
        gradient.setColorAt(1, QColor(39, 174, 96));
    }

    painter.setPen(QPen(QColor(255, 255, 255, 150), 2));
    painter.setBrush(gradient);
    painter.drawRoundedRect(rect, 12, 12);

    painter.setPen(QColor(255, 255, 255));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(rect, Qt::AlignTop | Qt::AlignHCenter, QString::number(spot.number));

    QString status = spot.occupied ? "ЗАНЯТО" : "СВОБОДНО";
    painter.setFont(QFont("Arial", 9, QFont::Normal));
    painter.drawText(rect.adjusted(5, 20, -5, -20), Qt::AlignTop | Qt::AlignHCenter, status);

    if (spot.occupied) {
        painter.setFont(QFont("Arial", 8, QFont::Normal));

        QString typeIcon = spot.vehicleType == "Truck" ? "🚛" : "🚗";
        painter.drawText(rect.adjusted(5, 35, -5, -10), Qt::AlignTop | Qt::AlignHCenter, typeIcon);

        QString plate = spot.licensePlate;
        if (plate.length() > 8) {
            plate = plate.left(6) + "...";
        }
        painter.drawText(rect.adjusted(5, 55, -5, -5), Qt::AlignBottom | Qt::AlignHCenter, plate);
    }

    if (rect.contains(mapFromGlobal(QCursor::pos()))) {
        painter.setPen(QPen(QColor(255, 255, 255), 3));
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(rect.adjusted(2, 2, -2, -2), 10, 10);
    }
}

void ParkingLotView::drawParkingLayout(QPainter &painter) const {  // Исправлено: const
    if (spots_.isEmpty()) return;

    painter.setPen(QPen(QColor(149, 165, 166, 100), 4));
    painter.setBrush(QColor(52, 73, 94, 80));

    int rows = (spots_.size() + columns_ - 1) / columns_;

    for (int row = 0; row < rows - 1; ++row) {
        int y = margin_ + 40 + (row + 1) * (spotHeight_ + verticalSpacing_) - verticalSpacing_ / 2;
        painter.drawLine(margin_, y, width() - margin_, y);
    }

    painter.setPen(QPen(QColor(255, 255, 255, 50), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(margin_ - 5, margin_ + 35,
                            width() - 2 * margin_ + 10,
                            height() - margin_ - 35, 15, 15);
}

void ParkingLotView::mousePressEvent(QMouseEvent *event) {
    for (int i = 0; i < spots_.size(); ++i) {
        QRect spotRect = getSpotRect(i);
        if (spotRect.contains(event->pos())) {
            emit spotClicked(spots_[i].number);
            break;
        }
    }
}

void ParkingLotView::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    calculateLayout();
    update();
}
