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
    explicit MainWindow(QWidget *parent = nullptr);  // Исправлено: explicit
    ~MainWindow() override;  // Исправлено: override

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
    void setupConnections();
    void updateVehicleTable() const;  // Исправлено: const
    void updateParkingCombo();
    void updateParkingView();
    void closeEvent(QCloseEvent *event) override;

    // Основные виджеты
    QWidget *leftPanel = nullptr;
    QComboBox *parkingCombo = nullptr;
    QPushButton *btnCreateParking = nullptr;
    QPushButton *btnDeleteParking = nullptr;
    QPushButton *btnAddVehicle = nullptr;
    QPushButton *btnRemoveVehicle = nullptr;
    QPushButton *btnParkVehicle = nullptr;
    QPushButton *btnFreeSpot = nullptr;

    // Статистика
    QLabel *totalSpotsLabel = nullptr;
    QLabel *occupiedSpotsLabel = nullptr;
    QLabel *freeSpotsLabel = nullptr;
    QLabel *occupancyPercentLabel = nullptr;
    QProgressBar *occupancyBar = nullptr;

    // Правая панель
    QWidget *rightPanel = nullptr;
    QLabel *parkingNameLabel = nullptr;
    QLabel *spotsInfoLabel = nullptr;
    QLabel *occupancyInfoLabel = nullptr;
    QTableWidget *vehicleTable = nullptr;
    QTabWidget *mainTabs = nullptr;

    ParkingSystem parkingSystem_;

    ParkingLotView *parkingLotView = nullptr;
    QScrollArea *parkingScrollArea = nullptr;

    QTimer *statsTimer = nullptr;
};

#endif
