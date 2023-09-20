//
//  DeviceInfoModel.h
//  Bluetooth_Example
//
//  Created by lemo. on 2019/5/28.
//  Copyright © 2019 chentingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DeviceInfoModel : NSObject

/**
 设备方案对应适配号 | Matching number
 */
@property (nonatomic, assign) NSInteger number;

/**
 0:nordic 1:dialog 2:MTK 3:TI 4:RTK
 */
@property (nonatomic, assign) NSInteger platform;

/**
 固件版本 | FirmwareVersion
 */
@property (nonatomic, copy  ) NSString *firmwareVersion;

/**
 UUID | UUID
 */
@property (nullable, nonatomic, copy) NSString *uuidStr;

/**
 设备名称 | DeviceName
 */
@property (nullable, nonatomic, copy) NSString *deviceName;

/**
 MAC地址 | MAC address
 */
@property (nullable, nonatomic, copy) NSString *macAddress;

- (instancetype)initWithDeviceName:(NSString *)deviceName
                            number:(NSInteger)number
                   firmwareVersion:(NSString *)firmwareVersion
                        macAddress:(NSString *)macAddress
                           uuidStr:(NSString *)uuidStr
                          platform:(NSInteger)platform;
/**
 * @brief 查询本地已连接设备信息，查询不到初始化新的对象 | Query local connected device information, query not to initialize new object
 * @return DeviceInfoModel
 */
+ (__kindof DeviceInfoModel *)currentModel;

/// 保存 | Save
- (void)save;

/// 删除 | Delete
- (void)deleteDeviceInfo;

@end

NS_ASSUME_NONNULL_END
