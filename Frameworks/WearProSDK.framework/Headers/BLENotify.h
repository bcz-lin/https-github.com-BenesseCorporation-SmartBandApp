//
//  BLENotify.h
//  Bluetooth
//
//  Created by lemo. on 2019/7/28.
//  Copyright © 2019 lemo. All rights reserved.
//

#ifndef BLENotify_h
#define BLENotify_h

/** 连接成功 */
#define BLENotificationConnected        @"BLENotificationConnected"
/** 断开连接通知 */
#define BLENotificationAtDisconnect     @"BLENotificationAtDisconnect"
/** 连接失败 */
#define BLENotificationAtFailToConnect  @"BLENotificationAtFailToConnect"
/** 系统蓝牙状态更新 */
#define BLENotificationDidUpdateState   @"BLENotificationDidUpdateState"


#define BLESportNotify                     @"BLESportNotify"
/// 找手机
#define BLEFindPhoneNotify                 @"BLEFindPhoneNotify"
/// 相机
#define BLECameraStateNotify               @"BLECameraStateNotify"
/// 实时计步数据
#define BLERealtimeStepsDataNotify         @"BLERealtimeStepsDataNotify"
/// 实时心率数据
#define BLERealtimeHeartRateDataNotify     @"BLERealtimeHeartRateDataNotify"
/// 实时血氧数据
#define BLERealtimeBloodOxygenDataNotify   @"BLERealtimeBloodOxygenDataNotify"
/// 实时体温数据
#define BLERealtimeTemperatureDataNotify   @"BLERealtimeTemperatureDataNotify"
/// 实时测量上报
#define BLERealTimeMeasurementStateNotify  @"BLERealTimeMeasurementStateNotify"
/// 实时血压数据
#define BLERealtimeBloodPressureDataNotify @"BLERealtimeBloodPressureDataNotify"


#endif /* BLENotify_h */
