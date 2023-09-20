//
//  CommandProvider.h
//  Bluetooth_Example
//
//  Created by lemo. on 2019/5/14.
//  Copyright © 2019 chentingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BLEPublic.h"

NS_ASSUME_NONNULL_BEGIN

@interface CommandProvider : NSObject

#pragma mark ======= Set Command =======

/// 同步基础配置(时间/语言)跟随系统同步(默认连接上自动同步) | Synchronization basic configuration (platform/device information/time/language) follows system synchronization(Automatic synchronization on the default connection)
+ (void)syncConfig;

/// 发送数据给手表 | Send Data To Data
+ (void)sendDataToDevice:(NSData *)data callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置当前日期 | Set current date
/// @param year 年 | year
/// @param month 月 | month
/// @param day 日 | day
/// @param hour 时 | hour
/// @param min 分 | min
/// @param second 秒 | second
/// @param is12Hour 时间制 | time system
+ (void)setDateCommandYear:(NSInteger)year
                     month:(NSInteger)month
                       day:(NSInteger)day
                      hour:(NSInteger)hour
                       min:(NSInteger)min
                    second:(NSInteger)second
                  is12Hour:(BOOL)is12Hour
                  callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;


/// 系统用户设置 | Set System user Settings
/// @param languageCode 0:中文 1:英文 2.俄罗斯语 3.西班牙语 4.德国 5.意大利 6.法国 7.葡萄牙 8.波兰语 9.荷兰 10.希腊 11.土耳其 12.罗马尼亚 13.日语 14.繁体（目前只支持M6） 15.希伯来语 16.丹麦语 17.塞尔维亚语 18:其他 | 0: Chinese 1: English 2. Russian 3. Spanish 4. Germany 5. Italy 6. France 7. Portugal 8. Polish 9. Netherlands 10. Greece 11. Turkey 12. Romania 13. Japanese 14. Traditional (currently only supported M6) 15. Hebrew 16. Danish 17. Serbian 18: others
/// @param is12Hour 时间制 (Yes: 12小时， No:24小时)| time system(Yes: 12 hour,  No: 24hour)
+ (void)setSystemUserCommandLanguageCode:(NSInteger)languageCode
                                is12Hour:(BOOL)is12Hour
                                callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 用户信息设置 | Set User information Settings
/// @param gender 0:女 1:男 | 0: female 1: male
/// @param age 年龄 | age
/// @param height 身高（cm） | height(cm)
/// @param weight 体重（kg） | weight(kg)
/// @param goal 运动目标（步数） | Moving target (steps)
/// @param BMI BMI
+ (void)setUserInfoCommandGender:(NSInteger)gender
                             age:(NSInteger)age
                          height:(NSInteger)height
                          weight:(NSInteger)weight
                            goal:(NSInteger)goal
                             BMI:(NSInteger)BMI
                        callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置推送 | Set the push
/// @param pushValue 推送值 0:推送所有 1:关闭推送（bit0：来电 bit1：短信 bit2：QQ bit3: 微信 bit4：whatsapp bit5：Messenger bit6：Twitter bit7：linkedin bit8：Instagram bit9：facebook bit10：others bit11:line bit12:viber bit13:skype bit14:Outlook）|
/// push value 0:push all 1:close push(Bit0: call bit1: SMS bit2: QQ bit3: WeChat bit4: whatsapp bit5: Messenger bit6: Twitter bit7: linkedin Bit8: Instagram bit9: facebook bit10: others bit11:line bit12:viber bit13:skype bit14:Outlook)
+ (void)setPushCommandPushValue:(NSInteger)pushValue
                       callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置心率检测 | Set heart rate detection
