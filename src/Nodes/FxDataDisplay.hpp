#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>

#include "FxData.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class QLabel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class FxDisplayModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    FxDisplayModel();

    ~FxDisplayModel() = default;

public:
    QString caption() const override { return QStringLiteral("FxResult"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("FxResult"); }

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

    QWidget *embeddedWidget() override;

    uint64_t data() const;

private:
    std::shared_ptr<FxData> _data;

    QLabel *_label;
};
