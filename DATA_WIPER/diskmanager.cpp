#include "diskmanager.h"
#include "certificategenerator.h" // A separate class for certificate creation
#include <QFile>
#include <QThread>
#include <QDebug>

DiskManager::DiskManager(QObject *parent) : QObject(parent) {}

void DiskManager::startWipe(const QString& drivePath)
{
    // Use QThread to run the heavy operation in the background
    QThread *thread = new QThread;
    this->moveToThread(thread);

    connect(thread, &QThread::started, this, [=]() {
        performSecureWipe(drivePath);
    });
    connect(this, &DiskManager::wipeCompleted, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}

void DiskManager::performSecureWipe(const QString& drivePath)
{
    qDebug() << "Starting secure wipe on" << drivePath;
    // Open the device in raw mode (platform-specific)
    // Windows: Use CreateFile with \\.\PhysicalDriveX
    // Linux: Open("/dev/sdX")
    // Android: Open("/dev/block/...") (requires root)

    // For demonstration, we'll simulate the process
    QFile device(drivePath);
    if (device.open(QIODevice::WriteOnly)) {
        // Implement the NIST SP 800-88 compliant algorithm
        // For HDDs: overwrite passes
        // For SSDs: issue ATA Secure Erase command
        // This part needs platform-specific C++ libraries or system calls
        // For example, on Linux, you'd write a loop to open the device file
        // and write data to it.
        qint64 totalSize = device.size();
        qint64 wipedSize = 0;

        // Example: simulate a 3-pass overwrite
        for (int pass = 1; pass <= 3; ++pass) {
            // Write random data or a fixed pattern
            QByteArray data(4096, 0); // Example zero fill
            qint64 bytesWritten = 0;
            while (bytesWritten < totalSize) {
                // write logic here
                bytesWritten += 4096;
                wipedSize = (pass - 1) * totalSize + bytesWritten;
                int progress = static_cast<int>((static_cast<double>(wipedSize) / (3.0 * totalSize)) * 100);
                emit progressUpdated(progress);
                QThread::msleep(10); // Simulate work
            }
        }
        device.close();

        // Handle ATA Secure Erase for SSDs by issuing commands via ioctl
        // Handle HPA/DCO by unhiding them before wiping.

        qDebug() << "Wipe successful.";
        generateCertificate(drivePath);
    } else {
        qDebug() << "Failed to open device:" << device.errorString();
        emit wipeCompleted(false, "");
    }
}

void DiskManager::generateCertificate(const QString& drivePath)
{
    CertificateGenerator certGen;
    QString certPath = certGen.createCertificate(drivePath);
    emit wipeCompleted(true, certPath);
}
