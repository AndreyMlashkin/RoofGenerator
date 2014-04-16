#include "basepainter.h"
#include "elementaryblock.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QStringList>
#include <QDebug>

bool BasePainter::check()
{
    return true;
}
bool BasePainter::getIsLoad() const
{
    return isLoad;
}

int BasePainter::loadBlocks(QString blockFile)
{
    QFile jsonFile(blockFile);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return false;
    }
    QJsonParseError error;
    QByteArray saveData = jsonFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));
    if(error.error != QJsonParseError::NoError){
        qDebug()<<error.errorString();
        return false;
    }
    QJsonObject json = loadDoc.object();
    QJsonObject blocks = json["blocks"].toObject();

    foreach(const QString &key, blocks.keys()){
        QJsonObject block = blocks[key].toObject();

        ElementaryBlock *eBlock = new ElementaryBlock(block["image"].toString(), block["char"].toString(), block["level"].toInt());
        blockList.insert(block["char"].toString(), eBlock);
    }
    isLoad = true;
    return true;
}

BasePainter::BasePainter():
    isLoad(false)
{

}

BasePainter::~BasePainter(){
    qDeleteAll( blockList );
    blockList.clear();
}
