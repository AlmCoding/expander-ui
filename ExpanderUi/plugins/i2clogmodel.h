#ifndef I2CLOGMODEL_H
#define I2CLOGMODEL_H

#include <QAbstractListModel>
#include <QFont>
#include <QFontMetrics>
#include "plugins/containers/i2c/i2clog.h"
#include "plugins/containers/i2c/i2cnotification.h"
#include "plugins/containers/i2c/i2crequest.h"

constexpr int LogEntryNameMaxWidth = 150;

class I2cLogModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int selectedLogIdx READ getSelectedLogIdx WRITE setSelectedLogIdx NOTIFY selectedLogIdxChanged)

   public:
    explicit I2cLogModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    int getSelectedLogIdx() const { return selected_log_idx_; }

   public slots:
    void setSelectedLogIdx(int idx);
    void appendNewLog(const I2cRequest& request);
    void appendNewLog(const I2cNotification& notification);

    I2cLog getSelectedLog() const { return logs_.at(selected_log_idx_); }

    void saveLogsToFile(const QString& file_path);
    void loadLogsFromFile(const QString& file_path);
    void clear();

   signals:
    void selectedLogIdxChanged(int idx);

   private:
    enum ModelRoles {
        TimeRole = Qt::UserRole + 1,
        InterfaceRole,
        TypeRole,
        NameRole,
        SlaveAddrRole,
        WriteDataRole,
        WriteDataAsciiRole,
        ReadDataRole,
        ReadDataAsciiRole,
        WriteSizeRole,
        ReadSizeRole,
        SatusRole,
    };
    const QHash<int, QByteArray> role_names_{
        { TimeRole, "time" },
        { InterfaceRole, "interface" },
        { TypeRole, "type" },
        { NameRole, "name" },
        { SlaveAddrRole, "slaveAddr" },
        { WriteDataRole, "writeData" },
        { WriteDataAsciiRole, "writeDataAscii" },
        { ReadDataRole, "readData" },
        { ReadDataAsciiRole, "readDataAscii" },
        { WriteSizeRole, "writeSize" },
        { ReadSizeRole, "readSize" },
        { SatusRole, "status" },
    };
    QString truncateNameString(const QString& str) const;

    QList<I2cLog> logs_;
    int selected_log_idx_ = 0;

    QFontMetrics font_metrics_{ QFont{ "Roboto", 12, QFont::Bold } };
};

#endif  // I2CLOGMODEL_H
