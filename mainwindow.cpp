#include "mainwindow.h"
#include "VehicleData.h"
#include "ParkingLotService.h"
#include "ParkingService.h"
#include "ParkingSpotData.h"
#include "FileIOException.h"
#include "DuplicateVehicleError.h"
#include "InvalidLicensePlateError.h"
#include "VehicleNotFoundError.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>
#include <QScrollArea>
#include <QScreen>
#include <QApplication>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupConnections();
    updateParkingCombo();
    updateVehicleTable();
    updateStatistics();
    if (const QScreen* screen = QGuiApplication::primaryScreen()) {
        QRect screenGeometry = screen->availableGeometry();
        move((screenGeometry.width() - width()) / 2, (screenGeometry.height() - height()) / 2);
    }
    statsTimer = new QTimer(this);
    connect(statsTimer, &QTimer::timeout, this, &MainWindow::updateStatistics);
    statsTimer->start(5000);
}

MainWindow::~MainWindow()
{
    parkingSystem_.saveState();
}

void MainWindow::setupUI()
{
    setWindowTitle("🚗 Система управления парковкой 🅿️");
    setMinimumSize(1000, 700);
    setStyleSheet(
        "QMainWindow { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2c3e50, stop:1 #34495e); }"
        "QGroupBox { color: #ecf0f1; font-weight: bold; font-size: 12px; border: 2px solid #3498db; border-radius: 12px; margin-top: 12px; padding-top: 12px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3a536b, stop:1 #2c3e50); }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 4px 16px; background-color: #3498db; border-radius: 8px; color: white; margin-top: -12px; }"
        "QLabel { color: #ecf0f1; font-size: 12px; }"
        "QComboBox, QLineEdit { background-color: #1f2530; color: #ecf0f1; border: 2px solid #3498db; border-radius: 8px; padding: 6px; font-size: 12px; min-height: 20px; }"
        "QComboBox::drop-down { border: none; }"
        "QComboBox QAbstractItemView { background-color: #2c3e50; color: #ecf0f1; border: 1px solid #3498db; selection-background-color: #3498db; }"
        "QPushButton { color: white; font-weight: bold; border-radius: 8px; padding: 10px; font-size: 12px; border: none; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3498db, stop:1 #2980b9); }"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1abc9c, stop:1 #16a085); }"
        "QPushButton:pressed { background-color: #34495e; }"
        "QTabWidget::pane { border: 2px solid #3498db; border-radius: 8px; background-color: #2c3e50; margin-top: -1px; }"
        "QTabBar::tab { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3a536b, stop:1 #2c3e50); color: #ecf0f1; padding: 10px 20px; margin-right: 2px; border: 1px solid #3498db; border-bottom: none; border-top-left-radius: 8px; border-top-right-radius: 8px; font-weight: bold; }"
        "QTabBar::tab:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3498db, stop:1 #2980b9); color: white; }"
        "QProgressBar { border: 2px solid #3498db; border-radius: 8px; text-align: center; color: #ecf0f1; font-weight: bold; background-color: #2c3e50; height: 20px; }"
        "QProgressBar::chunk { border-radius: 6px; }"
        );
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    auto mainLayout = new QHBoxLayout(centralWidget);
    setupLeftPanel();
    setupRightPanel();
    auto splitter = new QSplitter(Qt::Horizontal, centralWidget);
    splitter->addWidget(leftPanel_.panel);
    splitter->addWidget(rightPanel_.panel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    mainLayout->addWidget(splitter);
}

void MainWindow::setupLeftPanel()
{
    leftPanel_.panel = new QWidget(this);
    auto layout = new QVBoxLayout(leftPanel_.panel);
    layout->setSpacing(16);
    layout->setContentsMargins(12, 12, 12, 12);

    auto parkingGroup = new QGroupBox(leftPanel_.panel);
    parkingGroup->setTitle("");
    auto parkingLayout = new QVBoxLayout(parkingGroup);
    auto parkingLabel = new QLabel("Выберите парковку:", parkingGroup);
    parkingLabel->setWordWrap(true);
    leftPanel_.parkingCombo = new QComboBox(parkingGroup);
    leftPanel_.btnCreateParking = new QPushButton("➕ Создать парковку", parkingGroup);
    leftPanel_.btnDeleteParking = new QPushButton("🗑️ Удалить парковку", parkingGroup);
    leftPanel_.btnCreateParking->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2ecc71, stop:1 #27ae60); }");
    leftPanel_.btnDeleteParking->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e74c3c, stop:1 #c0392b); }");
    parkingLayout->addWidget(parkingLabel);
    parkingLayout->addWidget(leftPanel_.parkingCombo);
    parkingLayout->addWidget(leftPanel_.btnCreateParking);
    parkingLayout->addWidget(leftPanel_.btnDeleteParking);

    auto vehicleGroup = new QGroupBox(leftPanel_.panel);
    vehicleGroup->setTitle("");
    auto vehicleLayout = new QVBoxLayout(vehicleGroup);
    leftPanel_.btnAddVehicle = new QPushButton("➕ Добавить транспорт", vehicleGroup);
    leftPanel_.btnRemoveVehicle = new QPushButton("🗑️ Удалить транспорт", vehicleGroup);
    leftPanel_.btnParkVehicle = new QPushButton("🅿️ Припарковать", vehicleGroup);
    leftPanel_.btnFreeSpot = new QPushButton("🔓 Освободить место", vehicleGroup);
    leftPanel_.btnAddVehicle->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3498db, stop:1 #2980b9); }");
    leftPanel_.btnRemoveVehicle->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e74c3c, stop:1 #c0392b); }");
    leftPanel_.btnParkVehicle->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #9b59b6, stop:1 #8e44ad); }");
    leftPanel_.btnFreeSpot->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f39c12, stop:1 #d35400); }");
    vehicleLayout->addWidget(leftPanel_.btnAddVehicle);
    vehicleLayout->addWidget(leftPanel_.btnRemoveVehicle);
    vehicleLayout->addWidget(leftPanel_.btnParkVehicle);
    vehicleLayout->addWidget(leftPanel_.btnFreeSpot);

    auto statsGroup = new QGroupBox(leftPanel_.panel);
    statsGroup->setTitle("");
    auto statsLayout = new QFormLayout(statsGroup);
    stats_.totalSpotsLabel = new QLabel("0", statsGroup);
    stats_.occupiedSpotsLabel = new QLabel("0", statsGroup);
    stats_.freeSpotsLabel = new QLabel("0", statsGroup);
    stats_.occupancyPercentLabel = new QLabel("0%", statsGroup);
    stats_.occupancyBar = new QProgressBar(statsGroup);
    stats_.occupancyBar->setTextVisible(true);
    statsLayout->addRow("📍 Всего мест:", stats_.totalSpotsLabel);
    statsLayout->addRow("🟥 Занято:", stats_.occupiedSpotsLabel);
    statsLayout->addRow("🟩 Свободно:", stats_.freeSpotsLabel);
    statsLayout->addRow("📈 Заполненность:", stats_.occupancyPercentLabel);
    statsLayout->addRow(stats_.occupancyBar);

    layout->addWidget(parkingGroup);
    layout->addWidget(vehicleGroup);
    layout->addWidget(statsGroup);
    layout->addStretch();
}

void MainWindow::setupRightPanel()
{
    rightPanel_.panel = new QWidget(this);
    auto layout = new QVBoxLayout(rightPanel_.panel);
    auto infoLayout = new QHBoxLayout();
    rightPanel_.parkingNameLabel = new QLabel("🏢 Парковка не выбрана");
    rightPanel_.spotsInfoLabel = new QLabel("📍 Места: -/-");
    rightPanel_.occupancyInfoLabel = new QLabel("📊 Заполненность: -");
    rightPanel_.parkingNameLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #f1f1f1;");
    rightPanel_.spotsInfoLabel->setStyleSheet("color: #bdc3c7;");
    rightPanel_.occupancyInfoLabel->setStyleSheet("color: #bdc3c7;");
    infoLayout->addWidget(rightPanel_.parkingNameLabel);
    infoLayout->addWidget(rightPanel_.spotsInfoLabel);
    infoLayout->addWidget(rightPanel_.occupancyInfoLabel);
    infoLayout->addStretch();

    rightPanel_.mainTabs = new QTabWidget(rightPanel_.panel);
    auto visualizationTab = new QWidget();
    auto vizLayout = new QVBoxLayout(visualizationTab);
    rightPanel_.parkingLotView = new ParkingLotView(visualizationTab);
    rightPanel_.parkingScrollArea = new QScrollArea(visualizationTab);
    rightPanel_.parkingScrollArea->setWidget(rightPanel_.parkingLotView);
    rightPanel_.parkingScrollArea->setWidgetResizable(true);
    vizLayout->addWidget(rightPanel_.parkingScrollArea);

    auto tableTab = new QWidget();
    auto tableLayout = new QVBoxLayout(tableTab);
    rightPanel_.vehicleTable = new QTableWidget(tableTab);
    rightPanel_.vehicleTable->setColumnCount(5);
    rightPanel_.vehicleTable->setHorizontalHeaderLabels({"🚗 Тип", "📋 Модель", "🔢 Номер", "📊 Статус", "🅿️ Парковка"});
    rightPanel_.vehicleTable->horizontalHeader()->setStretchLastSection(true);
    rightPanel_.vehicleTable->setAlternatingRowColors(true);
    rightPanel_.vehicleTable->setStyleSheet(
        "QTableWidget { background-color: #1f2530; alternate-background-color: #232a36; gridline-color: #34495e; border: 1px solid #3498db; border-radius: 8px; }"
        "QTableWidget::item { color: white; padding: 8px; border: none; border-bottom: 1px solid #34495e; }"
        "QTableWidget::item:selected { background-color: #3498db; color: white; }"
        "QHeaderView::section { background-color: #34495e; color: #ecf0f1; padding: 12px; border: none; border-right: 1px solid #2c3e50; font-weight: bold; font-size: 12px; }"
        "QHeaderView::section:last { border-right: none; }"
        "QTableCornerButton::section { background-color: #34495e; border: none; }"
        );
    tableLayout->addWidget(rightPanel_.vehicleTable);

    rightPanel_.mainTabs->addTab(visualizationTab, "🗺️ Визуализация парковки");
    rightPanel_.mainTabs->addTab(tableTab, "📋 Список транспорта");
    layout->addLayout(infoLayout);
    layout->addWidget(rightPanel_.mainTabs);
}

void MainWindow::setupConnections() const
{
    connect(leftPanel_.btnCreateParking, &QPushButton::clicked, this, &MainWindow::onCreateParking);
    connect(leftPanel_.btnDeleteParking, &QPushButton::clicked, this, &MainWindow::onDeleteParking);
    connect(leftPanel_.btnAddVehicle, &QPushButton::clicked, this, &MainWindow::onAddVehicle);
    connect(leftPanel_.btnRemoveVehicle, &QPushButton::clicked, this, &MainWindow::onRemoveVehicle);
    connect(leftPanel_.btnParkVehicle, &QPushButton::clicked, this, &MainWindow::onParkVehicle);
    connect(leftPanel_.btnFreeSpot, &QPushButton::clicked, this, &MainWindow::onFreeSpot);
    connect(leftPanel_.parkingCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onParkingLotChanged);
    connect(rightPanel_.parkingLotView, &ParkingLotView::spotClicked, this, &MainWindow::onSpotClicked);
}

void MainWindow::onCreateParking()
{
    QString name = InputDialog::getText("Создание парковки", "Введите название парковки:", "", this);
    if (name.isEmpty()) return;
    int spots = InputDialog::getInteger("Создание парковки", "Количество мест (5-40):", 25, 5, 40, this);
    if (spots == 0) return;
    try {
        if (parkingSystem_.createParkingLot(name.toStdString(), spots)) {
            ModernDialog::showSuccess("Готово", "Парковка '" + name + "' успешно создана!", this);
            updateParkingCombo();
            leftPanel_.parkingCombo->setCurrentIndex(leftPanel_.parkingCombo->count() - 1);
        } else {
            ModernDialog::showError("Ошибка", "Не удалось создать парковку", this);
        }
    } catch (const DuplicateVehicleError& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    } catch (const FileIOException& e) {
        ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
    } catch (const std::exception& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    }
}

void MainWindow::onDeleteParking()
{
    if (leftPanel_.parkingCombo->currentIndex() < 0) {
        ModernDialog::showWarning("Внимание", "Не выбрана парковка для удаления", this);
        return;
    }
    int lotId = leftPanel_.parkingCombo->currentData().toInt();
    QString lotName = leftPanel_.parkingCombo->currentText();
    bool confirmed = ModernDialog::showQuestion("Подтверждение удаления", "Вы уверены, что хотите удалить парковку:\n\"" + lotName + "\"?", this);
    if (confirmed) {
        try {
            if (parkingSystem_.removeParkingLot(lotId)) {
                ModernDialog::showSuccess("Готово", "Парковка '" + lotName + "' удалена", this);
                updateParkingCombo();
            } else {
                ModernDialog::showError("Ошибка", "Не удалось удалить парковку", this);
            }
        } catch (const FileIOException& e) {
            ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
        } catch (const std::exception& e) {
            ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
        }
    }
}

void MainWindow::onAddVehicle()
{
    QStringList types = {"🚗 Легковой автомобиль", "🚛 Грузовик"};
    QString type = InputDialog::getItem("Добавление транспорта", "Тип транспорта:", types, 0, this);
    if (type.isEmpty()) return;
    QString licensePlate = InputDialog::getText("Добавление транспорта", "Номерной знак:", "", this);
    if (licensePlate.isEmpty()) return;
    if (!InputValidator::isValidLicensePlate(licensePlate)) {
        ModernDialog::showError("Неверный номер", "Формат номерного знака неверен", this);
        return;
    }
    licensePlate = InputValidator::formatLicensePlate(licensePlate);
    try {
        VehicleData vehicle;
        if (type == "🚗 Легковой автомобиль") {
            QString model = InputDialog::getText("Добавление автомобиля", "Модель автомобиля:", "", this);
            if (model.isEmpty()) return;
            vehicle.setType("Car");
            vehicle.setModel(model.toStdString());
            vehicle.setLicensePlate(licensePlate.toStdString());
        } else {
            QString cargoType = InputDialog::getText("Добавление грузовика", "Тип груза:", "", this);
            if (cargoType.isEmpty()) return;
            vehicle.setType("Truck");
            vehicle.setModel("Грузовик (" + cargoType.toStdString() + ")");
            vehicle.setLicensePlate(licensePlate.toStdString());
            vehicle.setCargoType(cargoType.toStdString());
        }
        if (parkingSystem_.addVehicle(vehicle)) {
            ModernDialog::showSuccess("Готово", "Транспорт успешно добавлен", this);
            updateVehicleTable();
        } else {
            ModernDialog::showWarning("Внимание", "Транспорт с таким номером уже существует", this);
        }
    } catch (const DuplicateVehicleError& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    } catch (const FileIOException& e) {
        ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
    } catch (const std::exception& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    }
}

void MainWindow::onRemoveVehicle()
{
    if (rightPanel_.vehicleTable->currentRow() < 0) {
        ModernDialog::showWarning("Внимание", "Не выбран транспорт для удаления", this);
        return;
    }
    QString licensePlate = rightPanel_.vehicleTable->item(rightPanel_.vehicleTable->currentRow(), 2)->text();
    bool confirmed = ModernDialog::showQuestion("Подтверждение удаления", "Удалить транспорт:\n\"" + licensePlate + "\"?", this);
    if (confirmed) {
        try {
            if (parkingSystem_.removeVehicle(licensePlate.toStdString())) {
                ModernDialog::showSuccess("Готово", "Транспорт '" + licensePlate + "' удален", this);
                updateVehicleTable();
                updateParkingView();
            } else {
                ModernDialog::showError("Ошибка", "Транспорт не найден", this);
            }
        } catch (const VehicleNotFoundError& e) {
            ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
        } catch (const FileIOException& e) {
            ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
        } catch (const std::exception& e) {
            ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
        }
    }
}

void MainWindow::onParkVehicle()
{
    if (rightPanel_.vehicleTable->currentRow() < 0) {
        ModernDialog::showWarning("Внимание", "Не выбран транспорт для парковки", this);
        return;
    }
    if (leftPanel_.parkingCombo->currentIndex() < 0) {
        ModernDialog::showWarning("Внимание", "Не выбрана парковка", this);
        return;
    }
    QString licensePlate = rightPanel_.vehicleTable->item(rightPanel_.vehicleTable->currentRow(), 2)->text();
    int lotId = leftPanel_.parkingCombo->currentData().toInt();
    int spotNumber = InputDialog::getInteger("Парковка транспорта", "Номер места (1-40):", 1, 1, 40, this);
    if (spotNumber == 0) return;
    try {
        if (parkingSystem_.parkVehicle(licensePlate.toStdString(), lotId, spotNumber)) {
            ModernDialog::showSuccess("Готово", "Припарковали на месте " + QString::number(spotNumber), this);
            updateVehicleTable();
            updateParkingView();
            updateStatistics();
        }
    } catch (const VehicleNotFoundError&) {
        ModernDialog::showError("Ошибка", "Транспорт не найден", this);
    } catch (const SpotNotFoundError&) {
        ModernDialog::showError("Ошибка", "Место не найдено", this);
    } catch (const SpotAlreadyOccupiedError&) {
        ModernDialog::showWarning("Занято", "Место уже занято", this);
    } catch (const VehicleAlreadyParkedError&) {
        ModernDialog::showWarning("Внимание", "Транспорт уже припаркован", this);
    } catch (const IncompatibleSpotSizeError&) {
        ModernDialog::showError("Ошибка", "Несовместимое место", this);
    } catch (const FileIOException& e) {
        ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
    } catch (const std::exception& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    }
}

void MainWindow::onFreeSpot()
{
    if (leftPanel_.parkingCombo->currentIndex() < 0) {
        ModernDialog::showWarning("Внимание", "Не выбрана парковка", this);
        return;
    }
    int spotNumber = InputDialog::getInteger("Освобождение места", "Номер места (1-40):", 1, 1, 40, this);
    if (spotNumber == 0) return;
    int lotId = leftPanel_.parkingCombo->currentData().toInt();
    try {
        if (parkingSystem_.releaseSpot(lotId, spotNumber)) {
            ModernDialog::showSuccess("Готово", "Место " + QString::number(spotNumber) + " освобождено", this);
            updateVehicleTable();
            updateParkingView();
            updateStatistics();
        }
    } catch (const SpotNotFoundError&) {
        ModernDialog::showError("Ошибка", "Место не найдено", this);
    } catch (const SpotAlreadyFreeError&) {
        ModernDialog::showInfo("Информация", "Место уже свободно", this);
    } catch (const FileIOException& e) {
        ModernDialog::showError("Ошибка файла", QString::fromUtf8(e.what()), this);
    } catch (const std::exception& e) {
        ModernDialog::showError("Ошибка", QString::fromUtf8(e.what()), this);
    }
}

void MainWindow::onSpotClicked(int spotNumber)
{
    const auto* lot = parkingSystem_.getParkingLot(leftPanel_.parkingCombo->currentData().toInt());
    if (!lot) return;
    const ParkingSpotData* spot = ParkingService::findSpot(*lot, spotNumber);
    if (!spot) {
        ModernDialog::showInfo("Информация", "Место " + QString::number(spotNumber) + " не найдено", this);
        return;
    }
    QString info = QString("📍 Место %1\n\n").arg(spotNumber);
    info += QString("📊 Статус: %1\n").arg(spot->isOccupied() ? "🟥 Занято" : "🟩 Свободно");
    if (spot->isOccupied() && !spot->getVehicleLicensePlate().empty()) {
        const VehicleData* vehicle = parkingSystem_.findVehicle(spot->getVehicleLicensePlate());
        if (vehicle) {
            info += QString("\n🚗 Транспорт: %1\n").arg(QString::fromStdString(vehicle->getModel()));
            info += QString("🔢 Номер: %1\n").arg(QString::fromStdString(vehicle->getLicensePlate()));
            info += QString("📋 Тип: %1").arg(QString::fromStdString(vehicle->getType()));
        }
    }
    ModernDialog::showInfo("Информация о месте", info, this);
}

void MainWindow::onParkingLotChanged(int index)
{
    if (index >= 0) {
        updateParkingView();
        updateStatistics();
    }
}

void MainWindow::updateVehicleTable() const
{
    rightPanel_.vehicleTable->setRowCount(0);
    const auto& vehicles = parkingSystem_.getVehicles();
    for (const auto& vehicle : vehicles) {
        int row = rightPanel_.vehicleTable->rowCount();
        rightPanel_.vehicleTable->insertRow(row);
        auto typeItem = new QTableWidgetItem(QString::fromStdString(vehicle.getType()));
        auto modelItem = new QTableWidgetItem(QString::fromStdString(vehicle.getModel()));
        auto plateItem = new QTableWidgetItem(QString::fromStdString(vehicle.getLicensePlate()));
        QString statusText = vehicle.isParked() ? "🟥 Припаркован" : "🟩 Свободен";
        auto statusItem = new QTableWidgetItem(statusText);
        typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        modelItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        plateItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        statusItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        typeItem->setForeground(Qt::white);
        modelItem->setForeground(Qt::white);
        plateItem->setForeground(Qt::white);
        statusItem->setForeground(vehicle.isParked() ? QColor("#e74c3c") : QColor("#27ae60"));
        rightPanel_.vehicleTable->setItem(row, 0, typeItem);
        rightPanel_.vehicleTable->setItem(row, 1, modelItem);
        rightPanel_.vehicleTable->setItem(row, 2, plateItem);
        rightPanel_.vehicleTable->setItem(row, 3, statusItem);

        QString parkingInfo = "❌ Не припаркован";
        if (vehicle.isParked()) {
            parkingInfo = findVehicleParkingSpot(vehicle);
        }
        auto parkingItem = new QTableWidgetItem(parkingInfo);
        parkingItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        parkingItem->setForeground(Qt::white);
        rightPanel_.vehicleTable->setItem(row, 4, parkingItem);
    }
    rightPanel_.vehicleTable->resizeColumnsToContents();
    for (int i = 0; i < rightPanel_.vehicleTable->columnCount(); ++i) {
        int width = rightPanel_.vehicleTable->columnWidth(i);
        rightPanel_.vehicleTable->setColumnWidth(i, width + 20);
    }
    rightPanel_.vehicleTable->verticalHeader()->setDefaultSectionSize(35);
    rightPanel_.vehicleTable->verticalHeader()->setVisible(false);
}

QString MainWindow::findVehicleParkingSpot(const VehicleData& vehicle) const
{
    for (const auto& [lotId, lot] : parkingSystem_.getParkingLots()) {
        for (const auto& spot : lot.getSpots()) {
            if (spot.isOccupied() && spot.getVehicleLicensePlate() == vehicle.getLicensePlate()) {
                return QString::fromStdString(lot.getName()) + " 🅿️ Место " + QString::number(spot.getNumber());
            }
        }
    }
    return "❌ Не припаркован";
}

void MainWindow::updateParkingCombo()
{
    leftPanel_.parkingCombo->clear();
    const auto& lots = parkingSystem_.getParkingLots();
    for (const auto& [lotId, lot] : lots) {
        leftPanel_.parkingCombo->addItem("🅿️ " + QString::fromStdString(lot.getName()), lotId);
    }
    if (leftPanel_.parkingCombo->count() > 0) {
        leftPanel_.parkingCombo->setCurrentIndex(0);
    }
}

void MainWindow::updateParkingView()
{
    if (leftPanel_.parkingCombo->currentIndex() < 0) return;
    int lotId = leftPanel_.parkingCombo->currentData().toInt();
    const auto* lot = parkingSystem_.getParkingLot(lotId);
    if (!lot) return;
    rightPanel_.parkingNameLabel->setText("🏢 " + QString::fromStdString(lot->getName()));
    int occupied = ParkingLotService::getOccupiedSpots(*lot);
    auto total = static_cast<int>(lot->getSpots().size());
    double occupancy = ParkingLotService::getOccupancyRate(*lot);
    rightPanel_.spotsInfoLabel->setText(QString("📍 Места: %1/%2").arg(occupied).arg(total));
    rightPanel_.occupancyInfoLabel->setText(QString("📊 Заполненность: %1%").arg(occupancy, 0, 'f', 1));
    QVector<ParkingSpotVisual> spots;
    spots.reserve(lot->getSpots().size());
    for (const auto& spot : lot->getSpots()) {
        ParkingSpotVisual visual;
        visual.number = spot.getNumber();
        visual.occupied = spot.isOccupied();
        if (visual.occupied && !spot.getVehicleLicensePlate().empty()) {
            const VehicleData* vehicle = parkingSystem_.findVehicle(spot.getVehicleLicensePlate());
            if (vehicle) {
                visual.vehicleType = QString::fromStdString(vehicle->getType());
                visual.licensePlate = QString::fromStdString(vehicle->getLicensePlate());
            }
        }
        spots.append(visual);
    }
    rightPanel_.parkingLotView->setSpots(spots);
    rightPanel_.parkingLotView->setParkingName(QString::fromStdString(lot->getName()));
}

void MainWindow::updateStatistics()
{
    stats_.totalSpotsLabel->setText(QString::number(parkingSystem_.getTotalSpots()));
    stats_.occupiedSpotsLabel->setText(QString::number(parkingSystem_.getOccupiedSpots()));
    stats_.freeSpotsLabel->setText(QString::number(parkingSystem_.getFreeSpots()));
    double occupancyRate = parkingSystem_.getOccupancyRate();
    stats_.occupancyPercentLabel->setText(QString("%1%").arg(occupancyRate, 0, 'f', 1));
    auto val = static_cast<int>(occupancyRate);
    stats_.occupancyBar->setValue(val);
    if (val < 50) {
        stats_.occupancyBar->setStyleSheet("QProgressBar::chunk { background-color: #27ae60; border-radius: 6px; }");
    } else if (val < 80) {
        stats_.occupancyBar->setStyleSheet("QProgressBar::chunk { background-color: #f39c12; border-radius: 6px; }");
    } else {
        stats_.occupancyBar->setStyleSheet("QProgressBar::chunk { background-color: #e74c3c; border-radius: 6px; }");
    }
    if (leftPanel_.parkingCombo->currentIndex() >= 0) {
        updateParkingView();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    parkingSystem_.saveState();
    event->accept();
}
