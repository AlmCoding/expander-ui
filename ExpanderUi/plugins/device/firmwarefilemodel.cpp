#include "firmwarefilemodel.h"
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
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
    evaluateNewerFirmwareSelected();
}

void FirmwareFileModel::setInstalledFirmwareVersion(const QString& version) {
    if (installed_firmware_version_ == version) {
        return;
    }

    installed_firmware_version_ = version;
    evaluateNewerFirmwareSelected();
}

QString FirmwareFileModel::getSelectedFile() const {
    if (selected_file_idx_ >= 0 && selected_file_idx_ < files_.size()) {
        return firmware_directory_ + "/" + files_.at(selected_file_idx_);
    }
    return QString{};
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

bool FirmwareFileModel::parseVersion(const QString& filename, Version& version) const {
    QRegularExpression re{ R"((\d+)\.(\d+)\.(\d+))" };
    QRegularExpressionMatch match = re.match(filename);

    if (match.hasMatch() == true) {
        version.major = match.captured(1).toInt();
        version.minor = match.captured(2).toInt();
        version.patch = match.captured(3).toInt();
        return true;
    }

    return false;
}

void FirmwareFileModel::evaluateNewerFirmwareSelected() {
    bool newer_selected = false;
    QString selected_file = getSelectedFile();

    Version selected_version = {};
    Version installed_version = {};

    if (installed_firmware_version_ != "N/A") {
        parseVersion(installed_firmware_version_, installed_version);
        parseVersion(selected_file, selected_version);

        // Compare the selected version with the installed version
        if (selected_version.major > installed_version.major) {
            newer_selected = true;
        } else if (selected_version.major == installed_version.major) {
            if (selected_version.minor > installed_version.minor) {
                newer_selected = true;
            } else if (selected_version.minor == installed_version.minor) {
                if (selected_version.patch > installed_version.patch) {
                    newer_selected = true;
                }
            }
        }
    }

    if (newer_version_selected_ != newer_selected) {
        newer_version_selected_ = newer_selected;
        emit newerVersionSelectedChanged(newer_version_selected_);
    }
}
