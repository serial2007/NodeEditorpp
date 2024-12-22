#include "FxDataSource.hpp"
#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

FxSourceModel::FxSourceModel()
    : _lineEdit{nullptr}
    , _data(std::make_shared<FxData>())
{}

QJsonObject FxSourceModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["FxData"] = _data->toString();

    return modelJson;
}

void FxSourceModel::load(QJsonObject const &p)
{
    QJsonValue v = p["FxData"];

    if (!v.isUndefined()) {
        QString strNum = v.toString();

        bool ok;
        uint64_t d = strNum.toULongLong(&ok);
        if (ok) {
            _data = std::make_shared<FxData>(d);

            if (_lineEdit)
                _lineEdit->setText(strNum);
        }
    }
}

unsigned int FxSourceModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

void FxSourceModel::onTextEdited(QString const &str)
{
    bool ok = false;

    uint64_t number = str.toULongLong(&ok);

    if (ok) {
        _data = std::make_shared<FxData>(number);

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType FxSourceModel::dataType(PortType, PortIndex) const
{
    return FxData().type();
}

std::shared_ptr<NodeData> FxSourceModel::outData(PortIndex)
{
    return _data;
}

QWidget *FxSourceModel::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit();

        _lineEdit->setValidator(new QDoubleValidator());
        _lineEdit->setMaximumSize(_lineEdit->sizeHint());

        connect(_lineEdit, &QLineEdit::textChanged, this, &FxSourceModel::onTextEdited);

        _lineEdit->setText(_data->toString());
    }

    return _lineEdit;
}

void FxSourceModel::setData(uint64_t data)
{
    _data = std::make_shared<FxData>(data);

    Q_EMIT dataUpdated(0);

    if (_lineEdit)
        _lineEdit->setText(_data->toString());
}
