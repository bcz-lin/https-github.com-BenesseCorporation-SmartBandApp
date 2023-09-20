//
//  HPlusBluetoothManager.h
//  HPlusBluetooth_Example
//
//  Created by lemo. on 2019/5/14.
//  Copyright © 2019 chentingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "BluetoothDelegate.h"
#import "PeripheralModel.h"


NS_ASSUME_NONNULL_BEGIN

@interface BluetoothManager : NSObject

/**
 设置代理 | Setting up the agent
 */
@property (nonatomic, weak) id<BluetoothDelegate> delegate;

/**
 * 设置扫描过滤信号弱的设备 默认值 80 大于80会被过滤
 * Set the device with weak scan filtering signal. Default value 80 is greater than 80 will be filtered.
 */
@property (nonatomic, assign) NSInteger rssiNum;

/**
 * 发送指令超时时长 默认5秒
 * Send command timeout defaults to 5 seconds by default
 */
@property (nonatomic, assign) NSInteger commandTimeOutNumber;

/**
 蓝牙管理中心 | Bluetooth Management Center
 */
@property (nonatomic, strong) CBCentralManager *centralManager;

/**
 外围设备 | Peripherals
 */
@property (nullable, nonatomic, strong) PeripheralModel *currenPeripheral;

/**
 当前连接设备是否绑定 | Is the current connected device bound?
 */
@property (nonatomic, assign, readonly) BOOL isBind;

/**
 蓝牙是否开启 | Is Bluetooth enabled?
 */
@property (nonatomic, assign, readonly) BOOL poweredOn;

/**
 蓝牙是否连接 | Bluetooth is connected
 */
@property (nonatomic, assign, readonly) BOOL connected;

/**
 * @brief 初始化蓝牙管理中心对象
 * Initialize the Bluetooth Management Center object
 * @return BluetoothManager
 */
+ (__kindof BluetoothManager *)shareInstance;

/**
 开始扫描 | Start scanning
 */
- (void)startScan;

/**
 停止扫描 | Stop scanning
 */
- (void)stopScan;

/**
 * @brief 选择外围设备连接 | Select peripheral connection
 * @param model PeripheralModel 对象 | PeripheralModel object
 */
- (void)connectDeviceWithModel:(PeripheralModel *)model;

/**
 * @brief 断开外围设备连接 | Disconnect peripherals
 * @param model PeripheralModel 对象 | PeripheralModel object
 */
- (void)disConnectDeviceWithModel:(PeripheralModel *)model;

/**
 断开当前外围设备的连接 (将会清空设备信息不再重连) | Disconnect the current peripheral device (The device information will be cleared and will not be reconnected)
 */
- (void)cancelCurrentPeripheralConnection;

/**
 蓝牙设备重连
 @param isStart 开启停止
 */
- (void)startAndStopReconnect:(BOOL)isStart;

@end

NS_ASSUME_NONNULL_END
