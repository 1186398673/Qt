#include <QApplication>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>


class ExcelWriterApp : public QWidget {


public:
    ExcelWriterApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("QXlsx 写入示例");
        setFixedSize(300, 200);

        QPushButton *writeButton = new QPushButton("写入 Excel", this);
        connect(writeButton, &QPushButton::clicked, this, &ExcelWriterApp::writeExcel);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(writeButton);
        setLayout(layout);
    }

private slots:
    void writeExcel() {
        // 创建 QXlsx::Document 对象
        QXlsx::Document xlsx;

        // 写入数据到指定单元格
        xlsx.write("A1", "姓名");
        xlsx.write("B1", "年龄");
        xlsx.write("A2", "张三");
        xlsx.write("B2", 25);
        xlsx.write("A3", "李四");
        xlsx.write("B3", 30);

        // 保存 Excel 文件
        bool success = xlsx.saveAs("example.xlsx");
        if (success) {
            qDebug() << "Excel 文件已保存成功！";
        } else {
            qDebug() << "保存 Excel 文件失败！";
        }
    }
};

class ExcelReaderApp : public QWidget {


public:
    ExcelReaderApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("QXlsx 读取示例");
        setFixedSize(300, 200);

        QPushButton *readButton = new QPushButton("读取 Excel", this);
        connect(readButton, &QPushButton::clicked, this, &ExcelReaderApp::readExcel);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(readButton);
        setLayout(layout);
    }

private slots:
    void readExcel() {
        // 打开 Excel 文件
        QXlsx::Document xlsx("example.xlsx");
        if (!xlsx.load()) {
            qDebug() << "无法打开 Excel 文件！";
            return;
        }

        // 读取单元格数据
        QString name1 = xlsx.read("A2").toString();
        int age1 = xlsx.read("B2").toInt();
        QString name2 = xlsx.read("A3").toString();
        int age2 = xlsx.read("B3").toInt();

        qDebug() << "姓名1:" << name1 << "年龄1:" << age1;
        qDebug() << "姓名2:" << name2 << "年龄2:" << age2;
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ExcelWriterApp writer;
    ExcelReaderApp reader;

    writer.show();
    reader.show();
    return app.exec();
}
