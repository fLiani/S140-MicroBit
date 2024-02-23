#include "MicroBit.h"

MicroBit uBit;

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    // ble_gap_scan_params_t scan_params = {
    //     .extended = 0,
    //     .report_incomplete_evts = 1,
    //     .active = 1,
    //     .filter_policy = 0,
    //     .interval = 0x0004,
    //     .window = 0x4000,
    //     .timeout = 0
    // };

    // const ble_data_t adv_report_buffer[BLE_GAP_SCAN_BUFFER_MAX] = {};

    // uint32_t error_code = sd_ble_gap_scan_start(&scan_params, adv_report_buffer);

    // DMESG("Error Code: %d", error_code);
}