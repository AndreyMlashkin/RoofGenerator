#include "basepainter.h"
#include "elementaryblock.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QStringList>
#include <QDebug>

bool BasePainter::check(QString rawString)
{
    if(rawString.length() == 0 || rawString.count("||") || rawString[0] == '|')
        return false;
    return true;
}
bool BasePainter::getIsLoad() const
{
    return isLoad;
}

int BasePainter::loadBlocks(QString blockFile, QString _name)
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

    if(_name != "")
        name = _name;
    isLoad = true;
    return true;
}

QString BasePainter::getName()
{
    return name;
}

BasePainter::BasePainter():
    isLoad(false), name("unnamed style")
{
}

BasePainter::~BasePainter(){
    qDeleteAll( blockList );
    blockList.clear();
}
