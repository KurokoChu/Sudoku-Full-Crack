#include <QtGui>
#include <QMessageBox>
#include <QFont>
#include <QString>

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

    this->setMinimumSize(1080, 810);
    this->setMaximumSize(1080, 810);

    Setup();
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdNumber->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgb(0, 0, 0, 0);");


    grid_setNum = 0;
    is_clickedAllStep = FALSE;
    is_inValid = FALSE;
    is_noSolution = FALSE;
    is_gameStart = FALSE;
    is_gameStop = TRUE;
    is_clear = FALSE;
    optionCandidate = TRUE;
    sameRandom = -1;
    timer = new QTimer(this);
    timer_second = 0;
    timer_minute = 0;

    grid_edited = MemoryManage_2D(9, 9);
    grid_step = MemoryManage_2D(9, 9);
    grid_locked = MemoryManage_2D(9, 9);
    grid_merge = MemoryManage_2D(9, 9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid_edit[i][j] = 1;
        }
    }

    buttonGrid = initButtonGrid();
    for (int i = 0; i < 9; i++) {
        controlButtons[i] = getControlButton(i + 1);
        setButtonNum(controlButtons[i], i + 1, 30, FALSE);
        connect(controlButtons[i], &QPushButton::clicked, [ = ]() { controlButtonPressed(controlButtons[i], i + 1); });
        for (int j = 0; j < 9; j++) {
            connect(buttonGrid[i][j], &QPushButton::clicked, [ = ]() { pushButtonPressed(buttonGrid[i][j], i + 1, j + 1); });
        }
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(timeCount()));

    if (optionCandidate == TRUE) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                Update_Board(grid_merge, i, j);
            }
        }
        gridCandidate(grid_merge);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonNum(QPushButton *pushButton, int num, int size, bool onlyHover) {
    if (num == 0) {
        pushButton->setIcon(QIcon(""));
    }
    else if (num >= 1 && num <= 9) {
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
    return NULL;
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
    if (is_noSolution == FALSE && is_inValid == FALSE) {
        if (is_gameStart == FALSE) {
            if (is_clickedAllStep == TRUE) {
                for(int i = 0; i < 9; ++i) {
                    for(int j = 0; j < 9; ++j) {
                        grid_edit[i][j] = 0;
                    }
                }
            }
            if (grid_edit[row - 1][col - 1]) {
                if(grid_setNum == grid_locked[row - 1][col - 1]) {
                    setButtonNum(pushButton, 0, 40, FALSE);
                    grid_locked[row - 1][col - 1] = 0;
                    grid_merge[row - 1][col - 1] = 0;
                }
                else {
                    grid_locked[row - 1][col - 1] = grid_setNum;
                    setButtonNum(pushButton, grid_setNum, 40, FALSE);
                    grid_merge[row - 1][col - 1] = grid_setNum;
                }
            }
        }
        else {
            if (grid_edit[row - 1][col - 1]) {
                if(grid_setNum == grid_merge[row - 1][col - 1]) {
                    setButtonNum(pushButton, 0, 40, FALSE);
                    pushButton->setText("");
                    grid_edited[row - 1][col - 1] = 0;
                    grid_merge[row - 1][col - 1] = 0;
                }
                else {
                    setButtonNum(pushButton, grid_setNum, 40, TRUE);
                    grid_edited[row - 1][col - 1] = grid_setNum;
                    grid_merge[row - 1][col - 1] = grid_setNum;
                }
            }
        }
        if (is_clickedAllStep == FALSE) {
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    eliminate[i][j].arr = MemoryManage_1D(9);
                    Update_Board(grid_merge, i, j);
                }
            }
            if (optionCandidate == TRUE) {
                gridCandidate(grid_merge);
            }
        }
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

void MainWindow::on_allStepButton_clicked() {
    if (is_clickedAllStep == FALSE && is_inValid == FALSE && is_gameStop == TRUE) {
        int **grid_temp, text[9][9] = {{0,9,0, 8,4,6, 0,0,3},
                                       {3,4,6, 0,0,0, 0,0,0},
                                       {0,0,0, 0,0,0, 0,0,0},

                                       {0,0,5, 0,3,0, 0,0,2},
                                       {0,1,4, 9,0,5, 3,8,0},
                                       {2,0,0, 0,6,0, 1,0,0},

                                       {0,0,0, 0,0,0, 0,0,0},
                                       {0,0,0, 0,0,0, 2,0,9},
                                       {5,0,0, 3,9,1, 0,4,0}};
        grid_temp = MemoryManage_2D(9, 9);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if (grid_edited[i][j] != 0) {
                    grid_locked[i][j] = 0;
                    setButtonNum(buttonGrid[i][j], 0, 40, FALSE);
                }
                grid_temp[i][j] = grid_locked[i][j];
            }
        }
        QPushButton *pushButton;
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                pushButton = buttonGrid[i][j];
                if(grid_locked[i][j] != 0) {
                    grid_step[i][j] = grid_locked[i][j];
                    setButtonNum(buttonGrid[i][j], grid_locked[i][j], 40, FALSE);
                }
                else {
                    pushButton->setStyleSheet("QPushButton { color: rgb(155, 155, 155); border:1 px solid gray; background-color: rgb(51, 51, 51); } QPushButton::pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
                }
                grid_merge[i][j] = grid_locked[i][j];
            }
        }
        ui->tabWidget->setCurrentIndex(1);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if( grid_locked[i][j] != 0) {
                    sudoBoard[i][j].num = grid_locked[i][j];
                }
                grid_edit[i][j] = 0;
            }
        }
        int resultType = startGuide(grid_locked, FALSE, 0);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                grid_locked[i][j] = grid_temp[i][j];
            }
        }
        ui->listWidget->clear();
        ui->textBrowser->clear();
        if (resultType != -1) {
            if (resultType == 1) {
                for(int i = 0; textGuide[i].text[0] != 0; i++) {
                    ui->listWidget->addItem(textGuide[i].text);
                }
                ui->textBrowser->setText(textSummary.text);
                ui->listWidget->addItem("Finish !");
            }
            else {
                for(int i = 0; textGuide[i].text[0] != 0; i++) {
                    ui->listWidget->addItem(textGuide[i].text);
                }
                ui->listWidget->addItem("Can't find Solution . . .");
                ui->textBrowser->setText("No Solution\nSudoku may have many Solution (not Unique) or Can't solve with Technique in Library.");
                is_noSolution = TRUE;
            }
        }
        else {
            ui->listWidget->addItem("Invalid Sudoku! at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1));
            ui->textBrowser->setText("Invalid Sudoku! look at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1) + "\nPlease re-enter Sudoku again");
            pushButton = buttonGrid[coord.x][coord.y];
            pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
            setButtonNum(pushButton, grid_locked[coord.x][coord.y], 40, TRUE);
            is_inValid = TRUE;
        }
        is_clickedAllStep = TRUE;
        startGuide(grid_merge, TRUE, 0);
        gridCandidate(grid_merge);
    }
}

