#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

class FlashCardApp : public QWidget {

public:
    FlashCardApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("空白扑克牌软件");
        setFixedSize(800, 480);

        // 创建多行输入框，用于显示和编辑卡片内容
        inputTextEdit = new QTextEdit(this);
        inputTextEdit->setPlaceholderText("输入卡片内容（支持多行）");
        inputTextEdit->setStyleSheet("font-size: 16px;");
        inputTextEdit->setMinimumHeight(150);
        inputTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // 创建按钮
        QPushButton *addButton = new QPushButton("添加卡片", this);
        QPushButton *editButton = new QPushButton("编辑卡片", this);
        QPushButton *deleteButton = new QPushButton("删除卡片", this);
        QPushButton *prevButton = new QPushButton("上一张", this);
        QPushButton *nextButton = new QPushButton("下一张", this);
        QPushButton *exitButton = new QPushButton("退出", this);
        QPushButton *saveButton = new QPushButton("保存卡片", this);
        QPushButton *loadButton = new QPushButton("加载卡片", this);

        // 设置按钮尺寸
        QSize buttonSize(100, 30);
        addButton->setFixedSize(buttonSize);
        editButton->setFixedSize(buttonSize);
        deleteButton->setFixedSize(buttonSize);
        prevButton->setFixedSize(buttonSize);
        nextButton->setFixedSize(buttonSize);
        exitButton->setFixedSize(buttonSize);
        saveButton->setFixedSize(buttonSize);
        loadButton->setFixedSize(buttonSize);

        // 创建卡片列表
        listWidget = new QListWidget(this);
        listWidget->setFixedWidth(200);

        // 连接按钮信号和槽
        connect(addButton, &QPushButton::clicked, this, &FlashCardApp::addCard);
        connect(editButton, &QPushButton::clicked, this, &FlashCardApp::editCard);
        connect(deleteButton, &QPushButton::clicked, this, &FlashCardApp::deleteCard);
        connect(prevButton, &QPushButton::clicked, this, &FlashCardApp::prevCard);
        connect(nextButton, &QPushButton::clicked, this, &FlashCardApp::nextCard);
        connect(exitButton, &QPushButton::clicked, this, &FlashCardApp::exitApp);
        connect(saveButton, &QPushButton::clicked, this, &FlashCardApp::saveCards);
        connect(loadButton, &QPushButton::clicked, this, &FlashCardApp::loadCards);
        connect(listWidget, &QListWidget::itemClicked, this, &FlashCardApp::showCard);

        // 允许双击编辑列表项
        listWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        connect(listWidget, &QListWidget::itemDoubleClicked, this, &FlashCardApp::editListItem);

        // 创建按钮布局
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(prevButton);
        buttonLayout->addWidget(nextButton);
        buttonLayout->addWidget(saveButton);
        buttonLayout->addWidget(loadButton);
        buttonLayout->addWidget(exitButton);
        buttonLayout->addStretch(); // 使用 stretch 使按钮自动缩小

        // 创建右侧布局
        QVBoxLayout *rightLayout = new QVBoxLayout();
        rightLayout->addLayout(buttonLayout);
        rightLayout->addWidget(inputTextEdit, 1); // inputTextEdit 占据更多空间

        // 创建主布局
        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(listWidget);
        mainLayout->addLayout(rightLayout);

        setLayout(mainLayout);

        // 初始化当前卡片索引
        currentIndex = 0;
        loadCards(); // 启动时加载卡片
    }

