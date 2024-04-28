import QtQuick

ListModel {
    ListElement {
        req_type: "W"
        slave_addr: "0x02"
        mem_addr: "0x42"
        data_size: "42 Bytes"
        write_data: "asjxekKejdjk"
    }
    ListElement {
        req_type: "R"
        slave_addr: "0x02"
        mem_addr: "0x42"
        data_size: "42 Bytes"
        write_data: ""
    }
    ListElement {
        req_type: "W"
        slave_addr: "0x02"
        mem_addr: "0x02"
        data_size: "12 Bytes"
        write_data: "asjxekKejdjk"
    }
}
