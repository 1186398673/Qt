#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextCursor>
#include <QTextDocument>
#include <QSettings>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

class ExcelReaderApp : public QWidget {

public:
    ExcelReaderApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("QXlsx Excel 编辑示例");
        setFixedSize(800, 600);

        // 创建按钮
        QPushButton *openButton = new QPushButton("打开 Excel 文件", this);
        connect(openButton, &QPushButton::clicked, this, &ExcelReaderApp::openExcel);

        QPushButton *newButton = new QPushButton("新建 Excel 文件", this);
        connect(newButton, &QPushButton::clicked, this, &ExcelReaderApp::newExcel);

        QPushButton *saveButton = new QPushButton("保存 Excel 文件", this);
        connect(saveButton, &QPushButton::clicked, this, &ExcelReaderApp::saveExcel);

        // 创建文本编辑框，用于显示和编辑 Excel 内容
        textEdit = new QTextEdit(this);
        textEdit->setReadOnly(false);
        textEdit->setStyleSheet("font-size: 14px;");
        textEdit->setMinimumHeight(400);

        // 创建布局
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(newButton);
        buttonLayout->addWidget(openButton);
        buttonLayout->addWidget(saveButton);
        buttonLayout->addStretch();

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(textEdit);

        setLayout(mainLayout);

        // 设置最大行数和列数
        maxRows = 100;
        maxCols = 26;

        // 读取上次打开的文件路径
        QSettings settings("MyCompany", "ExcelReaderApp");
        currentFilePath = settings.value("lastFilePath").toString();
        if (!currentFilePath.isEmpty()) {
            openExcel();
        }
    }

private slots:
    void openExcel() {
        // 打开文件对话框选择 Excel 文件
        QString filePath = QFileDialog::getOpenFileName(this, "选择 Excel 文件", "", "Excel 文件 (*.xlsx)");
        if (filePath.isEmpty()) {
            return;
        }

        QXlsx::Document xlsx(filePath);
        if (!xlsx.load()) {
            QMessageBox::warning(this, "错误", "无法打开 Excel 文件！");
            return;
        }

        // 读取 Excel 内容
        QString content;
        QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
        if (sheet) {
            QXlsx::CellRange range = sheet->dimension();
            int rowCount = range.lastRow();
            int colCount = range.lastColumn();

            // 限制最大行数和列数
            if (rowCount > maxRows) rowCount = maxRows;
            if (colCount > maxCols) colCount = maxCols;

            for (int row = 1; row <= rowCount; ++row) {
                for (int col = 1; col <= colCount; ++col) {
                    QString cellValue = xlsx.read(row, col).toString();
                    content += cellValue;
                    if (col < colCount) {
                        content += "\t";
                    }
                }
                content += "\n";
            }
        }

        textEdit->setText(content);
        currentFilePath = filePath;

        // 保存当前文件路径
        QSettings settings("MyCompany", "ExcelReaderApp");
        settings.setValue("lastFilePath", currentFilePath);
    }

    void newExcel() {
        // 清空文本编辑框
        textEdit->clear();

        // 重置当前文件路径
        currentFilePath = "";

        // 提示用户
        QMessageBox::information(this, "新建文件", "已新建一个空白 Excel 文件。");
    }

    void saveExcel() {
        if (currentFilePath.isEmpty()) {
            // 如果当前没有打开的文件，则提示用户选择保存路径
            QString filePath = QFileDialog::getSaveFileName(this, "保存 Excel 文件", "", "Excel 文件 (*.xlsx)");
            if (filePath.isEmpty()) {
                return;
            }
            currentFilePath = filePath;
        }

        QXlsx::Document xlsx;
        QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
        QString content = textEdit->toPlainText();

        QStringList lines = content.split("\n");
        int row = 1;
        for (const QString &line : lines) {
            if (row > maxRows) {
                QMessageBox::warning(this, "输入错误", "超过最大行数限制！");
                return;
            }
            QStringList columns = line.split("\t");
            int col = 1;
            for (const QString &cell : columns) {
                if (col > maxCols) {
                    QMessageBox::warning(this, "输入错误", "超过最大列数限制！");
                    return;
                }
                sheet->write(row, col, cell);
                col++;
            }
            row++;
        }

        if (xlsx.saveAs(currentFilePath)) {
            QMessageBox::information(this, "保存成功", "Excel 文件已保存！");
        } else {
            QMessageBox::warning(this, "错误", "保存 Excel 文件失败！");
        }

        // 保存当前文件路径
        QSettings settings("MyCompany", "ExcelReaderApp");
        settings.setValue("lastFilePath", currentFilePath);
    }

private:
    QTextEdit *textEdit;
    QString currentFilePath;
    int maxRows;
    int maxCols;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ExcelReaderApp reader;
    reader.show();
    return app.exec();
}
