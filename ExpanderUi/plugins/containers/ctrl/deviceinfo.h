#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>

class DeviceInfo {
   public:
    DeviceInfo() = default;
    explicit DeviceInfo(int device_type, int hardware_version, int firmware_version_major, int firmware_version_minor,
                        int firmware_version_patch, QString git_hash);

    void setRequestId(int request_id) { request_id = request_id; }
    void setDeviceType(int device_type) { device_type_ = device_type; }
    void setHardwareVersion(int hardware_version) { hardware_version_ = hardware_version; }
    void setFirmwareVersionMajor(int firmware_version_major) { firmware_version_major_ = firmware_version_major; }
    void setFirmwareVersionMinor(int firmware_version_minor) { firmware_version_minor_ = firmware_version_minor; }
    void setFirmwareVersionPatch(int firmware_version_patch) { firmware_version_patch_ = firmware_version_patch; }
    void setGitHash(QString git_hash) { git_hash_ = git_hash; }

    int getRequestId() const { return request_id; }
    int getDeviceType() const { return device_type_; }
    int getHardwareVersion() const { return hardware_version_; }
    int getFirmwareVersionMajor() const { return firmware_version_major_; }
    int getFirmwareVersionMinor() const { return firmware_version_minor_; }
    int getFirmwareVersionPatch() const { return firmware_version_patch_; }
    QString getGitHash() const { return git_hash_; }

   private:
    int request_id = -1;
    int device_type_ = -1;
    int hardware_version_ = -1;
    int firmware_version_major_ = -1;
    int firmware_version_minor_ = -1;
    int firmware_version_patch_ = -1;
    QString git_hash_;
};

#endif  // DEVICEINFO_H
