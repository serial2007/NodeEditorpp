#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include "FxData.hpp"
#include <iostream>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class QLineEdit;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class FxSourceModel: public NodeDelegateModel
{
    Q_OBJECT

public:
    FxSourceModel();

    virtual ~FxSourceModel() {}

public:
    QString caption() const override { return QStringLiteral("FxSourceModel"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("FxSourceModel"); }

public:
    QJsonObject save() const override;

    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}

    QWidget *embeddedWidget() override;

public:
    void setData(uint64_t data);

private Q_SLOTS:

    void onTextEdited(QString const &string);

private:
    std::shared_ptr<FxData> _data;

    QLineEdit *_lineEdit;
};
