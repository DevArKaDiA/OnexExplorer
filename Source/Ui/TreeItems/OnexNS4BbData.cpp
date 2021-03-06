#include "OnexNS4BbData.h"

OnexNS4BbData::OnexNS4BbData(QString name, QByteArray content, NosZlibOpener *opener, int id,
                             int creationDate, bool compressed)
        : OnexTreeImage(name, opener, content, id, creationDate, compressed) {
    if (content.isEmpty())
        this->content = QByteArrayLiteral("\x00\x00\x00\x00");
}

OnexNS4BbData::OnexNS4BbData(QJsonObject jo, NosZlibOpener *opener, const QString &directory) : OnexTreeImage(jo["ID"].toString(), opener) {
    this->content = QByteArrayLiteral("\x00\x00\x00\x00");
    setId(jo["ID"].toInt(), true);
    setCreationDate(jo["Date"].toString(), true);
    setCompressed(jo["isCompressed"].toBool(), true);
    onReplace(directory + jo["path"].toString());
}

OnexNS4BbData::~OnexNS4BbData() = default;

QImage OnexNS4BbData::getImage() {
    ImageResolution resolution = this->getResolution();
    return imageConverter->convertBGRA8888_INTERLACED(content, resolution.x, resolution.y, 4);
}

ImageResolution OnexNS4BbData::getResolution() {
    int x = opener->getLittleEndianConverter()->fromShort(content.mid(0, 2));
    int y = opener->getLittleEndianConverter()->fromShort(content.mid(2, 2));
    return ImageResolution{x, y};
}

int OnexNS4BbData::afterReplace(QImage image) {
    QByteArray newContent;
    newContent.push_back(opener->getLittleEndianConverter()->toShort(image.width()));
    newContent.push_back(opener->getLittleEndianConverter()->toShort(image.height()));
    newContent.push_back(imageConverter->toBGRA8888_INTERLACED(image));
    setContent(newContent);
    setWidth(image.width(), true);
    setHeight(image.height(), true);

    emit OnexTreeImage::replaceSignal(this->getImage());
    emit replaceInfo(generateInfos());
    return 1;
}

void OnexNS4BbData::setWidth(int width, bool update) {
    content.replace(0, 2, opener->getLittleEndianConverter()->toShort(width));
    if (update)
            emit changeSignal("Width", width);
}

void OnexNS4BbData::setHeight(int height, bool update) {
    content.replace(2, 2, opener->getLittleEndianConverter()->toShort(height));
    if (update)
            emit changeSignal("Height", height);
}

