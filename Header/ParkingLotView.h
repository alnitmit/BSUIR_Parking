#ifndef PARKINGLOTVIEW_H
#define PARKINGLOTVIEW_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QLinearGradient>

struct ParkingSpotVisual {
    int number;
    bool occupied;
    QString vehicleType;
    QString licensePlate;
};

class ParkingLotView : public QWidget {
    Q_OBJECT

public:
    explicit ParkingLotView(QWidget *parent = nullptr);
    void setSpots(const QVector<ParkingSpotVisual>& spots);
    void setParkingName(const QString& name);

signals:
    void spotClicked(int spotNumber);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void calculateLayout();
    QRect getSpotRect(int index) const;
    void drawSpot(QPainter &painter, const ParkingSpotVisual &spot, const QRect &rect) const;  // Исправлено: const
    void drawParkingLayout(QPainter &painter) const;  // Исправлено: const

    QVector<ParkingSpotVisual> spots_;
    QString parkingName_;
    int columns_ = 5;  // Исправлено: инициализация в классе
    int spotWidth_ = 120;
    int spotHeight_ = 80;
    int horizontalSpacing_ = 15;
    int verticalSpacing_ = 15;
    int margin_ = 20;
};

#endif // PARKINGLOTVIEW_H