/// @param isOpen 开关 | switch
/// @param startHour 开始时 | start hour
/// @param startMin 开始分 | start min
/// @param endHour 结束时 | end hour
/// @param endMin 结束分 | end min
/// @param interval 间隔（分钟）10的倍数 | interval（min）
+ (void)setHeartRateCheckCommandIsOpen:(BOOL)isOpen
                             startHour:(NSInteger)startHour
                              startMin:(NSInteger)startMin
                               endHour:(NSInteger)endHour
                                endMin:(NSInteger)endMin
                              interval:(NSInteger)interval
                              callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置勿扰模式 | Set do not disturb mode
/// @param isOpen 开关 | switch
/// @param startHour 开始时 | start hour
/// @param startMin 开始分 | start min
/// @param endHour 结束时 | end hour
/// @param endMin 结束分 | end min
+ (void)setNotDisturbCommandIsOpen:(BOOL)isOpen
                             startHour:(NSInteger)startHour
                              startMin:(NSInteger)startMin
                               endHour:(NSInteger)endHour
                                endMin:(NSInteger)endMin
                              callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置喝水提醒 | Set a water reminder
/// @param isOpen 开关 | switch
/// @param startHour 开始时 | start hour
/// @param startMin 开始分 | start min
/// @param endHour 结束时 | end hour
/// @param endMin 结束分 | end min
/// @param cycle 重复 0:表示仅一次 1:表示每天重复（bit0 - bit6分别表示周一到周日的重复设置，所有位都为0时，表示只提醒一次） | Repeat 0: only once 1: every day (bit0-bit6 is the repeat setting from Monday to Sunday, and when all bits are 0, it is only reminded once)
/// @param interval 间隔（分钟）| interval（min）
+ (void)setDrinkRemindCommandIsOpen:(BOOL)isOpen
                          startHour:(NSInteger)startHour
                           startMin:(NSInteger)startMin
                            endHour:(NSInteger)endHour
                             endMin:(NSInteger)endMin
                              cycle:(NSInteger)cycle
                           interval:(NSInteger)interval
                           callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置久坐提醒 | Set a sedentary reminder
/// @param isOpen 开关 | switch
/// @param startHour 开始时 | start hour
/// @param endHour 结束时 | end hour
/// @param cycle 重复 0:表示仅一次 1:表示每天重复（bit0 - bit6分别表示周一到周日的重复设置，所有位都为0时，表示只提醒一次） | Repeat 0: only once 1: every day (bit0-bit6 is the repeat setting from Monday to Sunday, and when all bits are 0, it is only reminded once)
/// @param sittingTime 久坐时间(分钟)超过这个时间提醒 | Sitting time (min) Over this time reminder
/// @param sittingThreshold 久坐阈值（步数）以小时为单位久坐时间内，步数低于这个阈值才提醒 | Sedentary threshold（Step）
+ (void)setSedentaryCommandIsOpen:(BOOL)isOpen
                        startHour:(NSInteger)startHour
                          endHour:(NSInteger)endHour
                            cycle:(NSInteger)cycle
                      sittingTime:(NSInteger)sittingTime
                 sittingThreshold:(NSInteger)sittingThreshold
                         callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置闹钟 | Set the alarm clock
/// @param alarms 闹钟模型数组（最多5个）| Alarm clock model array (up to 5)
/// alarms: @[@{@"hour": Int, @"min": Int, @"cycle": Int , @"label": Int(0：闹钟 1：会议), @"isOpen": BOOL}]
/// cycle:  重复 0:表示仅一次 1:表示每天重复（bit0 - bit6分别表示周一到周日的重复设置，所有位都为0时，表示只提醒一次） | Repeat 0: only once 1: every day (bit0-bit6 is the repeat setting from Monday to Sunday, and when all bits are 0, it is only reminded once)
+ (void)setAlarmClockCommandAlarms:(NSArray *)alarms
                         callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置单位 | Set the unit
/// @param measure 度量单位（0:公制 1:英制） | Unit of measure (0: metric 1: imperial)
/// @param temperature 温度（0: 摄氏度 1:华氏摄氏度）| Temperature (0: Celsius 1: Fahrenheit)
+ (void)setUnitCommandMeasure:(NSInteger)measure
                  temperature:(NSInteger)temperature
                     callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置运动目标 | Set a moving target
