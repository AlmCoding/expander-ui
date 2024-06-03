#include "i2clogmodel.h"

I2cLogModel::I2cLogModel(QObject* parent) : QObject{ parent } {}

int I2cLogModel::rowCount(const QModelIndex& parent) const { return logs_.size(); }

QHash<int, QByteArray> I2cLogModel::roleNames() const { return role_names_; }
