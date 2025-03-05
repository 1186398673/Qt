#ifndef ASCIIARTCONVERTER_H
#define ASCIIARTCONVERTER_H
#include <QString>
#include <QPixmap>

class AsciiArtConverter {
public:
    AsciiArtConverter();
    QString convertToAscii(const QPixmap &pixmap, int width = 100);

private:
    QString asciiChars; // 字符集，从密集到稀疏
};

#endif // ASCIIARTCONVERTER_H
