cmake_minimum_required(VERSION 3.16)

project(pr VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    VehicleData.h
    VehicleData.cpp
    ParkingSpotData.h
    ParkingSpotData.cpp
    ParkingLotData.h
    ParkingLotData.cpp
    ParkingService.h
    ParkingService.cpp
    VehicleService.h
    VehicleService.cpp
    ParkingLotService.h
    ParkingLotService.cpp
    StatisticsService.h
    StatisticsService.cpp
    FileManager.h
    FileManager.cpp
    DataRepository.h
    DataRepository.cpp
    ParkingSystem.h
    ParkingSystem.cpp
    InputValidator.h
    InputValidator.cpp
    FilterCriteria.h
    FilterCriteria.cpp
    ParkingLotView.h
    ParkingLotView.cpp
    ModernDialog.h
    ModernDialog.cpp
    InputDialog.h
    InputDialog.cpp
    InvalidLicensePlateError.h
    InvalidLicensePlateError.cpp
    InvalidTimeFormatError.h
    InvalidTimeFormatError.cpp
    InputCancelledError.h
    InputCancelledError.cpp
    DuplicateVehicleError.h
    DuplicateVehicleError.cpp
    InvalidSpotNumberError.h
    InvalidSpotNumberError.cpp
    FileIOException.h
    FileIOException.cpp
    ParkingSystemError.h
    ParkingSystemError.cpp
    VehicleNotFoundError.h
    VehicleNotFoundError.cpp
    SpotNotFoundError.h
    SpotNotFoundError.cpp
    SpotAlreadyOccupiedError.h
    SpotAlreadyOccupiedError.cpp
    SpotAlreadyFreeError.h
    SpotAlreadyFreeError.cpp
    VehicleAlreadyParkedError.h
    VehicleAlreadyParkedError.cpp
    IncompatibleSpotSizeError.h
    IncompatibleSpotSizeError.cpp
    ExportError.h
    ExportError.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pr
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ParkingLotNotFoundError.h ParkingLotNotFoundError.cpp
    )
else()
    if(ANDROID)
        add_library(pr SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(pr
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(pr PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.pr)
endif()
set_target_properties(pr PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS pr
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pr)
endif()