private slots:
    // 添加卡片
    void addCard() {
        QString text = inputTextEdit->toPlainText();
        if (!text.isEmpty()) {
            cards.append(text);
            listWidget->addItem(text.split("\n").first()); // 使用第一行作为列表项显示
            inputTextEdit->clear();
            currentIndex = cards.size() - 1;
            listWidget->setCurrentRow(currentIndex);
        } else {
            QMessageBox::warning(this, "输入错误", "请输入卡片内容！");
        }
    }

    // 编辑当前卡片
    void editCard() {
        if (currentIndex < cards.size()) {
            QString newText = inputTextEdit->toPlainText();
            if (!newText.isEmpty()) {
                cards[currentIndex] = newText;
                listWidget->item(currentIndex)->setText(newText.split("\n").first()); // 更新列表项显示
            } else {
                QMessageBox::warning(this, "输入错误", "卡片内容不能为空！");
            }
        }
    }

    // 删除当前卡片
    void deleteCard() {
        if (currentIndex < cards.size()) {
            int ret = QMessageBox::warning(this, "删除卡片", "确定要删除当前卡片吗？", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                cards.removeAt(currentIndex);
                delete listWidget->takeItem(currentIndex);
                if (currentIndex >= cards.size()) {
                    currentIndex = cards.size() - 1;
                }
                if (currentIndex >= 0) {
                    listWidget->setCurrentRow(currentIndex);
                    showCard(listWidget->item(currentIndex));
                } else {
                    inputTextEdit->clear();
                }
            }
        }
    }

    // 切换到上一张卡片
    void prevCard() {
        if (currentIndex > 0) {
            currentIndex--;
            listWidget->setCurrentRow(currentIndex);
            showCard(listWidget->item(currentIndex));
        } else {
            QMessageBox::information(this, "提示", "已经是第一张卡片！");
        }
    }

    // 切换到下一张卡片
    void nextCard() {
        if (currentIndex < cards.size() - 1) {
            currentIndex++;
            listWidget->setCurrentRow(currentIndex);
            showCard(listWidget->item(currentIndex));
        } else {
            QMessageBox::information(this, "提示", "已经是最后一张卡片！");
        }
    }

    // 退出应用
    void exitApp() {
        QApplication::quit();
    }

    // 显示当前卡片
    void showCard(QListWidgetItem *item) {
        if (item) {
            int index = listWidget->row(item);
            inputTextEdit->setText(cards[index]);
        }
    }

    // 编辑列表项
    void editListItem(QListWidgetItem *item) {
        if (item) {
            bool ok;
            QString newText = QInputDialog::getText(this, "编辑卡片标题", "请输入新的卡片标题:", QLineEdit::Normal, item->text(), &ok);
            if (ok && !newText.isEmpty()) {
                item->setText(newText);
                int index = listWidget->row(item);
                cards[index] = newText;
            }
        }
    }

    // 保存卡片到文件
    void saveCards() {
        QFile file("flashcards.json");
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "保存失败", "无法打开文件进行写入！");
            return;
        }

        QJsonArray jsonCards;
        for (const QString &card : cards) {
            jsonCards.append(QJsonValue(card));
        }

        QJsonDocument jsonDoc(jsonCards);
        file.write(jsonDoc.toJson());
        file.close();

        QMessageBox::information(this, "保存成功", "卡片已保存！");
    }

    // 从文件加载卡片
    void loadCards() {
        QFile file("flashcards.json");
        if (!file.open(QIODevice::ReadOnly)) {
            // 如果文件不存在，则不执行任何操作
            return;
        }

        QByteArray data = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (jsonDoc.isArray()) {
            QJsonArray jsonCards = jsonDoc.array();
            for (const QJsonValue &value : jsonCards) {
                if (value.isString()) {
                    cards.append(value.toString());
                    listWidget->addItem(value.toString().split("\n").first());
                }
            }
            currentIndex = cards.size() - 1;
            listWidget->setCurrentRow(currentIndex);
        } else {
            QMessageBox::warning(this, "加载失败", "文件格式不正确！");
        }

        file.close();
    }

private:
    QTextEdit *inputTextEdit; // 用于显示和编辑卡片内容
    QListWidget *listWidget;
    QStringList cards;
    int currentIndex;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FlashCardApp flashCardApp;
    flashCardApp.show();
    return app.exec();
}
