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

#include "AdvertisedScannedDeviceCallback.hpp"

void AdvertisedScannedDeviceCallback::onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    DynamicJsonDocument ble_device( (advertisedDevice->getPayloadLength() * 2) + advertisedDevice->getAdvLength() + 200);
    DynamicJsonDocument advertisement_data(advertisedDevice->getAdvLength());

    Serial0.println("Device advertised! Writing to JSON");
    devices++;

    ble_device["address"] = advertisedDevice->getAddress().toString();
    ble_device["payload"] = advertisedDevice->getPayload();

    if(advertisedDevice->haveName())
        ble_device["name"] = advertisedDevice->getName();
    
    if(advertisedDevice->haveRSSI())
        ble_device["rssi"] = advertisedDevice->getRSSI();

    if(advertisedDevice->haveAppearance())
        ble_device["appearance"] = advertisedDevice->getAppearance();
    
    if(advertisedDevice->haveManufacturerData())
        ble_device["manufacturer_data"] = advertisedDevice->getManufacturerData();
    
    if(advertisedDevice->haveURI())
        ble_device["uri"] = advertisedDevice->getURI();

    if(advertisedDevice->haveServiceData()){
        ble_device["service_data"] = advertisedDevice->getServiceData();
        ble_device["service_data_uuid"] = advertisedDevice->getServiceDataUUID().toString();
    }
    
    if(advertisedDevice->haveServiceUUID())
        ble_device["service_uuid"] = advertisedDevice->getServiceUUID().toString();
    
    if(advertisedDevice->haveTXPower())
        ble_device["tx_power"] = advertisedDevice->getTXPower();

    advertisement_data["adv_type"] = advertisedDevice->getAdvType();
    advertisement_data["adv_length"] = advertisedDevice->getAdvLength();

    if(advertisedDevice->haveAdvInterval())
        advertisement_data["adv_interval"] = advertisedDevice->getAdvInterval();

    ble_device.add(advertisement_data);

    advertised_devices.add(ble_device);
}
