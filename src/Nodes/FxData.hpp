#pragma once
#include <QtNodes/NodeDelegateModel>
#include <QtCore/QObject>

class FxData : public QtNodes::NodeData
{
public:
    FxData()
    {
    }
    FxData(void* a) {
        this->data = a;
    }

    QtNodes::NodeDataType type() const override { return QtNodes::NodeDataType{"fxdata", "FxData"}; }

    void* number() const { return data; }

    QString numberAsText() const { return QString::number(114.0, 'f'); }

public:
    void* data;
};


