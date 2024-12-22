#pragma once
#include <QtNodes/NodeDelegateModel>
#include <QtCore/QObject>

class FxData : public QtNodes::NodeData
{
public:
    FxData()
    {
        this->data = 0ULL;
    }
    FxData(uint64_t a) {
        this->data = a;
    }

    QtNodes::NodeDataType type() const override { return QtNodes::NodeDataType{"fxdata", "FxData"}; }

    uint64_t number() const { return data; }

    QString numberAsText() const { return QString::number(114.0, 'f'); }

    QString toString() const override{
        return QString::number(data);
    }
    void fromString(QString st) override{
        this->data = st.toULongLong();
    }
public:
    uint64_t data;
};


