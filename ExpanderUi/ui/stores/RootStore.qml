import QtQuick
import expander.I2cConfig
import expander.I2cRequestModel
import expander.I2cRequestForm
import expander.I2cLogModel
import expander.InterfaceExpander
import expander.ComPortModel

Item {
    property I2cConfig i2cConfig1: I2cConfig {
        id: i2cConfig1
        slaveAddr: "0x001"
        memAddrWidth: 1 // Byte
        slaveAddrWidth: 7 // Bits
    }

    property I2cConfig i2cConfig2: I2cConfig {
        id: i2cConfig2
        slaveAddr: "0x002"
        memAddrWidth: 1 // Byte
        slaveAddrWidth: 7 // Bits
    }

    property I2cRequestModel i2cRequestModel: I2cRequestModel {
        id: i2cRequestModel
        onSelectedRequestIdxChanged: function(idx) {
            console.log("Selected idx: ", idx);
            i2cRequestForm.externalUpdate = true; // Avoid binding loop
            i2cRequestForm.loadRequest(i2cRequestModel.getSelectedRequest());
            i2cRequestForm.externalUpdate = false;
        }
    }

    property I2cRequestForm i2cRequestForm: I2cRequestForm {
        id: i2cRequestForm
        onRequestChanged: function(request) {
            console.log("Update request");
            i2cRequestModel.updateSelectedRequest(request);
        }
    }

    function addNewRequest() {
        console.log("Add request");
        i2cRequestModel.addNewRequest(i2cRequestModel.selectedRequestIdx);
        i2cRequestForm.visible = true;
    }

    function deleteRequest() {
        console.log("Delete request: ", i2cRequestModel.selectedRequestIdx);
        i2cRequestModel.deleteRequest(i2cRequestModel.selectedRequestIdx);

        if (i2cRequestModel.getRequestCount() === 0) {
            i2cRequestForm.visible = false;
        }
    }

    function clearRequest() {
        console.log("Clear request: ", i2cRequestModel.selectedRequestIdx);
        i2cRequestForm.externalUpdate = true; // Avoid binding loop
        i2cRequestForm.clearRequest();
        i2cRequestForm.externalUpdate = false;
    }

    property I2cLogModel i2cLogModel: I2cLogModel {
        id: i2cLogModel
    }

    property ComPortModel comPortModel: ComPortModel {
        id: comPortModel
    }

    property InterfaceExpander interfaceExpander: InterfaceExpander {
        id: interfaceExpander
    }
}