void MainWindow::on_listWidget_itemDoubleClicked() {
    if (is_inValid == FALSE) {
        int index = ui->listWidget->currentRow();
        int loop = index;
        int **grid_temp;
        grid_temp = MemoryManage_2D(9, 9);
        QPushButton *pushButton;
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                pushButton = buttonGrid[i][j];
                if (grid_locked[i][j] == 0) {
                    setButtonNum(pushButton, 0, 40, FALSE);
                }
                grid_merge[i][j] = grid_locked[i][j];
                grid_step[i][j] = grid_locked[i][j];
                grid_temp[i][j] = grid_locked[i][j];
                pushButton->setStyleSheet("QPushButton { color: rgb(155, 155, 155); border:1 px solid gray; background-color: rgb(51, 51, 51); } QPushButton::pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
            }
        }
        startGuide(grid_step, TRUE, index + 1);
        selectGridCandidate(index);
        gridCandidate(grid_step);
        startGuide(grid_temp, TRUE, index);
        gridCandidate(grid_temp);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if (sudoBoard[i][j].num != 0) {
                    pushButton = buttonGrid[i][j];
                    pushButton->setText("");
                    if (grid_locked[i][j] == 0) {
                        setButtonNum(pushButton, sudoBoard[i][j].num, 40, TRUE);
                    }
                }
            }
        }
    }
}

void MainWindow::on_clearButton_clicked() {
    Setup();
    QPushButton *pushButton;
    if (grid_setNum != 0) {
        pushButton = getControlButton(grid_setNum);
        pushButton->setStyleSheet("QPushButton { border:1 px solid gray; background-color: #f19b38; }");
        setButtonNum(pushButton, grid_setNum, 30, FALSE);
        grid_setNum = 0;
    }

    ui->tabWidget->setCurrentIndex(0);
    ui->listWidget->clear();
    ui->textBrowser->setText("New Game!");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(grid_locked[i][j] == 0) {
                buttonGrid[i][j]->setText("");
            }
            sudoBoard[i][j].num = 0;
            grid_edit[i][j] = 1;
            grid_locked[i][j] = 0;
            grid_step[i][j] = 0;
            grid_merge[i][j] = 0;
            grid_edited[i][j] = 0;
            setButtonNum(buttonGrid[i][j], 0, 40, FALSE);
            pushButton = buttonGrid[i][j];
            pushButton->setStyleSheet("QPushButton { border:1 px solid gray; background-color: rgb(51, 51, 51); } QPushButton::pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        }
    }
    is_clickedAllStep = FALSE;
    is_inValid = FALSE;
    is_noSolution = FALSE;
    is_gameStart = FALSE;
    is_clear = TRUE;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Update_Board(grid_merge, i, j);
        }
    }
    if (optionCandidate == TRUE) {
        gridCandidate(grid_merge);
    }
    is_gameStop = TRUE;
    timer_second = 0;
    timer_minute = 0;
    ui->lcdNumber->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgb(0, 0, 0, 0);");
    ui->startGameButton->setText("Start Game");
}

