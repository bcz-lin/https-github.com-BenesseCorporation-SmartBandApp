//
//  PeripheralModel.h
//  HPlusBluetooth_Example
//
//  Created by lemo. on 2019/5/15.
//  Copyright © 2019 chentingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface PeripheralModel : NSObject

/**
 手环rssi | Bracelet rssi
 */
@property (nonatomic, assign) NSInteger rssi;

/**
 手环名字 | Bracelet name
 */
@property (nullable, nonatomic, copy ) NSString *name;

/**
 macID | Bracelet macAddress
 */
@property (nullable, nonatomic, copy ) NSString *macID;

/**
 uuid | Bracelet uuid
 */
@property (nullable, nonatomic, copy ) NSString *uuidStr;

/**
 服务UUID
 */
@property (nullable,nonatomic,copy) NSString *serviceUUID;

/**
 扫描服务UUID
 */
@property (nullable,nonatomic,copy) NSString *scanServiceUUID;

/**
 写指令通道
 */
@property (nullable,nonatomic,copy) NSString *writeCharacteristic;

/**
 读数据通道
 */
@property (nullable,nonatomic,copy) NSString *notifyCharacteristic;

/**
 外围设备 | peripheral
 */
@property (nullable, nonatomic, strong) CBPeripheral *peripheral;


/// 通过广播数据构造一个外设模型
/// @param peripheral 外设
/// @param advertisementData 广播数据
/// @param rssi 信号量
- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral
                 AdvertisementData:(NSDictionary *)advertisementData
                              RSSI:(NSNumber *)rssi;

/// 通过本地数据构造一个外设模型
/// @param peripheral 外设
/// @param macID macID地址
- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral
                             macID:(nullable NSString *)macID;

@end

NS_ASSUME_NONNULL_END
