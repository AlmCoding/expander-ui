#ifndef INTERFACEEXPANDER_H
#define INTERFACEEXPANDER_H

#include <QObject>
#include "plugins/device/devicecom.h"

class InterfaceExpander : public QObject {
    Q_OBJECT
   public:
    explicit InterfaceExpander(QObject* parent = nullptr);

   signals:

   private:
    DeviceCom* device_com_ = nullptr;
};

#endif  // INTERFACEEXPANDER_H