/// @param step 步数 | step
/// @param sportMode 0: 日常计步 1:走路 2: 跑步 3: 骑行 4: 爬山 | 0: daily step counting 1: walking 2: running 3: cycling 4: climbing
+ (void)setSportTargetCommandStep:(NSInteger)step
                        sportMode:(NSInteger)sportMode
                         callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 天气推送 | Set weather push
/// @param lowTemperature 低温 | low temperature
/// @param highTemperature 高温 | hight temperature
/// @param weatherType 天气类型（0:晴 1:阴 2:雨 3:雪） | weather type(0: fine 1: Yin 2: rain 3: snow)
/// @param currenTemperature 当前温度 | curren temperature
+ (void)setWeatherPushCommandLowTemperature:(NSInteger)lowTemperature
                            highTemperature:(NSInteger)highTemperature
                                weatherType:(NSInteger)weatherType
                          currenTemperature:(NSInteger)currenTemperature
                                   callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 气象推送 | Set weather push
/// @param uvIndex 紫外线 | ultraviolet rays
/// @param pressure 气压 | air pressure
/// @param altitude 海拔 | altitude
+ (void)setMeteorologicalPushCommandUvIndex:(NSInteger)uvIndex
                                   pressure:(NSInteger)pressure
                                    altitude:(NSInteger)altitude
                                    callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置提醒模式 | Set reminder mode
/// @param remindType 提醒方式 1:亮屏 2:震动 3:亮屏+震动 | Reminder 1: bright screen 2: vibration 3: bright screen + vibration
+ (void)setRemindModelCommandRemindType:(NSInteger)remindType
                               callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置女性生理期 | Set female menstrual period
/// @param state  1:生理期  2：安全期  3：排卵期 | 1: Menstrual period 2: Safe period 3: Ovulation period
+ (void)setPCACommandState:(NSInteger)state
                               callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 清除通讯录 | Clear address book
+ (void)setClearContactCommandCallback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 同步通讯录 | Sync address book
/// @param phone  号码 | phone
/// @param name 姓名 | name
/// @param index  偏移 | index
+ (void)setContactInfoPhone:(NSString *)phone
                       name:(NSString *)name
                      index:(NSInteger)index
                   callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 实时测量 | Real-time measurement
/// @param state  0:不支持些功能 1:启动测量 2:结束测量 3:脱手 4:超时 5.设备忙, 以下情况会出现返回error code:(1运动中. 2秒表中 3通话中) |  0: some functions are not supported 1: start measurement 2: end measurement 3: hands off 4: timeout 5. The device is busy, and the error code will be returned in the following situations: (1 in motion. 2 in the stopwatch 3 in the call )
/// @param type 0:未知 1:睡眠(保留) 2:心率 3:计步 4:运动 5:血压 6:心电 7:血氧(note：现在支持心率、血压、血氧) | 0: unknown 1: sleep (reserved) 2: heart rate 3: step counting 4: exercise 5: blood pressure 6: ECG 7: blood oxygen (note: now supports heart rate, blood pressure, blood oxygen)
/// @param mode 0:未知 1:前台(亮屏, 手表跳转到心率测量页面) 2:后台(保留后续使用) | 0: unknown 1: foreground (the screen is on, the watch jumps to the heart rate measurement page) 2: background (reserve for future use)
+ (void)realTimeMeasurementWithState:(NSInteger)state
                                type:(NSInteger)type
                                mode:(NSInteger)mode
                            callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 校验血压 | Check blood pressure
/// @param high 高压（收缩压）80 - 200 | High pressure (systolic blood pressure) 80-200
/// @param low 低压（舒张压）50 - 110 |  low pressure (diastolic blood pressure) 50-110
/// @param callback 回调
+ (void)setBloodPressureCalibration:(NSInteger)high
                                low:(NSInteger)low
                           callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 清除二维码 | Clear QRCode
