import QtQuick
import expander.forms
import expander.models
import expander.containers.i2c

Item {
    property var selectedInterface: I2cConfigTypes.I2c0;

    property I2cConfigForm i2cConfigForm0: I2cConfigForm {
        id: i2cConfigForm0
        i2cId: I2cConfigTypes.I2c0
        slaveAddr: "0x001"
        memAddrWidth: I2cConfigTypes.OneByte
        slaveAddrWidth: I2cConfigTypes.SevenBit
    }

    property I2cConfigForm i2cConfigForm1: I2cConfigForm {
        id: i2cConfigForm1
        i2cId: I2cConfigTypes.I2c1
        slaveAddr: "0x002"
        memAddrWidth: I2cConfigTypes.OneByte
        slaveAddrWidth: I2cConfigTypes.SevenBit
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
}
