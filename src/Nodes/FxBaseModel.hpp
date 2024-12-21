#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <FxData.hpp>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;


/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class FxBaseModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    ~FxBaseModel() = default;

public:
    unsigned int nPorts(PortType portType) const override {
        unsigned int result = 1;

        switch (portType) {
        case PortType::In:
            result = din.size();
            break;

        case PortType::Out:
            result = dout.size();

        default:
            break;
        }

        return result;
    }

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override {
        return FxData().type();
    }

    std::shared_ptr<NodeData> outData(PortIndex port) override{
        return std::static_pointer_cast<NodeData>(dout[0]);
    }

    void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override {
        auto numberData = std::dynamic_pointer_cast<FxData>(data);
        for(unsigned i=din.size(); i<portIndex; i++) {
            din.push_back(std::weak_ptr<FxData>());
        }
        if (!data) {
            Q_EMIT dataInvalidated(0);
        }
        din[portIndex] = numberData;
        compute();
    }

    QWidget *embeddedWidget() override { return nullptr; }

protected:
    virtual void compute() = 0;

protected:
    std::vector<std::weak_ptr<FxData>> din;
    std::vector<std::shared_ptr<FxData>> dout;
};