void MainWindow::gridCandidate(int **grid) {
    QPushButton *pushButton;
    char *text, *temp;
    text = MemoryManage_1D_Char(64);
    temp = MemoryManage_1D_Char(32);
    temp[0] = '\0';
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            text[0] = '\0';
            pushButton = buttonGrid[i][j];
            if (is_clickedAllStep != TRUE && is_inValid != TRUE) {
                pushButton->setStyleSheet("QPushButton { color: rgb(155, 155, 155); border:1 px solid gray; background-color: rgb(51, 51, 51); } QPushButton::pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
            }
            if(grid[i][j] == 0 && optionCandidate == TRUE) {
                for (int num = 0; num < 9; ++num) {
                    if ((num + 1) % 3 != 0) {
                        if ((num + 1 != 7)) {
                            if (cell[i][j].arr[num] != 0) {
                                sprintf(temp, "%d    ", cell[i][j].arr[num]);
                                strcat(text, temp);
                            }
                            else {
                                sprintf(temp, "%c    ", '_');
                                strcat(text, temp);
                            }
                        }
                        else {
                            if (cell[i][j].arr[num] != 0) {
                                sprintf(temp, "    %d    ", cell[i][j].arr[num]);
                                strcat(text, temp);
                            }
                            else {
                                sprintf(temp, "    %c    ", '_');
                                strcat(text, temp);
                            }
                        }
                    }
                    else {
                        if (num + 1 != 9) {
                            if (cell[i][j].arr[num] != 0) {
                                sprintf(temp, "%d    \n", cell[i][j].arr[num]);
                                strcat(text, temp);
                            }
                            else {
                                sprintf(temp, "%c    \n", '_');
                                strcat(text, temp);
                            }
                        }
                        else {
                            if (cell[i][j].arr[num] != 0) {
                                sprintf(temp, "%d    ", cell[i][j].arr[num]);
                                strcat(text, temp);
                            }
                            else {
                                sprintf(temp, "%c    ", '_');
                                strcat(text, temp);
                            }
                        }
                    }
                }
                buttonGrid[i][j]->setText(text);
            }
            else {
                buttonGrid[i][j]->setText("");
            }
        }
    }
}

void MainWindow::selectGridCandidate(int index) {
    QPushButton *pushButton;
    if (textGuide[index].numCoord == 1) {
        pushButton = buttonGrid[textGuide[index].row - 1][textGuide[index].col - 1];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");

    }
    else if (textGuide[index].numCoord == 2) {
        pushButton = buttonGrid[coord_pair.x1][coord_pair.y1];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x2][coord_pair.y2];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");

    }
    else if (textGuide[index].numCoord == 3) {
        pushButton = buttonGrid[coord_pair.x1][coord_pair.y1];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x2][coord_pair.y2];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x3][coord_pair.y3];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
    }
    else if (textGuide[index].numCoord == 4) {
        pushButton = buttonGrid[coord_pair.x1][coord_pair.y1];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x2][coord_pair.y2];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x3][coord_pair.y3];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        pushButton = buttonGrid[coord_pair.x4][coord_pair.y4];
        pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (48 <= event->text() && event->text() <= 57) {
        int num = event->text().toInt();
        QPushButton *pushButton;
        if (num != 0) {
            if (num != grid_setNum) {
                pushButton = getControlButton(num);
                controlButtonPressed(pushButton, num);
            }
        }
        else {
            pushButton = getControlButton(grid_setNum);
            controlButtonPressed(pushButton, grid_setNum);
        }
    }
}

