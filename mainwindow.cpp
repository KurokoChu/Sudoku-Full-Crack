#include <QtGui>
#include <QMessageBox>
#include <QFont>
#include <QPalette>

#include "mainwindow.h"
#include "ui_mainwindow.h"
extern "C"
{
    #include "src/solve/Sudoku.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    grid_setNum = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid_edit[i][j] = 1;
            grid_locked[i][j] = 0;
        }
    }

    setButtonNum(ui->pushButton_01, 1, 30, FALSE);
    setButtonNum(ui->pushButton_02, 2, 30, FALSE);
    setButtonNum(ui->pushButton_03, 3, 30, FALSE);
    setButtonNum(ui->pushButton_04, 4, 30, FALSE);
    setButtonNum(ui->pushButton_05, 5, 30, FALSE);
    setButtonNum(ui->pushButton_06, 6, 30, FALSE);
    setButtonNum(ui->pushButton_07, 7, 30, FALSE);
    setButtonNum(ui->pushButton_08, 8, 30, FALSE);
    setButtonNum(ui->pushButton_09, 9, 30, FALSE);

    QPushButton* controlButtons[9] = { ui->pushButton_01, ui->pushButton_02, ui->pushButton_03, ui->pushButton_04, ui->pushButton_05, ui->pushButton_06, ui->pushButton_07, ui->pushButton_08, ui->pushButton_09 };
    SudokuGrid buttonGrid = initButtonGrid();


    for (int i = 0; i < 9; i++) {
        connect(controlButtons[i], &QPushButton::clicked, [ = ]() {
            controlButtonPressed(controlButtons[i], i + 1);
        });
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            connect(buttonGrid[i][j], &QPushButton::clicked, [ = ]() {
                pushButtonPressed(buttonGrid[i][j], i + 1, j + 1);
            });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonNum(QPushButton *pushButton, int num, int size, bool onlyHover) {
    if (num == 0) {
        pushButton->setIcon(QIcon(":/src/resource/img/NumEmpty.png"));
    } else if (num >= 1 && num <= 9) {
        QString strIcon = QString::fromUtf8(":/src/resource/img/");
        strIcon.push_back(QString("Num"));
        strIcon.push_back(QChar('0' + num));
        if (onlyHover) {
            strIcon.push_back(QString("H"));
        }
        strIcon.push_back(QString(".png"));
        pushButton->setIconSize(QSize(size, size));
        pushButton->setIcon(QIcon(strIcon));
    }
}

QPushButton* MainWindow::getControlButton(int num) {
    QPushButton* numButtons[] = { ui->pushButton_01, ui->pushButton_02, ui->pushButton_03, ui->pushButton_04, ui->pushButton_05, ui->pushButton_06, ui->pushButton_07, ui->pushButton_08, ui->pushButton_09 };
    if (num >= 1 && num <= 9) {
        return numButtons[num - 1];
    }
}

void MainWindow::controlButtonPressed(QPushButton *pushButton, int num) {
    if (grid_setNum != num) {
        if (grid_setNum != 0) {
            QPushButton *pushButton_control = getControlButton(grid_setNum);
            pushButton_control->setStyleSheet("QPushButton { border:1 px solid gray; background-color: #f19b38; }");
            setButtonNum(pushButton_control, grid_setNum, 30, FALSE);
        }
        pushButton->setStyleSheet("QPushButton { border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        setButtonNum(pushButton, num, 40, TRUE);
        grid_setNum = num;
    }
    else if (grid_setNum == num) {
        if (grid_setNum != 0) {
            pushButton->setStyleSheet("QPushButton { border:1 px solid gray; background-color: #f19b38; }");
            setButtonNum(pushButton, num, 30, FALSE);
            grid_setNum = 0;
        }
    }
}

void MainWindow::pushButtonPressed(QPushButton *pushButton, int row, int col) {
    if (grid_edit[row - 1][col - 1]) {
        grid_locked[row - 1][col - 1] = grid_setNum;
        setButtonNum(pushButton, grid_setNum, 40, FALSE);
    }
}

SudokuGrid MainWindow::initButtonGrid() {
    SudokuGrid buttonGrid = {
        {   {{ ui->pushButton_11, ui->pushButton_12, ui->pushButton_13, ui->pushButton_14, ui->pushButton_15, ui->pushButton_16, ui->pushButton_17, ui->pushButton_18, ui->pushButton_19 }},
            {{ ui->pushButton_21, ui->pushButton_22, ui->pushButton_23, ui->pushButton_24, ui->pushButton_25, ui->pushButton_26, ui->pushButton_27, ui->pushButton_28, ui->pushButton_29 }},
            {{ ui->pushButton_31, ui->pushButton_32, ui->pushButton_33, ui->pushButton_34, ui->pushButton_35, ui->pushButton_36, ui->pushButton_37, ui->pushButton_38, ui->pushButton_39 }},
            {{ ui->pushButton_41, ui->pushButton_42, ui->pushButton_43, ui->pushButton_44, ui->pushButton_45, ui->pushButton_46, ui->pushButton_47, ui->pushButton_48, ui->pushButton_49 }},
            {{ ui->pushButton_51, ui->pushButton_52, ui->pushButton_53, ui->pushButton_54, ui->pushButton_55, ui->pushButton_56, ui->pushButton_57, ui->pushButton_58, ui->pushButton_59 }},
            {{ ui->pushButton_61, ui->pushButton_62, ui->pushButton_63, ui->pushButton_64, ui->pushButton_65, ui->pushButton_66, ui->pushButton_67, ui->pushButton_68, ui->pushButton_69 }},
            {{ ui->pushButton_71, ui->pushButton_72, ui->pushButton_73, ui->pushButton_74, ui->pushButton_75, ui->pushButton_76, ui->pushButton_77, ui->pushButton_78, ui->pushButton_79 }},
            {{ ui->pushButton_81, ui->pushButton_82, ui->pushButton_83, ui->pushButton_84, ui->pushButton_85, ui->pushButton_86, ui->pushButton_87, ui->pushButton_88, ui->pushButton_89 }},
            {{ ui->pushButton_91, ui->pushButton_92, ui->pushButton_93, ui->pushButton_94, ui->pushButton_95, ui->pushButton_96, ui->pushButton_97, ui->pushButton_98, ui->pushButton_99 }}
        }
    };
    return buttonGrid;
}

void MainWindow::on_allStepButton_clicked()
{
    ui->allStepButton->setStyleSheet("QPushButton { border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            if( grid_locked[i][j] != 0) {
                sudoBoard[i][j].num = grid_locked[i][j];
                grid_edit[i][j] = 0;
            }
        }
    }
    startGuide();
    SudokuGrid buttonGrid = initButtonGrid();
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            if(grid_edit[i][j] != 0) {
                setButtonNum(buttonGrid[i][j], sudoBoard[i][j].num, 40, True);
            }
        }
    }
    for(int i = 0; textGuide[i].text[0] != '\0'; i++) {
        ui->listWidget->addItem(textGuide[i].text + QString(tr("r")) + QString::number(textGuide[i].row) + QString(tr("c")) + QString::number(textGuide[i].col) + " = " + QString::number(textGuide[i].num));
    }
}
