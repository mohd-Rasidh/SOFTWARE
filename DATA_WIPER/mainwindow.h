#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void detectDrives();
    void wipeSelectedDrive();
    void showProgress(int progress);
    void wipeComplete(bool success, const QString& certificatePath);

private:
    QListWidget *driveList;
    QPushButton *wipeButton;
    // Other UI elements like progress bar, status labels
};

#endif // MAINWINDOW_H
