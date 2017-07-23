#ifndef ONEXTREEITEM_H
#define ONEXTREEITEM_H
#include <QTreeWidgetItem>
#include <QtEndian>
#include <QMenu>
#include <QMessageBox>
#include <QObject>
#include <QFileDialog>

class OnexTreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
protected:
    QByteArray content;
    QString name;

    QString getSelectedDirectory();
    QString getSaveDirectory(QString filter);
    QMessageBox getMsgBox(QString title, QString message, QMessageBox::Icon icon);
public:
    OnexTreeItem(QString name, QByteArray content = QByteArray());
    QByteArray getContent();
    bool hasParent();
    short fromLittleEndianToShort(QByteArray array);
    int getContentSize();

    virtual QString getName();
    virtual QMenu* getContextMenu();
    virtual QWidget *onClicked() = 0;
    virtual ~OnexTreeItem();

private slots:
    virtual void onExportAll();
    virtual void onExportSingle();
    virtual void onExporSingleRaw();
};

#endif // ONEXTREEITEM_H
