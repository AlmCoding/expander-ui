#ifndef I2CLOGMODEL_H
#define I2CLOGMODEL_H

#include <QObject>

class I2cLogModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int selectedLogIdx READ getSelectedLogIdx WRITE setSelectedLogIdx NOTIFY selectedLogIdxChanged)

   public:
    explicit I2cLogModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    int getSelectedLogIdx() const { return selected_log_idx_; }

   signals:

   private:
    enum ModelRoles {
        TimeRole = Qt::UserRole + 1,
        InterfaceRole,
        TypeRole,
        NameRole,
        SlaveAddrRole,
        SizeRole,
        DataRole,
    };
    const QHash<int, QByteArray> role_names_{
        { TypeRole, "type" },       { NameRole, "name" }, { RwRole, "rw" },     { SlaveAddrRole, "slaveAddr" },
        { MemAddrRole, "memAddr" }, { SizeRole, "size" }, { DataRole, "data" },
    };

    QList<I2cRequest> logs_;
    int selected_log_idx_ = 0;
};

#endif  // I2CLOGMODEL_H
