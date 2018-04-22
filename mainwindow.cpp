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

    grid_setNum = 0;
    is_clickedAllStep = FALSE;
    is_inValid = FALSE;
    is_noSolution = FALSE;
    is_gameStart = FALSE;
    is_clear = FALSE;
    sameRandom = -1;

    grid_edited = MemoryManage_2D(9, 9);
    grid_step = MemoryManage_2D(9, 9);
    grid_locked = MemoryManage_2D(9, 9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid_edit[i][j] = 1;
            grid_edited[i][j] = 0;
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
    buttonGrid = initButtonGrid();


    for (int i = 0; i < 9; i++) {
        connect(controlButtons[i], &QPushButton::clicked, [ = ]() { controlButtonPressed(controlButtons[i], i + 1); });
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            connect(buttonGrid[i][j], &QPushButton::clicked, [ = ]() { pushButtonPressed(buttonGrid[i][j], i + 1, j + 1); });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonNum(QPushButton *pushButton, int num, int size, bool onlyHover) {
    if (num == 0) {
        pushButton->setIcon(QIcon(""));
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
    if (is_gameStart == FALSE) {
        if (grid_edit[row - 1][col - 1]) {
            if(grid_setNum == grid_locked[row - 1][col - 1]) {
                setButtonNum(pushButton, 0, 40, FALSE);
                grid_locked[row - 1][col - 1] = 0;
            }
            else {
                grid_locked[row - 1][col - 1] = grid_setNum;
                setButtonNum(pushButton, grid_setNum, 40, FALSE);
            }
        }
    }
    else {
        if (grid_edit[row - 1][col - 1]) {
            if(grid_setNum == grid_locked[row - 1][col - 1]) {
                setButtonNum(pushButton, 0, 40, FALSE);
                grid_locked[row - 1][col - 1] = 0;
                grid_edited[row - 1][col - 1] = 0;
            }
            else {
                grid_locked[row - 1][col - 1] = grid_setNum;
                setButtonNum(pushButton, grid_setNum, 40, TRUE);
                grid_edited[row - 1][col - 1] = grid_setNum;
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
    if (is_clickedAllStep == FALSE) {
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if (grid_edited[i][j] != 0) {
                    grid_locked[i][j] = 0;
                    setButtonNum(buttonGrid[i][j], 0, 40, FALSE);
                }
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
            pushButton = buttonGrid[coord.x][coord.y];
            pushButton->setStyleSheet("QPushButton { color: rgb(0, 0, 0); border:1 px solid gray; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
            setButtonNum(pushButton, grid_locked[coord.x][coord.y], 40, TRUE);
            is_inValid = TRUE;
        }
        is_clickedAllStep = TRUE;
    }
}

void MainWindow::on_listWidget_itemDoubleClicked() {
    if (is_inValid == FALSE) {
        int index = ui->listWidget->currentRow();
        int loop = index;
        QPushButton *pushButton;
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                pushButton = buttonGrid[i][j];
                if (grid_locked[i][j] == 0) {
                    setButtonNum(pushButton, 0, 40, FALSE);
                }
                pushButton->setStyleSheet("QPushButton { color: rgb(155, 155, 155); border:1 px solid gray; background-color: rgb(51, 51, 51); } QPushButton::pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa); }");
            }
        }
        gridCandidate(index + 1);
        selectGridCandidate(index);
        gridCandidate(index);
        if (is_noSolution == TRUE) {
            gridCandidate(index);
        }
        for(int num = 0; num < loop; ++num) {
            int row = textGuide[num].row, col = textGuide[num].col;
            if(row != 0 && col != 0) {
                pushButton = buttonGrid[row - 1][col - 1];
                pushButton->setText("");
                setButtonNum(pushButton, sudoBoard[row - 1][col - 1].num, 40, TRUE);
            }
        }
    }
}

void MainWindow::on_clearButton_clicked() {
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
}

void MainWindow::gridCandidate(int loopFreeze) {
    startGuide(grid_step, TRUE, loopFreeze);
    char *text, *temp;
    text = MemoryManage_1D_Char(64);
    temp = MemoryManage_1D_Char(32);
    temp[0] = '\0';
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            text[0] = '\0';
            if(grid_locked[i][j] == 0) {
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
        }
    }
}

void MainWindow::on_startGameButton_clicked() {
    if (is_clickedAllStep == FALSE) {
        if (is_gameStart == FALSE) {
            ui->listWidget->clear();
            ui->textBrowser->clear();
            QPushButton *pushButton;
            for(int i = 0; i < 9; ++i) {
                for(int j = 0; j < 9; ++j) {
                    if (grid_locked[i][j] != 0) {
                        grid_edit[i][j] = 0;
                    }
                }
            }
            int resultType = startGuide(grid_locked, FALSE, 0);
            if (resultType != -1) {
                if (resultType == 1) {
                    ui->textBrowser->setText("Game Start!");
                    is_gameStart = TRUE;
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
            int **sudoku;
            sudoku = MemoryManage_2D(9, 9);
            for(int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (grid_locked[i][j] != 0) {
                        sudoku[i][j] = grid_locked[i][j];
                    }
                    grid_edit[i][j] = 0;
                }
            }
            if(Find_EmptySlot(sudoku, 0, 0) == TRUE) {
                ui->textBrowser->setText("UNFINISHED!");
            }
            else if(IsValid_Board(sudoku, 9, 9) == FALSE) {
                ui->textBrowser->setText("WRONG! Look at r" + QString::number(coord.x + 1) + QString(tr("c")) + QString::number(coord.y + 1) + "\nTry again" );
            }
            else {
                ui->textBrowser->setText("CORRECT!");
            }
        }
    }
    else {
        ui->textBrowser->setText("Press 'New' and try again");
    }
}
