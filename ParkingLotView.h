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
    void drawSpot(QPainter &painter, const ParkingSpotVisual &spot, const QRect &rect);
    void drawParkingLayout(QPainter &painter);

    QVector<ParkingSpotVisual> spots_;
    QString parkingName_;
    int columns_;
    int spotWidth_;
    int spotHeight_;
    int horizontalSpacing_;
    int verticalSpacing_;
    int margin_;
};

#endif // PARKINGLOTVIEW_H
