import QtQuick
import expander.I2cConfig
import expander.I2cRequestModel
import expander.I2cRequestForm


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
            if (i2cRequestForm.visible == true) {
                i2cRequestForm.loadRequest(i2cRequestModel.getSelectedRequest());
            }
        }
    }

    property I2cRequestForm i2cRequestForm: I2cRequestForm {
        id: i2cRequestForm
        onRequestChanged: function(request) {
            console.log("Save request");
            i2cRequestModel.updateSelectedRequest(request);
        }
    }

    function addNewRequest() {
        console.log("Add new request");
        i2cRequestModel.addNewRequest(i2cRequestModel.selectedRequestIdx);
        i2cRequestForm.visible = true;
    }

    // function saveRequest() {
    // }

    function clearRequest() {
        i2cRequestForm.clearRequest();
    }

}
