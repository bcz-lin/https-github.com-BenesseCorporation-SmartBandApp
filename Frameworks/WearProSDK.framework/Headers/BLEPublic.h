//
//  BLEPublic.h
//  WearProSDK
//
//  Created by Mac on 2021/3/27.
//

#ifndef BLEPublic_h
#define BLEPublic_h

#pragma mark - BLE State

/**
 * 蓝牙管理状态枚举
 * Bluetooth management status enumeration
 */
typedef NS_ENUM(NSInteger, BLE_MANAGER_STATE) {
    /**
     * 蓝牙关闭
     * Bluetooth off
     */
    BLE_MANAGER_STATE_POWEREDOFF = 1,

    /**
     * 蓝牙打开
     * Bluetooth open
     */
    BLE_MANAGER_STATE_POWEREDON,
};

/**
 * 蓝牙发送指令错误类型枚举
 * Bluetooth send command error type enumeration
 */
typedef NS_ENUM(NSInteger, BLE_COMMAND_ERROR_TYPE) {
    /**
     * 指令发送成功
     * The command was sent successfully.
     */
    BLE_COMMAND_SUCCESS_TYPE = 1,
    
    /**
     * 外设未连接
     * Bluetooth Not connected
     */
    BLE_COMMAND_NOT_CONNECTED_TYPE,
    
    /**
     * 指令超时
     * Instruction timeout
     */
    BLE_COMMAND_TIME_OUT_TYPE,
};

/**
 * 设备主动上报蓝牙数据
 * The device actively reports bluetooth data
 */
typedef NS_ENUM(NSInteger, BLE_REPORT_COMMAND) {
    /**
     * 实时步数
     * Real time steps
     */
    BLE_REPORT_COMMAND_realStep = 1,
    
    /**
     * 实时心率
     * Real time heart rate
     */
    BLE_REPORT_COMMAND_realHeartRate,
    
    /**
     * 实时血压
     * Real time blood pressure
     */
    BLE_REPORT_COMMAND_realBloodPressure,
    
    /**
     * 实时血氧
     * Real time blood oxyge
     */
    BLE_REPORT_COMMAND_realBloodOxyge,
    
    /**
     * 相机控制
     * Camera control
     */
    BLE_REPORT_COMMAND_cameraControl,
    
    /**
     * 设备查找手机
     * Find your phone
     */
    BLE_REPORT_COMMAND_findPhone,
    
    /**
     * ECG开始
     * ECG Start
     */
    BLE_REPORT_COMMAND_ecg_start,
    
    /**
     * ECG数据
     * ECG Data
     */
    BLE_REPORT_COMMAND_ecg_data,
    
    /**
     * ECG结束
     * ECG End
     */
    BLE_REPORT_COMMAND_ecg_end,
    
    /**
     * 体温
     * Temperature
     */
    BLE_REPORT_COMMAND_temperature,
    
    /**
     * 实时测量
     * Real time measurement
     */
    BLE_REPORT_COMMAND_realTime_measurement,
    
    /**
     * 设备上报数据（唯蜜瘦）
     * Device info message Report
     */
    BLE_REPORT_COMMAND_device_msg,
};


/**
 * OTA 升级状态
 * OTA upgrade status
 */
typedef NS_ENUM(NSInteger, BLE_OTA_STATE) {
    /**
     *OTA 失败 | OTA fail
     * Bluetooth Off
     */
    BLE_OTA_STATE_FAIL,

    /**
     * OTA 成功 | OTA Success
     */
    BLE_OTA_STATE_SUCCESS,
    
    /**
     * OTA 升级中 | OTA During upgrade
     */
    BLE_OTA_STATE_ING,
};

/**
 * 推送类型
 * Push type
 */
typedef NS_ENUM(NSUInteger, PushType) {
    PushType_Call,
    PushType_Message,
    PushType_QQ,
    PushType_Wechat,
    PushType_Whatsapp,
    PushType_Messenger,
    PushType_Twitter,
    PushType_Linkedin,
    PushType_Instagram,
    PushType_Facebook,
    PushType_Others,
    PushType_Line,
    PushType_Viber,
    PushType_Skype,
    PushType_Outlook,
    PushType_All, //（除了call，message |  Except for call, message）
};

// 蓝牙指令数据回调Block | Bluetooth command data callback Block
typedef void (^ResultCmdBlock)   (BLE_COMMAND_ERROR_TYPE errorType);
typedef void (^ResultBlock)      (BLE_COMMAND_ERROR_TYPE errorType, NSDictionary * _Nullable json);
typedef void (^ResultReportBlock)(BLE_REPORT_COMMAND     reportCmd, NSDictionary * _Nullable json);

// 蓝牙OTA状态回调Block | Bluetooth OTA status callback Block
typedef void (^OTAStateBlock)    (BLE_OTA_STATE          stateType, NSUInteger length, NSUInteger totalLength, NSUInteger fileIndex, NSUInteger fileTotal);

#pragma mark - UUID
// 服务UUID
#define xkyScanServiceUUID      @"C1A0"
#define xkyServiceUUID          @"C3E6C1A0-E966-1000-8000-BE99C223DF6A"
// 指令通道
#define xkyNotifyCharacteristic @"C3E6C1A2-E966-1000-8000-BE99C223DF6A"
#define xkyWriteCharacteristic  @"C3E6C1A1-E966-1000-8000-BE99C223DF6A"



#endif /* BLEPublic_h */
