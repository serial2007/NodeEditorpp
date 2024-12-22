#include "FxDataDisplay.hpp"

#include <QtWidgets/QLabel>

FxDisplayModel::FxDisplayModel()
    : _label{nullptr}
{}

unsigned int FxDisplayModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 1;
        break;

    case PortType::Out:
        result = 0;

    default:
        break;
    }

    return result;
}

NodeDataType FxDisplayModel::dataType(PortType, PortIndex) const
{
    return FxData().type();
}

std::shared_ptr<NodeData> FxDisplayModel::outData(PortIndex)
{
    std::shared_ptr<NodeData> ptr;
    return ptr;
}

void FxDisplayModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    _data = std::dynamic_pointer_cast<FxData>(data);

    if (!_label)
        return;

    if (_data) {
        _label->setText(_data->toString());
    } else {
        _label->clear();
    }

    _label->adjustSize();
}

QWidget *FxDisplayModel::embeddedWidget()
{
    if (!_label) {
        _label = new QLabel();
        _label->setMargin(3);
    }

    return _label;
}

uint64_t FxDisplayModel::data() const
{
    if (_data)
        return _data->number();

    return 0.0;
}
