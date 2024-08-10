#include "deviceinfo.h"

DeviceInfo::DeviceInfo(int device_type, int hardware_version, int firmware_version_major, int firmware_version_minor,
                       int firmware_version_patch, QString git_hash)
    : device_type_{ device_type },
      hardware_version_{ hardware_version },
      firmware_version_major_{ firmware_version_major },
      firmware_version_minor_{ firmware_version_minor },
      firmware_version_patch_{ firmware_version_patch },
      git_hash_{ git_hash } {}
