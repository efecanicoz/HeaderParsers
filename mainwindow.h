#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFontDatabase>
#include <EInterface.h>
#include <fileReader.h>
#include <qstringlistmodel.h>
#include <iomanip>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sectionListView_doubleClicked(const QModelIndex &index);

private:
    QString format_for_hex_view(std::vector<uint8_t>);
    QString format_for_ascii_view(std::vector<uint8_t>);
    Ui::MainWindow *ui;
    QString exePath;
    ExecutableFile *exeObj;
};

#endif // MAINWINDOW_H
