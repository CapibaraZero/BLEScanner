/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2023 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "BLEScanner.hpp"
#include "posixsd.hpp"

#define SCAN_FILENAME String(String("/bluetooth/scan_") + millis() + String(".json"))

BLEScanner::BLEScanner(int scan_time)
{
    // advertisements from the same address will be reported only once,
    // except if the data in the advertisement has changed
    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DATA_DEVICE);
    NimBLEDevice::init(""); // Init BLE stack
    adv_device_callback = new AdvertisedScannedDeviceCallback();

    create_scan();
    start_scan(scan_time);
}

BLEScanner::~BLEScanner()
{
    pBLEScan->stop();
    pBLEScan->clearResults();
}

void BLEScanner::save_to_sd(FS sd, DynamicJsonDocument result) {
    File file = open(SCAN_FILENAME, "w");
    serializeJson(result, file);
    file.close();
}

void BLEScanner::create_scan() {
    pBLEScan = NimBLEDevice::getScan(); //create new scan

    // Set the callback for when devices are discovered, no duplicates.
    adv_device_callback->begin();   // Clear previous results, if any
    pBLEScan->setAdvertisedDeviceCallbacks(adv_device_callback);

    pBLEScan->setActiveScan(true); // Set active scanning, this will get more data from the advertiser.
    pBLEScan->setInterval(97); // How often the scan occurs / switches channels; in milliseconds,
    pBLEScan->setWindow(37);  // How long to scan during the interval; in milliseconds.
    pBLEScan->setMaxResults(0); // do not store the scan results, use callback only.
}

inline void BLEScanner::start_scan(int scan_time) {
    pBLEScan->start(scan_time);
}

void BLEScanner::restart_scan(int scan_time) {
    create_scan();
    start_scan(scan_time);
}