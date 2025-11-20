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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void updateVehicleTable();
    void updateParkingCombo();
    void updateParkingView();
    void closeEvent(QCloseEvent *event) override;

    QWidget *leftPanel;
    QComboBox *parkingCombo;
    QPushButton *btnCreateParking;
    QPushButton *btnDeleteParking;
    QPushButton *btnAddVehicle;
    QPushButton *btnRemoveVehicle;
    QPushButton *btnParkVehicle;
    QPushButton *btnFreeSpot;

    QLabel *totalSpotsLabel;
    QLabel *occupiedSpotsLabel;
    QLabel *freeSpotsLabel;
    QLabel *occupancyPercentLabel;
    QProgressBar *occupancyBar;

    QWidget *rightPanel;
    QLabel *parkingNameLabel;
    QLabel *spotsInfoLabel;
    QLabel *occupancyInfoLabel;
    QTableWidget *vehicleTable;
    QTabWidget *mainTabs;

    ParkingSystem parkingSystem_;

    ParkingLotView *parkingLotView;
    QScrollArea *parkingScrollArea;

    QTimer *statsTimer;
};

#endif
