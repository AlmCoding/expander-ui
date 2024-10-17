#include "firmwarefilemodel.h"
#include <QDir>
#include <QFileInfo>
#include <algorithm>

FirmwareFileModel::FirmwareFileModel(QObject* parent) : QAbstractListModel{ parent } { files_.clear(); }

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

QString FirmwareFileModel::getSelectedFile() const {
    if (selected_file_idx_ >= 0 && selected_file_idx_ < files_.size()) {
        return firmware_directory_ + "/" + files_.at(selected_file_idx_);
    }
    return QString{};
}

void FirmwareFileModel::setFirmwareDirectory(const QString& path) {
    if (firmware_directory_ == path) {
        return;
    }

    firmware_directory_ = path;
    emit firmwareDirectoryChanged(firmware_directory_);
    refresh();
}

void FirmwareFileModel::setSelectedFileIdx(int idx) {
    if (idx >= 0 && idx < files_.size() && idx != selected_file_idx_) {
        selected_file_idx_ = idx;
        emit selectedFileIdxChanged(selected_file_idx_);
    }
}

void FirmwareFileModel::refresh() {
    if (QDir().exists(firmware_directory_) == false) {
        qDebug() << "Firmware directory does not (yet) exist: " << firmware_directory_;
        return;
    }

    // List files in directory
    QFileInfoList files = QDir(firmware_directory_).entryInfoList(QDir::Files);

    beginResetModel();
    files_.clear();
    for (const QFileInfo& file : files) {
        files_.append(file.fileName());
    }
    std::reverse(files_.begin(), files_.end());
    endResetModel();

    setSelectedFileIdx(0);
    emit fileCountChanged(files_.size());
}
