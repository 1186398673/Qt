#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <vector>
#include<QMessageBox>
// 定义棋盘的大小
const int BOARD_SIZE = 15;
const int CELL_SIZE = 40;
const int OFFSET = 20;

// 定义棋子状态
enum CellState { EMPTY, BLACK, WHITE };

class Gomoku : public QWidget {


public:
    Gomoku(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("五子棋");
        setFixedSize((BOARD_SIZE + 1) * CELL_SIZE + OFFSET * 2, (BOARD_SIZE + 1) * CELL_SIZE + OFFSET * 2);

        // 初始化棋盘
        board.resize(BOARD_SIZE, std::vector<CellState>(BOARD_SIZE, EMPTY));
        currentPlayer = BLACK;
    }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制棋盘
        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        for (int i = 0; i < BOARD_SIZE; ++i) {
            painter.drawLine(CELL_SIZE + OFFSET, CELL_SIZE + i * CELL_SIZE + OFFSET, CELL_SIZE * BOARD_SIZE + OFFSET, CELL_SIZE + i * CELL_SIZE + OFFSET);
            painter.drawLine(CELL_SIZE + i * CELL_SIZE + OFFSET, CELL_SIZE + OFFSET, CELL_SIZE + i * CELL_SIZE + OFFSET, CELL_SIZE * BOARD_SIZE + OFFSET);
        }

        // 绘制棋子
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != EMPTY) {
                    if (board[i][j] == BLACK) {
                        painter.setBrush(QBrush(Qt::black));
                    } else {
                        painter.setBrush(QBrush(Qt::white));
                    }
                    painter.drawEllipse(QPoint(CELL_SIZE + j * CELL_SIZE + OFFSET, CELL_SIZE + i * CELL_SIZE + OFFSET), CELL_SIZE / 2 - 2, CELL_SIZE / 2 - 2);
                }
            }
        }
    }

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override {
        int x = event->x();
        int y = event->y();

        // 计算点击的格子
        int row = (y - OFFSET + CELL_SIZE / 2) / CELL_SIZE;
        int col = (x - OFFSET + CELL_SIZE / 2) / CELL_SIZE;

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY) {
            board[row][col] = currentPlayer;
            update();

            // 检查是否有五子连珠
            if (checkWin(row, col)) {
                QString winner = currentPlayer == BLACK ? "黑棋" : "白棋";
                QMessageBox::information(this, "游戏结束", winner + " 获胜！");
                QApplication::quit();
            }

            // 切换玩家
            currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
        }
    }

private:
    std::vector<std::vector<CellState>> board;
    CellState currentPlayer;

    // 检查是否有五子连珠
    bool checkWin(int row, int col) {
        CellState player = board[row][col];
        int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

        for (int d = 0; d < 4; ++d) {
            int count = 1;
            // 向一个方向搜索
            int dr = directions[d][0];
            int dc = directions[d][1];
            int r = row + dr;
            int c = col + dc;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
                count++;
                r += dr;
                c += dc;
            }

            // 向相反方向搜索
            dr = -directions[d][0];
            dc = -directions[d][1];
            r = row + dr;
            c = col + dc;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
                count++;
                r += dr;
                c += dc;
            }

            if (count >= 5) {
                return true;
            }
        }

        return false;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Gomoku game;
    game.show();
    return app.exec();
}


