#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QProgressBar>
#include <QGroupBox>
#include <QSplitter>
#include <QTimer>
#include <QHeaderView>
#include <QTabWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QScrollArea>
#include "ParkingLotView.h"
#include "ParkingSystem.h"
#include "VehicleData.h"
#include "InputValidator.h"
#include "ModernDialog.h"
#include "InputDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onCreateParking();
    void onDeleteParking();
    void onAddVehicle();
    void onRemoveVehicle();
    void onParkVehicle();
    void onFreeSpot();
    void onSpotClicked(int spotNumber);
    void onParkingLotChanged(int index);
    void updateStatistics();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupConnections() const;
    void updateVehicleTable() const;
    void updateParkingCombo();
    void updateParkingView();
    void closeEvent(QCloseEvent *event) override;
    QString findVehicleParkingSpot(const VehicleData& vehicle) const;

    // Структуры для организации виджетов
    struct LeftPanelWidgets {
        QWidget* panel = nullptr;
        QComboBox* parkingCombo = nullptr;
        QPushButton* btnCreateParking = nullptr;
        QPushButton* btnDeleteParking = nullptr;
        QPushButton* btnAddVehicle = nullptr;
        QPushButton* btnRemoveVehicle = nullptr;
        QPushButton* btnParkVehicle = nullptr;
        QPushButton* btnFreeSpot = nullptr;
    };

    struct StatsWidgets {
        QLabel* totalSpotsLabel = nullptr;
        QLabel* occupiedSpotsLabel = nullptr;
        QLabel* freeSpotsLabel = nullptr;
        QLabel* occupancyPercentLabel = nullptr;
        QProgressBar* occupancyBar = nullptr;
    };

    struct RightPanelWidgets {
        QWidget* panel = nullptr;
        QLabel* parkingNameLabel = nullptr;
        QTableWidget* vehicleTable = nullptr;
        QTabWidget* mainTabs = nullptr;
        ParkingLotView* parkingLotView = nullptr;
        QScrollArea* parkingScrollArea = nullptr;
    };

    // Объявление переменных-членов
    LeftPanelWidgets leftPanel_;
    StatsWidgets stats_;
    RightPanelWidgets rightPanel_;
    ParkingSystem parkingSystem_;
    QTimer* statsTimer = nullptr;
};

#endif
