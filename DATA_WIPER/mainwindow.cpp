#include "mainwindow.h"
#include "diskmanager.h" // Our backend class
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug> // <-- ADDED: For printing messages

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup UI
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    driveList = new QListWidget(this);
    layout->addWidget(driveList);

    wipeButton = new QPushButton("Secure Wipe Selected Drive", this);
    layout->addWidget(wipeButton);

    // Connect signals and slots
    connect(wipeButton, &QPushButton::clicked, this, &MainWindow::wipeSelectedDrive);

    // Initial drive detection
    detectDrives();
}

// ADDED: The missing destructor implementation
MainWindow::~MainWindow()
{
}

void MainWindow::detectDrives()
{
    // Placeholder for actual disk detection logic
    driveList->clear();
    // In a real app, this would call a backend function to list drives
    driveList->addItem("C: (Windows - 500 GB)");
    driveList->addItem("/dev/sda (Linux - 1 TB)");
    driveList->addItem("eMMC (Android - 64 GB)");
}

void MainWindow::wipeSelectedDrive()
{
    if (driveList->currentItem() == nullptr) {
        QMessageBox::warning(this, "No Drive Selected", "Please select a drive to wipe.");
        return;
    }

    QString selectedDrive = driveList->currentItem()->text();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Wipe", "WARNING: This will permanently erase all data on " + selectedDrive + ". Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Start the wipe process in a separate thread to keep the UI responsive
        DiskManager *manager = new DiskManager(this);
        connect(manager, &DiskManager::progressUpdated, this, &MainWindow::showProgress);
        connect(manager, &DiskManager::wipeCompleted, this, &MainWindow::wipeComplete);
        manager->startWipe(selectedDrive);
        wipeButton->setEnabled(false); // Disable button during wipe
    }
}

// ADDED: The missing slot implementation for progress
void MainWindow::showProgress(int progress)
{
    // In a real app, you would update a QProgressBar here.
    qDebug() << "Wipe progress:" << progress << "%";
    this->setWindowTitle("Wiping in progress... " + QString::number(progress) + "%");
}

// ADDED: The missing slot implementation for completion
void MainWindow::wipeComplete(bool success, const QString& certificatePath)
{
    this->setWindowTitle("DATA WIPER");
    wipeButton->setEnabled(true); // Re-enable button
    if (success) {
        QMessageBox::information(this, "Success", "The drive has been wiped successfully.\nCertificate at: " + certificatePath);
    } else {
        QMessageBox::critical(this, "Error", "The wipe process failed.");
    }
}