+ (void)setClearQRCodeCommandCallback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 设置二维码 | Set QRCode
/// @param message 二维码数据 |  QRCode Data（服务器返回 | Server returns）
/// @param remark 备注 | Remark
/// @param type 类型 | Type (0: wechat  1:alipay  2:qq  3:other  4:more)
/// @param width 宽度  | Width（服务器返回 | Server returns）
/// @param height 高度 | Height（服务器返回 | Server returns）
/// @param checkNum 校验码 | CheckNum （服务器返回 | Server returns）
/// @param index 索引 | Index
/// @param callback 回调 | Callback
+ (void)setQRCodeCommand:(NSString *)message remark:(NSString *)remark type:(NSInteger)type width:(NSInteger)width height:(NSInteger)height checkNum:(NSInteger)checkNum index:(NSInteger)index Callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;


#pragma mark ======= Get Command =======
/// 获取手环mac地址| Get device mac address
+ (void)getBraceletSetCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

/// 获取固件版本信息 | Get firmware information
+ (void)getFirmwareInfoCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

/// 获取电量 | Get attery
+ (void)getBatteryCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

/// 获取配置信息 | Get configuration information
+ (void)getProfileCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

/// 获取当前实时数据 | Get the current real-time data
/// @param type 1：睡眠 2：心率 3：计步 4：运动模式 | 1: sleep 2: heart rate 3: count steps 4: exercise mode
+ (void)getRealTimeDataCommandType:(NSInteger)type
                         callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

/// 获取指定日期健康数据 | Gets health data for the specified date
/// @param type 1:睡眠  2:心率 3:计步 4:运动  5:血压  6:心电  7:血氧  8:腰带记录 | 1: sleep 2: heart rate  3: step counting 4: exercise 5: blood pressure  6: ecg  7: blood oxygen 8:belt record
/// @param year 年
/// @param month 月
/// @param day 日
/// 设备最多保存七天数据 | The device holds data for up to seven days
+ (void)getHealthDataCommandType:(NSInteger)type
                            year:(NSInteger)year
                           month:(NSInteger)month
                             day:(NSInteger)day
                        callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType, NSDictionary *_Nullable json))callback;

#pragma mark ======= Control Command =======
/// 查找设备 | Find device
+ (void)findDeviceCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 取消设备查找手机 | Cancel find phone
+ (void)cancelFindPhoneCommand:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 抬手亮屏 | Raised my hand against the bright screen
/// @param hand 0:左手 1:右手 | 0: left hand 1: right hand
/// @param raise 0:抬手亮屏关闭  1:抬手亮屏开启 | 0: turn off the bright screen 1: turn on the bright screen
/// @param flip 0:翻腕亮屏关闭  1:翻腕亮屏开启 | 0: turn wrist bright screen off 1: turn wrist bright screen on
+ (void)gesturesControlCommandHand:(NSInteger)hand
                             raise:(NSInteger)raise
                              flip:(NSInteger)flip
                          callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

/// 远程拍照控制 | Remote camera control
/// @param isOpen 0:相机已关闭 1:相机已打开 | 0: camera closed 1: camera on
+ (void)cameraControlCommandIsOpen:(NSInteger)isOpen
                        callback:(void(^_Nullable)(BLE_COMMAND_ERROR_TYPE errorType))callback;

#pragma mark ======= Listen Command =======
/// 设备主动上报蓝牙数据 | The device actively reports bluetooth data
+ (void)listenDevceReportCommand:(void(^_Nullable)(BLE_REPORT_COMMAND reportCmd, NSDictionary *_Nullable json))callback;

#pragma mark ======= Tool =======
/// 女性周期计算
/// @param currentDay 当前是时间 （2020-11-1）
/// @param recentDay   最近月经日子 （2020-11-1）
/// @param period 持续时间
/// @param interval 间隔天数
/// @return //生理状态：0月经期， 1月经期(预测) 2，安全期 , 3 排卵期
+ (NSInteger)calculationPCAStatusWithCurrentDay:(NSString *)currentDay
                                      recentDay:(NSString *)recentDay
                                         period:(NSInteger)period
                                       interval:(NSInteger)interval;

