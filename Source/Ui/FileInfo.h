#ifndef FILEINFO_H
#define FILEINFO_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class FileInfo : public QWidget {
Q_OBJECT
public:
    QGridLayout *grid;
    FileInfo(QWidget *parent = nullptr);
    QLineEdit *addStringLineEdit(const QString &title, const QString &value);
    QLineEdit *addIntLineEdit(const QString &title, int value);
    QLineEdit *addFloatLineEdit(const QString &title, float value);
    QCheckBox *addCheckBox(const QString &title, bool checked);
public slots:
    void update(const QString &title, const QString &value);
    void update(const QString &title, int value);
    void update(const QString &title, float value);
    void update(const QString &title, bool value);
    void replace(FileInfo *newInfo);
signals:
    void updateInfo(FileInfo *info);
private:
    int rows;
};

#endif // FILEINFO_H
