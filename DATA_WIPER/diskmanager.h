#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <QObject>
#include <QString>

class DiskManager : public QObject
{
    Q_OBJECT

public:
    explicit DiskManager(QObject *parent = nullptr);
    void startWipe(const QString& drivePath);

signals:
    void progressUpdated(int progress);
    void wipeCompleted(bool success, const QString& certificatePath);

private:
    void performSecureWipe(const QString& drivePath);
    void generateCertificate(const QString& drivePath);
};

#endif // DISKMANAGER_H
