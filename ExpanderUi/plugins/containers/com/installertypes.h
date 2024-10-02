#ifndef INSTALLERTYPES_H
#define INSTALLERTYPES_H

#include <QObject>

namespace InstallerTypes {
Q_NAMESPACE

enum class State {
    Idle = 0,
    Connect,
    Download,
    Success,
    Error,
};

Q_ENUM_NS(State)

}  // namespace InstallerTypes

#endif  // INSTALLERTYPES_H
