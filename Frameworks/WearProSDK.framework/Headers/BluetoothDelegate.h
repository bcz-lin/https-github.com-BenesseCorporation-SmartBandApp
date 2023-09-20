//
//  BluetoothDelegate.h
//  Bluetooth_Example
//
//  Created by lemo. on 2019/5/14.
//  Copyright © 2019 chentingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BLEPublic.h"
#import "PeripheralModel.h"

NS_ASSUME_NONNULL_BEGIN

@class BluetoothManager;

@protocol BluetoothDelegate <NSObject>

@optional
/**
 * @brief 蓝牙管理状态 | Bluetooth management status
 * @param manager HPlus蓝牙管理中心 | HPlus Bluetooth Management Center
 * @param state 状态 | Status
 */
- (void)bluetoothManager:(BluetoothManager *)manager
          didUpdateState:(BLE_MANAGER_STATE)state;

/**
 * @brief 扫描所有外围设备 | Scan all peripherals
 * @param manager HPlus蓝牙管理中心 | HPlus Bluetooth Management Center
 * @param allDevices 扫描所有外围设备(包括OTA设备集合) | Scan all peripherals (including OTA device collections)
 * @param otaDevices OTA 设备集合 | OTA Device Collection
 */
- (void)bluetoothManager:(BluetoothManager *)manager
              allDevices:(NSArray <PeripheralModel *>*)allDevices
              otaDevices:(NSArray <PeripheralModel *>*)otaDevices;

/**
 * @brief 连接设备成功回调 | Connected device successfully callback
 * @param manager HPlus蓝牙管理中心 | HPlus Bluetooth Management Center
 * @param centerManager 蓝牙管理中心 | Bluetooth Management Center
 * @param peripheral 外围设备 | Peripherals
 * @param isOtaMode 连接是否在OTA模式 | Is the connection in OTA mode?
 */
- (void)bluetoothManager:(BluetoothManager *)manager
           centerManager:(CBCentralManager *)centerManager
    didConnectPeripheral:(CBPeripheral *)peripheral
               isOatMode:(BOOL)isOtaMode;

/**
 * @brief 连接设备错误回调,当解绑设备断开连接时不会回调此方法
 * Connection Device Error Callback,This method is not called back when the unbound device is disconnected.
 * @param manager HPlus蓝牙管理中心 | HPlus Bluetooth Management Center
 * @param error 错误信息 | Error message
 */
- (void)bluetoothManager:(BluetoothManager *)manager
  connectPeripheralError:(NSError *)error;

/**
 * @brief 设备断开连接回调 | Device disconnect callback
 * @param manager HPlus蓝牙管理中心 | HPlus Bluetooth Management Center
 * @param centerManager 蓝牙管理中心 | Bluetooth Management Center
 * @param peripheral 外围设备 | Peripherals
 * @param isOtaMode 连接是否在OTA模式 | Is the connection in OTA mode?
 */
- (void)bluetoothManager:(BluetoothManager *)manager
           centerManager:(CBCentralManager *)centerManager
    disConnectPeripheral:(CBPeripheral *)peripheral
               isOatMode:(BOOL)isOtaMode;

@end

NS_ASSUME_NONNULL_END
