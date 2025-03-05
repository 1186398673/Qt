#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<QMessageBox>
// 定义游戏区域大小
const int ROWS = 10;
const int COLS = 10;
const int CELL_SIZE = 30;
const int OFFSET = 20;
const int MINE_COUNT = 15;

// 定义格子状态
enum CellState { EMPTY, MINE, FLAG, REVEALED };

class Minesweeper : public QWidget {


public:
    Minesweeper(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("扫雷");
        setFixedSize((COLS + 2) * CELL_SIZE + OFFSET * 2, (ROWS + 2) * CELL_SIZE + OFFSET * 2);

        // 初始化游戏状态
        srand(time(0));
        board.resize(ROWS, std::vector<CellState>(COLS, EMPTY));
        mineCount = MINE_COUNT;
        flags = 0;
        gameOver = false;

        // 生成雷区
        placeMines();
        calculateNumbers();
    }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制游戏区域
        painter.setBrush(QBrush(Qt::lightGray));
        painter.drawRect(OFFSET, OFFSET, COLS * CELL_SIZE, ROWS * CELL_SIZE);

        // 绘制格子
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                int x = col * CELL_SIZE + OFFSET;
                int y = row * CELL_SIZE + OFFSET;

                if (board[row][col] == REVEALED) {
                    painter.setBrush(QBrush(Qt::white));
                } else {
                    painter.setBrush(QBrush(Qt::gray));
                }

                painter.drawRect(x, y, CELL_SIZE, CELL_SIZE);

                // 绘制数字或雷
                if (board[row][col] == REVEALED) {
                    if (numbers[row][col] > 0) {
                        painter.setPen(Qt::blue);
                        painter.drawText(QRect(x, y, CELL_SIZE, CELL_SIZE), Qt::AlignCenter, QString::number(numbers[row][col]));
                    } else if (numbers[row][col] == 0) {
                        // 空格子
                    } else if (board[row][col] == MINE) {
                        painter.setBrush(QBrush(Qt::red));
                        painter.drawEllipse(QPoint(x + CELL_SIZE / 2, y + CELL_SIZE / 2), CELL_SIZE / 4, CELL_SIZE / 4);
                    }
                } else if (board[row][col] == FLAG) {
                    painter.setPen(Qt::red);
                    painter.drawText(QRect(x, y, CELL_SIZE, CELL_SIZE), Qt::AlignCenter, "F");
                }
            }
        }

        // 绘制雷数
        painter.setPen(Qt::black);
        painter.drawText(10, 10, QString("雷数: %1").arg(mineCount - flags));
    }

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override {
        if (gameOver) return;

        int x = event->x();
        int y = event->y();

        // 计算点击的格子
        int col = (x - OFFSET) / CELL_SIZE;
        int row = (y - OFFSET) / CELL_SIZE;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return;

        if (event->button() == Qt::LeftButton) {
            if (board[row][col] != FLAG) {
                if (board[row][col] == MINE) {
                    // 踩雷，游戏结束
                    gameOver = true;
                    revealAllMines();
                    QMessageBox::information(this, "游戏结束", "你踩到雷了！");
                    QApplication::quit();
                } else {
                    revealCell(row, col);
                    if (checkWin()) {
                        QMessageBox::information(this, "恭喜", "你赢了！");
                        QApplication::quit();
                    }
                }
            }
        } else if (event->button() == Qt::RightButton) {
            if (board[row][col] == EMPTY) {
                board[row][col] = FLAG;
                flags++;
                update();
            } else if (board[row][col] == FLAG) {
                board[row][col] = EMPTY;
                flags--;
                update();
            }
        }

        update();
    }

private:
    std::vector<std::vector<CellState>> board;
    std::vector<std::vector<int>> numbers;
    int mineCount;
    int flags;
    bool gameOver;

    // 生成雷区
    void placeMines() {
        int minesPlaced = 0;
        while (minesPlaced < MINE_COUNT) {
            int row = rand() % ROWS;
            int col = rand() % COLS;
            if (board[row][col] != MINE) {
                board[row][col] = MINE;
                minesPlaced++;
            }
        }
    }

    // 计算每个格子的数字提示
    void calculateNumbers() {
        numbers.resize(ROWS, std::vector<int>(COLS, 0));
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                if (board[row][col] == MINE) {
                    numbers[row][col] = -1;
                } else {
                    int count = 0;
                    for (int r = row - 1; r <= row + 1; ++r) {
                        for (int c = col - 1; c <= col + 1; ++c) {
                            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == MINE) {
                                count++;
                            }
                        }
                    }
                    numbers[row][col] = count;
                }
            }
        }
    }

    // 翻开格子
    void revealCell(int row, int col) {
        if (board[row][col] != EMPTY) return;
        board[row][col] = REVEALED;
        if (numbers[row][col] == 0) {
            for (int r = row - 1; r <= row + 1; ++r) {
                for (int c = col - 1; c <= col + 1; ++c) {
                    if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                        revealCell(r, c);
                    }
                }
            }
        }
    }

    // 揭示所有雷
    void revealAllMines() {
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                if (board[row][col] == MINE) {
                    board[row][col] = REVEALED;
                }
            }
        }
    }

    // 检查是否赢得游戏
    bool checkWin() {
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                if (board[row][col] != REVEALED && board[row][col] != MINE) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Minesweeper game;
    game.show();
    return app.exec();
}


