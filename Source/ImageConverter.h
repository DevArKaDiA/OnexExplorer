#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H
#include <QImage>
#include <QMap>
#include <QColor>
#include <QDebug>

class ImageConverter
{
private:
    QMap<int, QColor> colors;
public:
    QImage convertGBAR4444(QByteArray& array, int width, int height, int startByte = 0);
    QImage convertBGRA8888(QByteArray& array, int width, int height, int startByte = 0);
    QImage convertARGB555(QByteArray& array, int width, int height, int startByte = 0);
    QImage convertNSTC(QByteArray& array, int width, int height, int startByte = 0);
    QImage convertBGRA8888_INTERLACED(QByteArray& array, int width, int height, int startByte = 0);
    QImage convertBARG4444(QByteArray& array, int width, int height, int startByte = 0);
    QByteArray toGBAR4444(QImage& image);
    QByteArray toNSTC(QImage& image);
    ImageConverter();
};

#endif // IMAGECONVERTER_H
