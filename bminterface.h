#pragma once

#include <QObject>

class BMInterface
{
public:
    virtual bool onPropertyChange(QString property, QJsonValue value)=0;
};

