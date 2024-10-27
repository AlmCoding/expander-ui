#ifndef FIRMWAREFILEMODEL_H
#define FIRMWAREFILEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QString>

class FirmwareFileModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(
        QString firmwareDirectory READ getFirmwareDirectory WRITE setFirmwareDirectory NOTIFY firmwareDirectoryChanged)
    Q_PROPERTY(int selectedFileIdx READ getSelectedFileIdx WRITE setSelectedFileIdx NOTIFY selectedFileIdxChanged)
    Q_PROPERTY(int fileCount READ getFileCount NOTIFY fileCountChanged)
    Q_PROPERTY(QString installedFirmwareVersion WRITE setInstalledFirmwareVersion)
    Q_PROPERTY(bool newerVersionSelected READ getNewerVersionSelected NOTIFY newerVersionSelectedChanged)

   public:
    explicit FirmwareFileModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QString getFirmwareDirectory() const { return firmware_directory_; }
    int getSelectedFileIdx() const { return selected_file_idx_; }
    int getFileCount() const { return files_.size(); }
    bool getNewerVersionSelected() const { return newer_version_selected_; }

   public slots:
    void setFirmwareDirectory(const QString& path);
    void setSelectedFileIdx(int idx);
    void setInstalledFirmwareVersion(const QString& version);
    QString getSelectedFile() const;
    void refresh();

   signals:
    void firmwareDirectoryChanged(const QString& path);
    void selectedFileIdxChanged(int idx);
    void fileCountChanged(int count);
    void newerVersionSelectedChanged(bool newer);

   private:
    struct Version {
        int major = 0;
        int minor = 0;
        int patch = 0;
    };
    bool parseVersion(const QString& filename, Version& version) const;
    void evaluateNewerFirmwareSelected();

    QList<QString> files_;
    int selected_file_idx_ = 0;
    QString firmware_directory_;
    QString installed_firmware_version_;
    bool newer_version_selected_ = false;
};

#endif  // FIRMWAREFILEMODEL_H
