#include "basepainter.h"
#include "elementaryblock.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QStringList>
#include <QDebug>
BasePainter::BasePainter(QString blockFile)
{
    loadBlocks(blockFile);
}

bool BasePainter::check()
{
    return true;
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

        ElementaryBlock *eBlock = new ElementaryBlock(block["image"].toString(), block["char"].toString()[0], block["level"].toInt());
        blockList.insert(block["char"].toString()[0], eBlock);
    }
    return true;
}

BasePainter::~BasePainter(){
    foreach (ElementaryBlock *value, blockList)
        delete value;
}
