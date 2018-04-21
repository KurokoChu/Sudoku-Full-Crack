#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidgetItem>

using SudokuGrid = std::array<std::array<QPushButton*, 9>, 9>;

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
    void pushButtonPressed(QPushButton *pushButton, int row, int col);
    void controlButtonPressed(QPushButton *pushButton, int num);
    void on_allStepButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    int grid_edit[9][9];
    int grid_locked[9][9];
    int grid_setNum;
    SudokuGrid buttonGrid;

    QPushButton* getControlButton(int num);
    void setButtonNum(QPushButton *pushButton, int num, int size, bool onlyHover);
    SudokuGrid initButtonGrid();

};

#endif // MAINWINDOW_H
