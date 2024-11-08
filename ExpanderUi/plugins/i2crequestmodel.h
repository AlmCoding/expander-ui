#ifndef I2CREQUESTMODEL_H
#define I2CREQUESTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include "plugins/containers/i2c/i2crequest.h"

class I2cRequestModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(
        int selectedRequestIdx READ getSelectedRequestIdx WRITE setSelectedRequestIdx NOTIFY selectedRequestIdxChanged)
    Q_PROPERTY(QString filePath READ getFilePath NOTIFY filePathChanged)

   public:
    explicit I2cRequestModel(QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    Qt::DropActions supportedDropActions() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent,
                  int destinationChild) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    int getSelectedRequestIdx() const { return selected_request_idx_; }

   public slots:
    // void moveItNow(int from, int to) { moveRows(QModelIndex(), from, 1, QModelIndex(), to); }
    void addNewRequest(int template_req_idx);
    void deleteRequest(int request_idx);

    void setSelectedRequestIdx(int idx);
    void setFilePath(QString file_path);
    void updateSelectedRequest(I2cRequest request);

    int getRequestCount() const { return requests_.size(); }
    I2cRequest getSelectedRequest() const { return requests_.at(selected_request_idx_); }
    QString getFilePath() { return file_path_; }

    void saveRequestsToFile(const QString& file_path);
    void loadRequestsFromFile(const QString& file_path);
    void clear();

   signals:
    void selectedRequestIdxChanged(int idx);
    void filePathChanged(QString file_path);

   private:
    enum ModelRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        SlaveAddrRole,
        WriteDataRole,
        SizeRole,
    };
    const QHash<int, QByteArray> role_names_{
        { NameRole, "name" },           { TypeRole, "type" }, { SlaveAddrRole, "slaveAddr" },
        { WriteDataRole, "writeData" }, { SizeRole, "size" },
    };

    QList<I2cRequest> requests_;
    int selected_request_idx_ = 0;
    QString file_path_;
};

#endif  // I2CREQUESTMODEL_H
