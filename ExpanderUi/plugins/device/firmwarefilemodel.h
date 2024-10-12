#ifndef FIRMWAREFILEMODEL_H
#define FIRMWAREFILEMODEL_H

#include <QAbstractListModel>
#include <QObject>

class FirmwareFileModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int selectedFileIdx READ getSelectedFileIdx WRITE setSelectedFileIdx NOTIFY selectedFileIdxChanged)
    Q_PROPERTY(int fileCount READ getFileCount NOTIFY fileCountChanged)

   public:
    explicit FirmwareFileModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    int getSelectedFileIdx() const { return selected_file_idx_; }
    int getFileCount() const { return files_.size(); }
    QString getSelectedFile() const;

   public slots:
    void setSelectedFileIdx(int idx);

   signals:
    void selectedFileIdxChanged(int idx);
    void fileCountChanged(int count);

   private:
    void updateFiles();

    QList<QString> files_;
    int selected_file_idx_ = 0;
    bool update_index_ = false;
};

#endif  // FIRMWAREFILEMODEL_H
