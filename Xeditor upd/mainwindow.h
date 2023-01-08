#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void open();
    void save();
    void exit();
    void about();
    void copy();
    void paste();
    void clear();
    void undo();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
