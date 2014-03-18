#ifndef ROOF_H
#define ROOF_H

#include <QWidget>

namespace Ui
{
    class roof;
}

class roof : public QWidget
{
    Q_OBJECT

public:
    explicit roof(QWidget *parent = 0);
    ~roof();

private:
    Ui::roof *ui;
};

#endif // ROOF_H
