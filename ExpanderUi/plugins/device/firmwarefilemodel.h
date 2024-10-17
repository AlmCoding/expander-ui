#ifndef FIRMWAREFILEMODEL_H
#define FIRMWAREFILEMODEL_H

#include <QAbstractListModel>
#include <QObject>

class FirmwareFileModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(
        QString firmwareDirectory READ getFirmwareDirectory WRITE setFirmwareDirectory NOTIFY firmwareDirectoryChanged)
    Q_PROPERTY(int selectedFileIdx READ getSelectedFileIdx WRITE setSelectedFileIdx NOTIFY selectedFileIdxChanged)
    Q_PROPERTY(int fileCount READ getFileCount NOTIFY fileCountChanged)

   public:
    explicit FirmwareFileModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QString getFirmwareDirectory() const { return firmware_directory_; }
    int getSelectedFileIdx() const { return selected_file_idx_; }
    int getFileCount() const { return files_.size(); }

   public slots:
    void setFirmwareDirectory(const QString& path);
    void setSelectedFileIdx(int idx);

    QString getSelectedFile() const;
    void refresh();

   signals:
    void firmwareDirectoryChanged(const QString& path);
    void selectedFileIdxChanged(int idx);
    void fileCountChanged(int count);

   private:
    QList<QString> files_;
    int selected_file_idx_ = 0;
    // bool update_index_ = false;
    QString firmware_directory_;
};

#endif  // FIRMWAREFILEMODEL_H
