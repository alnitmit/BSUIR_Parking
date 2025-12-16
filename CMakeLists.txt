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
    Source/VehicleData.cpp
    Source/VehicleData.h
    Source/ParkingSpotData.cpp
    Source/ParkingSpotData.h
    Source/ParkingLotData.cpp
    Source/ParkingLotData.h
    Source/ParkingService.cpp
    Source/ParkingService.h
    Source/VehicleService.cpp
    Source/VehicleService.h
    Source/ParkingLotService.cpp
    Source/ParkingLotService.h
    Source/StatisticsService.cpp
    Source/StatisticsService.h
    Source/FileManager.cpp
    Source/FileManager.h
    Source/DataRepository.cpp
    Source/DataRepository.h
    Source/ParkingSystem.cpp
    Source/ParkingSystem.h
    Source/InputValidator.cpp
    Source/InputValidator.h
    Source/FilterCriteria.cpp
    Source/FilterCriteria.h
    Source/ParkingLotView.cpp
    Source/ParkingLotView.h
    Source/ModernDialog.cpp
    Source/ModernDialog.h
    Source/InputDialog.cpp
    Source/InputDialog.h
    Exceptions/InvalidLicensePlateError.cpp
    Exceptions/InvalidLicensePlateError.h
    Exceptions/InvalidTimeFormatError.cpp
    Exceptions/InvalidTimeFormatError.h
    Exceptions/InputCancelledError.cpp
    Exceptions/InputCancelledError.h
    Exceptions/DuplicateVehicleError.cpp
    Exceptions/DuplicateVehicleError.h
    Exceptions/InvalidSpotNumberError.cpp
    Exceptions/InvalidSpotNumberError.h
    Exceptions/FileIOException.cpp
    Exceptions/FileIOException.h
    Exceptions/ParkingSystemError.cpp
    Exceptions/ParkingSystemError.h
    Exceptions/VehicleNotFoundError.cpp
    Exceptions/VehicleNotFoundError.h
    Exceptions/SpotNotFoundError.cpp
    Exceptions/SpotNotFoundError.h
    Exceptions/SpotAlreadyOccupiedError.cpp
    Exceptions/SpotAlreadyOccupiedError.h
    Exceptions/SpotAlreadyFreeError.cpp
    Exceptions/SpotAlreadyFreeError.h
    Exceptions/VehicleAlreadyParkedError.cpp
    Exceptions/VehicleAlreadyParkedError.h
    Exceptions/IncompatibleSpotSizeError.cpp
    Exceptions/IncompatibleSpotSizeError.h
    Exceptions/ExportError.cpp
    Exceptions/ExportError.h
)

# Добавляем если есть
list(APPEND PROJECT_SOURCES
    Exceptions/ParkingLotNotFoundError.cpp
    Exceptions/ParkingLotNotFoundError.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pr
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
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
