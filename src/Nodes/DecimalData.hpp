#pragma once

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DecimalData : public NodeData
{
public:
    DecimalData()
        : _data(0.0)
    {}

    DecimalData(double const number)
        : _data(number)
    {}

    NodeDataType type() const override { return NodeDataType{"decimal", "Decimal"}; }

    double number() const { return _data; }

    QString toString() const override{
        return QString::number(_data, 'f');
    }
    void fromString(QString st) override{
        this->_data = st.toDouble();
    }
private:
    double _data;
};
