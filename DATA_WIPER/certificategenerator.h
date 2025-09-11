#ifndef CERTIFICATEGENERATOR_H
#define CERTIFICATEGENERATOR_H

#include <QObject>
#include <QString>

class CertificateGenerator : public QObject
{
    Q_OBJECT

public:
    explicit CertificateGenerator(QObject *parent = nullptr);
    QString createCertificate(const QString& devicePath);

private:
    QString generateJSON(const QString& devicePath);
    bool createPDF(const QString& jsonData, const QString& outputPath);
    QString signData(const QString& data);
};

#endif // CERTIFICATEGENERATOR_H
