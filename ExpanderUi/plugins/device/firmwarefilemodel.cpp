#include "firmwarefilemodel.h"

FirmwareFileModel::FirmwareFileModel(QObject* parent) : QAbstractListModel{ parent } { updateFiles(); }

int FirmwareFileModel::rowCount(const QModelIndex& parent) const { return files_.size(); }

QVariant FirmwareFileModel::data(const QModelIndex& index, int role) const {
    if (index.isValid() == false || index.row() >= files_.size()) {
        return QVariant();
    }

    const QString& file = files_.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return QVariant{ file };
        case Qt::EditRole:
            return QVariant{ file };
        default:
            return QVariant{};
    }
}

void FirmwareFileModel::setSelectedFileIdx(int idx) {
    if (update_index_ == true) {
        update_index_ = false;
        return;
    }

    if (idx >= 0 && idx < files_.size()) {
        selected_file_idx_ = idx;
        emit selectedFileIdxChanged(selected_file_idx_);
    }
}

QString FirmwareFileModel::getSelectedFile() const {
    if (selected_file_idx_ >= 0 && selected_file_idx_ < files_.size()) {
        return files_.at(selected_file_idx_);
    }
    return QString{};
}

void FirmwareFileModel::updateFiles() {
    if (files_.size() == 0) {
        update_index_ = true;
    }

    beginResetModel();
    files_.clear();
    files_.append("firmware1.hex");
    files_.append("firmware2.hex");
    files_.append("firmware3.hex");
    endResetModel();

    if (update_index_ == true) {
        selected_file_idx_ = 0;
        emit selectedFileIdxChanged(selected_file_idx_);
    }
    emit fileCountChanged(files_.size());
}
