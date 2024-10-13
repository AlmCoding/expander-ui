#include "firmwarefilemodel.h"
#include <QDir>
#include <QFileInfo>

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
    updateFiles();
    emit firmwareDirectoryChanged(firmware_directory_);
}

void FirmwareFileModel::setSelectedFileIdx(int idx) {
    // if (update_index_ == true) {
    //     update_index_ = false;
    //     return;
    // }

    if (idx >= 0 && idx < files_.size()) {
        selected_file_idx_ = idx;
        emit selectedFileIdxChanged(selected_file_idx_);
    }
}

void FirmwareFileModel::updateFiles() {
    if (QDir().exists(firmware_directory_) == false) {
        qDebug() << "Firmware directory does not (yet) exist: " << firmware_directory_;
        return;
    }

    // if (files_.size() == 0) {
    //     update_index_ = true;
    // }

    // List files in directory
    QFileInfoList files = QDir(firmware_directory_).entryInfoList(QDir::Files);

    beginResetModel();
    files_.clear();
    for (const QFileInfo& file : files) {
        files_.append(file.fileName());
    }
    endResetModel();

    // if (update_index_ == true) {
    selected_file_idx_ = 0;
    emit selectedFileIdxChanged(selected_file_idx_);
    //}
    emit fileCountChanged(files_.size());
}
