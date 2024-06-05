#include "interfaceexpander.h"

InterfaceExpander::InterfaceExpander(QObject* parent) : QObject{ parent } {

    device_com_ = new DeviceCom{this};

    device_com_->start();
}