void MainWindow::on_randomButton_clicked() {
    if (is_gameStop == TRUE) {
        on_clearButton_clicked();
        ui->textBrowser->setText("Puzzle generated");
        int loop = 8000, random = sameRandom, count = 0;
        while(random == sameRandom) {
            random = qrand() % loop;
        }
        sameRandom = random;
        QFile localFile(":/src/generate/sudokuTable.txt");
        localFile.open(QIODevice::ReadOnly);
        QTextStream in(&localFile);
        QString grid;
        for(int i = 0; i < random + 1; ++i) {
            grid = in.readLine();
        }
        localFile.close();

        QPushButton *pushButton;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid_locked[i][j] = grid.split("")[++count].toInt();
                pushButton = buttonGrid[i][j];
                setButtonNum(pushButton, grid_locked[i][j], 40, FALSE);
                grid_merge[i][j] = grid_locked[i][j];
            }
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                eliminate[i][j].arr = MemoryManage_1D(9);
                Update_Board(grid_merge, i, j);
            }
        }
        startGuide(grid_merge, TRUE, 0);
        if (optionCandidate == TRUE) {
            gridCandidate(grid_merge);
        }
    }
}

void MainWindow::on_startGameButton_clicked() {
    if (is_clickedAllStep == FALSE) {
        if (is_gameStart == FALSE) {
            int **grid_temp;
            grid_temp = MemoryManage_2D(9, 9);
            ui->listWidget->clear();
            ui->textBrowser->clear();
            QPushButton *pushButton;
            for(int i = 0; i < 9; ++i) {
                for(int j = 0; j < 9; ++j) {
                    if (grid_locked[i][j] != 0) {
                        grid_edit[i][j] = 0;
                        grid_merge[i][j] = grid_locked[i][j];
                    }
                    grid_temp[i][j] = grid_locked[i][j];
                }
            }
            int resultType = startGuide(grid_locked, FALSE, 0);
            for(int i = 0; i < 9; ++i) {
                for(int j = 0; j < 9; ++j) {
                    grid_locked[i][j] = grid_temp[i][j];
                }
            }
            for(int i = 0; i < 9; ++i) {
                for(int j = 0; j < 9; ++j) {
                    if (grid_locked[i][j] != 0) {
                        grid_edit[i][j] = 0;
                        grid_merge[i][j] = grid_locked[i][j];
                    }
                }
            }
            if (resultType != -1) {
                if (resultType == 1) {
                    ui->textBrowser->setText("Game Start!");
                    ui->startGameButton->setText("Stop");
                    ui->lcdNumber->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgb(255, 255, 255);");
                    is_gameStart = TRUE;
                    is_gameStop = FALSE;
                    timer->start(1000);
                    timeCount();
                }
                else {
                    ui->listWidget->addItem("Don't have Solution . . .");
                    ui->textBrowser->setText("Don't have Solution\nSudoku may have many Solution (not Unique) or Sudoku is Invalid\nPlease re-enter Sudoku again");
                    is_noSolution = TRUE;
                    is_gameStart = FALSE;
                }
            }
            else {
                ui->listWidget->addItem("Invalid Sudoku! at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1));
                ui->textBrowser->setText("Invalid Sudoku! look at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1) + "\nPlease re-enter Sudoku again");
                pushButton = buttonGrid[coord.x][coord.y];
                pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
                setButtonNum(pushButton, grid_locked[coord.x][coord.y], 40, TRUE);
                for(int i = 0; i < 9; ++i) {
                    for(int j = 0; j < 9; ++j) {
                        grid_edit[i][j] = 0;
                    }
                }
                is_inValid = TRUE;
                is_gameStart = FALSE;
            }
        }
        else {
            is_gameStop = TRUE;
            ui->startGameButton->setText("Stop");
            timer_second = 0;
            timer_minute = 0;
            int **sudoku;
            sudoku = MemoryManage_2D(9, 9);
            for(int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (grid_merge[i][j] != 0) {
                        sudoku[i][j] = grid_merge[i][j];
                    }
                    grid_edit[i][j] = 0;
                }
            }
            if(Find_EmptySlot(sudoku, 0, 0) == TRUE) {
                ui->textBrowser->setText("UNFINISHED!\n Press 'New' and try again or See all solution step");
            }
            else if(IsValid_Board(sudoku, 9, 9) == FALSE) {
                ui->textBrowser->setText("WRONG! Look at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1) + "\nTry again" );
            }
            else {
                char *text;
                ui->textBrowser->setText("CORRECT!\n");
                ui->textBrowser->append(textSummary.text);
            }
        }
    }
    else {
        ui->textBrowser->setText("Press 'New' and try again");
    }
}

void MainWindow::timeCount() {
    if (is_gameStop == FALSE) {
        show_time = QString(":");
        show_time.push_front(QString(timer_minute % 10 + '0'));
        show_time.push_front(QString((timer_minute % 100) / 10 + '0'));
        show_time.push_back(QString((timer_second % 100) / 10 + '0'));
        show_time.push_back(QString(timer_second % 10 + '0'));
        ui->lcdNumber->display(show_time);
        timer_second++;
        if (timer_second >= 60) {
            timer_second = 0;
            timer_minute++;
            if (timer_minute >= 60) {
                timer_minute = 0;
            }
        }
    }
}