/// 通过周期值计算周几被选择了  |  Calculate the day of the week by the period value is selected
/// @param cycleValue 周期值 |  Cycle value
/// return array  0: 未选择 1:选择 @[@0, @0, @1, @1, @1, @1, @0]  |  0: Not selected 1: Selected @[@0, @0, @1, @1, @1, @1, @0]
+ (NSArray<NSNumber *> *)getTheDayOfTheWeekSelectedToPassCycleValue:(NSInteger)cycleValue;

/// 是否选中当前日期 |  Whether to select the current date
/// @param cycle 周期值 |  Period value
/// @param day 星期几 | Day of the week ( 0:monday, 1:tuesday, 2:wednesday,3: thursday, 4:friday, 5:saturday, 6:sunday)
+ (BOOL)isSelect:(NSInteger)cycle dayOfTheWeek:(NSInteger)day;

/// 根据周一到周日选择数组转换周期值 | Select the array conversion period value according to Monday to Sunday
/// - Parameter selects: 选中数组  0:未选择 1:选择  @[@0, @0, @1, @1, @1, @1, @0]  | Selected array   0: not selected 1: selected  @[@0, @0, @1, @1, @1, @1, @0]
+ (NSInteger)calculationCycleValue:(NSArray<NSNumber *> *)selects;

/// 获取当前类型开关 | Get the current type switch
/// @param pushValue  值
/// @param type 推送类型(0:call,  1: message,  2:qq  3:wechat  4: whatsapp  5:messenger  6: twitter 7: linkedin 8:instagram 9:facebook, 10: others 11: line 12:viber 13: skype 14: outlook )  |  Push type (0:call,  1: message,  2:qq  3:wechat  4: whatsapp  5:messenger  6: twitter 7: linkedin 8:instagram 9:facebook, 10: others 11: line 12:viber 13: skype 14: outlook )
+ (BOOL)isOpen:(NSInteger)pushValue pushType:(NSInteger)type;

/// 转换推送
/// @param pushValue 值
/// @param pushType 推送类型(0:call,  1: message,  2:qq  3:wechat  4: whatsapp  5:messenger  6: twitter 7: linkedin 8:instagram 9:facebook, 10: others 11: line 12:viber 13: skype 14: outlook )  |  Push type (0:call,  1: message,  2:qq  3:wechat  4: whatsapp  5:messenger  6: twitter 7: linkedin 8:instagram 9:facebook, 10: others 11: line 12:viber 13: skype 14: outlook )
/// @param isOn 是否打开 | Whether to open
+ (NSInteger)tranfromPushValue:(NSInteger)pushValue pushType:(NSInteger)pushType isOn:(BOOL)isOn;

/// 根据所有推送类型开关状态转换推送值 | Switch the push value according to the switch state of all push types
/// @param pushValue  当前的推送值 | Current push value
/// @param selects 所有推送类型开关状态 0:未开启  1:开启  @[@0, @0, @1, @1, @1, @1, @0, @0, @0, @1, @1, @1, @1, @0, @0]  | Switch status of all push types  0: not open 1: open  @[@0, @0, @1, @1, @1, @1, @0, @0, @0, @1, @1, @1, @1, @0, @0]
+ (NSInteger)calculationPushValue:(NSInteger)pushValue select:(NSArray<NSNumber *> *)selects;

/// 获取所有推送类型开关状态  | Get the switch status of all push types
/// @param pushValue 推送值 |  Push value
/// return array  0: 未开启 1:开启 | 0: not open 1: open  @[@0, @0, @1, @1, @1, @1, @0, @0, @0, @1, @1, @1, @1, @0, @0]
+ (NSArray<NSNumber *> *)getPushSwitchStateToPassPushValue:(NSInteger)pushValue;

@end

NS_ASSUME_NONNULL_END
