#ifndef COMPORTMODEL_H
#define COMPORTMODEL_H

#include <QAbstractListModel>
#include <QSerialPortInfo>
#include <QTimer>

class ComPortModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int selectedPortIdx READ getSelectedPortIdx WRITE setSelectedPortIdx NOTIFY selectedPortIdxChanged)
    Q_PROPERTY(int portCount READ getPortCount NOTIFY portCountChanged)

   public:
    explicit ComPortModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    int getSelectedPortIdx() const { return selected_port_idx_; }
    int getPortCount() const { return ports_.size(); }

   public slots:
    void setSelectedPortIdx(int idx);
    QSerialPortInfo getSelectedPort() const;

   signals:
    void selectedPortIdxChanged(int idx);
    void portCountChanged(int count);

   private:
    static constexpr int PortUpdateIntervalMs = 2000;

    void updatePorts();

    QList<QSerialPortInfo> ports_;
    int selected_port_idx_ = 0;
    QTimer* timer_ = nullptr;
    bool update_index_ = false;
};

#endif  // COMPORTMODEL_H
