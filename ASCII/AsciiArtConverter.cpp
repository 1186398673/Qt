// AsciiArtConverter.cpp
#include "AsciiArtConverter.h"
#include <QImage>
#include <QString>

AsciiArtConverter::AsciiArtConverter() {
    // 定义字符集，从密集到稀疏
    asciiChars = "@%#*+=-:. ";
}

QString AsciiArtConverter::convertToAscii(const QPixmap &pixmap, int width) {
    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    image = image.convertToFormat(QImage::Format_Grayscale8); // 转换为灰度图

    // 调整图片大小
    int height = (width * image.height()) / image.width();
    QImage resizedImage = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QString asciiArt;
    for (int y = 0; y < resizedImage.height(); y++) {
        for (int x = 0; x < resizedImage.width(); x++) {
            // 获取像素的亮度值 (0-255)
            int gray = qGray(resizedImage.pixel(x, y));
            // 根据亮度选择对应的字符
            int index = (gray / 255.0) * (asciiChars.length() - 1);
            asciiArt += asciiChars[index];
        }
        asciiArt += "\n"; // 换行
    }

    return asciiArt;
}
