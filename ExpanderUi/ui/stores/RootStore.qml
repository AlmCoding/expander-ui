import QtQuick
import expander.models
import expander.InterfaceExpander

Item {
    property I2cLogModel i2cLogModel: I2cLogModel {
        id: i2cLogModel
    }

    property ComPortModel comPortModel: ComPortModel {
        id: comPortModel
    }

    property InterfaceExpander interfaceExpander: InterfaceExpander {
        id: interfaceExpander
    }

    property I2cStore i2cStore: I2cStore {
        id: i2cStore
    }

    function applyI2cConfig() {
        console.log("Apply I2c Config");
        let config0 = i2cStore.i2cConfigForm0.getConfig();
        let config1 = i2cStore.i2cConfigForm1.getConfig();

        interfaceExpander.sendI2cConfig(config0);
        interfaceExpander.sendI2cConfig(config1);
    }

    function sendI2cRequest() {
        console.log("Send I2c Request");
        let request = i2cStore.i2cRequestModel.getSelectedRequest();

        interfaceExpander.sendI2cRequest(request);
    }
}
