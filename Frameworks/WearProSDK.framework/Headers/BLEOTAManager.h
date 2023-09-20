//
//  BLEOTAManager.h
//  WearProSDK
//
//  Created by Mac on 2021/3/27.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "BLEPublic.h"

NS_ASSUME_NONNULL_BEGIN

@interface BLEOTAManager : NSObject

/// 初始化OTA对象 |  Initialize the OTA object
+ (__kindof BLEOTAManager *)shareInstance;

/// 开始OTA | Start OTA
/// @param peripheral 外围设备 | Peripheral equipment
/// @param filePath 本地升级文件地址 | Local upgrade file address
- (void)startOTAUpgradeWithPeripheral:(CBPeripheral *)peripheral filePath:(NSString *)filePath state:(OTAStateBlock)block;

/// 清理数据 | Clean up data
- (void)clear;

@end

NS_ASSUME_NONNULL_END
