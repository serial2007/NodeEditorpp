#pragma once

#include "DecimalData.hpp"
#include "FxData.hpp"
#include "MathOperationDataModel.hpp"

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class FxExampleModel : public NodeDelegateModel
{
public:
    ~FxExampleModel() = default;

public:
    QString caption() const override { return QStringLiteral("FxExampleModel"); }

    QString name() const override { return QStringLiteral("FxExampleModel"); }

private:
    void compute()
    {
        PortIndex const outPortIndex = 0;

        auto n0 = din0.lock();
        auto n1 = din1.lock();

        if (n0 && n1) {
            dout = std::make_shared<FxData>();
        } else {
            dout.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }


public:
    std::weak_ptr<DecimalData> din0;
    std::weak_ptr<FxData> din1;
    std::shared_ptr<FxData> dout;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override {
        if (portType == PortType::In) {
            if (portIndex == 0) return DecimalData().type();
            else return FxData().type();
        }else return FxData().type();
    }
    void setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex) override {
        if (!data) {
            Q_EMIT dataInvalidated(0);
        }

        if (portIndex == 0) {
            din0 = std::dynamic_pointer_cast<DecimalData>(data);
        } else {
            din1 = std::dynamic_pointer_cast<FxData>(data);
        }
        compute();
    }

    std::shared_ptr<NodeData> outData(PortIndex const port) override {
        return dout;
    }

    QWidget *embeddedWidget() override {
        return nullptr;
    }

    bool resizable() const override{ return false; }

    unsigned int nPorts(PortType portType) const override
    {
        unsigned int result;

        if (portType == PortType::In)
            result = 2;
        else
            result = 1;

        return result;
    }

};
