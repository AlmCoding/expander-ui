import QtQuick
import expander.models
import expander.InterfaceExpander
import expander.containers.types
import expander.FirmwareDownloader

Item {
    property ComPortModel comPortModel: ComPortModel {
        id: comPortModel
    }

    property FirmwareFileModel firmwareFileModel: FirmwareFileModel {
        id: firmwareFileModel
        firmwareDirectory: constants.firmwareDirectory
        installedFirmwareVersion: interfaceExpander.fwVersion
    }

    // Download firmware from internet
    property FirmwareDownloader firmwareDownloader: FirmwareDownloader {
        id: firmwareDownloader
        firmwareDirectory: constants.firmwareDirectory
        onFirmwareDownloaded: function() {
            firmwareFileModel.refresh();
        }
    }

    property InterfaceExpander interfaceExpander: InterfaceExpander {
        id: interfaceExpander
        onIsConnectedChanged: function() {
            if (isConnected === true) {
                // Request device info
                interfaceExpander.sendCtrlGetDeviceInfo();

                // Send i2c configurations
                let config0 = i2cStore.i2cConfigForm0.getConfig();
                interfaceExpander.sendI2cConfig(config0);
                let config1 = i2cStore.i2cConfigForm1.getConfig();
                interfaceExpander.sendI2cConfig(config1);
            }
        }
        Component.onCompleted: function() {
            setI2cLogModel(i2cStore.i2cLogModel);
        }
    }

    property I2cStore i2cStore: I2cStore {
        id: i2cStore
    }

    function applyI2cConfig() {
        if (interfaceExpander.isConnected === false) {
            return;
        }

        var config;
        if (i2cStore.selectedInterface === I2cTypes.I2c0) {
            console.log("Apply I2c0 Config");
            config = i2cStore.i2cConfigForm0.getConfig();
        } else {
            console.log("Apply I2c1 Config");
            config = i2cStore.i2cConfigForm1.getConfig();
        }

        interfaceExpander.sendI2cConfig(config);
    }

    function sendI2cRequest() {
        console.log("Send I2c Request");
        let request = i2cStore.i2cRequestModel.getSelectedRequest();

        interfaceExpander.sendI2cRequest(request, i2cStore.selectedInterface);
    }
}
