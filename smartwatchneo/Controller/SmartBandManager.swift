//
//  SmartBandManager.swift
//  smartwatchneo
//
//  Created by 林国平 on 20.9.2023.
//

import Foundation
import WearProSDK
import AVFoundation
import CoreBluetooth
//import UIKit

struct SBDevice: Identifiable {
    var id = UUID()
    var macAddr: String
    var peripheral: PeripheralModel
}
let kSavedDeviceUUIDKey = "SavedDeviceUUID"
let smartWatchNeoName = "BenesseSW"
let smartWatchNeoNameReconnect = "Benesse SW"
// CBCentralManagerDelegateは接続解除後の再接続のために仮で追加したもの。
// 最終的な要否は別途確認が必要
// 不要の場合、centralManagerDidUpdateStateは削除すること
class SmartBandManager: NSObject, ObservableObject, BluetoothDelegate, CBCentralManagerDelegate {
    @Published var sbMgrText = "初期状態"
    @Published var deviceArray: [SBDevice] = []
    private var foundMacAddrs: Set<String> = []
    @Published var connected = false
    @Published var bluetoothOn = false
    @Published var connectedMacAddr: String = ""
    @Published var connectedDeviceUuid: UUID!
    @Published var connectedDeviceUuidStr: String = ""
    var centralManager: CBCentralManager!
    
    override init() {
        super.init()
        BluetoothManager.shareInstance().delegate = self
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    func scan(){
        print("reconnet test IN: SmartBandManager#scan()")
        BluetoothManager.shareInstance().startScan()
        
    }
    
    func bluetoothManager(_ manager: BluetoothManager, allDevices: [PeripheralModel], otaDevices: [PeripheralModel]) {
        NSLog("IN: bluetoothManager#allDevices")
        allDevices.forEach{ model in
            print("Found Model: \(model.name)")
            if let name = model.name {
                print("name: \(name)")
                /*
                 if model.macID == nil {
                 model.macID = "paired"
                 }
                 */
                if (name.starts(with:smartWatchNeoName) == true  || name.starts(with:smartWatchNeoNameReconnect) == true) {
                    print("Found Smart Watch!!")
                    if let macID = model.macID {
                        if (foundMacAddrs.contains(macID) == false){
                            var sbdevice = SBDevice(macAddr: macID, peripheral: model)
                            //sbdevice.macAddr = model.macID
                            //sbdevice.peripheral = model
                            deviceArray.append(sbdevice)
                            foundMacAddrs.insert(macID)
                            print("Added device to deviceArray: \(macID)")
                        }
                    } else {
                        // さらにmacIDがnilでもリストアップするようにした
                        print("macID is nil")
                        var sbdevice = SBDevice(macAddr: "paired", peripheral: model)
                        deviceArray.append(sbdevice)
                        foundMacAddrs.insert("paired")
                        print("Added device to deviceArray: paired")
                      }
                }
                
                //                if (name.starts(with:"SmartWatch") == true ) {
                //                            var sbdevice = SBDevice(macAddr: model.macID, peripheral: model)
                //                            //sbdevice.macAddr = model.macID
                //                            //sbdevice.peripheral = model
                //                            deviceArray.append(sbdevice)
                //                            foundMacAddrs.insert(model.macID)
                //                            print("Added device to deviceArray: \(model.macID)")
                //                }
                
                
                
            }
            //BluetoothManager.shareInstance().connectDevice(with: model)
            //BluetoothManager.shareInstance().stopScan()
        }
        
    }
    
    func stopScan(){
        print("IN: stopScan()")
        BluetoothManager.shareInstance().stopScan()
    }
    
    func connect(macAddress: String){
        BluetoothManager.shareInstance().stopScan()
        deviceArray.forEach { model in
            if model.macAddr == macAddress {
                BluetoothManager.shareInstance().connectDevice(with: model.peripheral)
                self.connectedMacAddr = macAddress
                
                // 明示的な接続解除後の再接続のためのデータ保存。実装中。（7/9現在reconnect..でCBCentralからデバイスが取得できていない
                //                let defaults = UserDefaults.standard
                //                let uuid_str = model.peripheral.peripheral?.identifier.uuidString
                //                defaults.set(macAddress, forKey: "SavedMacAddr")
                //                defaults.set(uuid_str, forKey: "SavedUUID")
                UserDefaults.standard.set(model.peripheral.peripheral?.identifier.uuidString, forKey: kSavedDeviceUUIDKey)
                UserDefaults.standard.set(macAddress, forKey: "SavedMacAddr")
                print("デバイスに接続成功: \(model.peripheral.name ?? "Unknown Device")")
                print("モデルのuuID: \(model.peripheral.serviceUUID ?? "UUID取得なし")")
                print("サービスのuuID: \(model.peripheral.peripheral?.identifier.uuidString ?? "サービスUUID取得なし")")
                print("macAdressの値: \(macAddress ?? "macAdress取得なし")")
            }
        }
        deviceArray = []
        foundMacAddrs = []
        
    }
    
    func reconnectSmartBand(){
        BluetoothManager.shareInstance().startAndStopReconnect(true)
        print("再接続テスト reconnect!")
        //        connected = true;
        //        BluetoothManager.shareInstance().startScan()
    }
    
    // ユーザが接続解除したが、設定に登録が残っているときに過去の情報から再接続する
    // 実装要否は別途検討
    //
    func reconnectPreviousConnectedDevice(){
        print("IN: recconectPreviousConnectedDevice()")
        let defaults = UserDefaults.standard
        if let savedUUIDString = defaults.string(forKey: kSavedDeviceUUIDKey),
           let savedUUID = UUID(uuidString: savedUUIDString),
           let savedMacAddr = defaults.string(forKey: "SavedMacAddr")
        {
            //            print("saved UUID: \(savedUUID.uuidString), SavedMacAddr: \(savedMacAddr)")
            //            print("saved UUID: \(savedUUID.uuidString))
            // CBCentralManagerのインスタンスを作成
            //            let centralManager = CBCentralManager(delegate: self, queue: nil)
            let knownPeripherals = centralManager.retrievePeripherals(withIdentifiers: [savedUUID])
            //let knownPeripherals = centralManager.retrieveConnectedPeripherals(withServices: [])
            print("KnownPripherals Count: \(knownPeripherals.count)")
            if let knownPeripheral = knownPeripherals.first {
                print("knownPeripheral Found!!")
                print("reconnect savedMacAddr：\(savedMacAddr)")
                let model = PeripheralModel(peripheral: knownPeripheral, macID: savedMacAddr)
                BluetoothManager.shareInstance().connectDevice(with: model)
                //self.centralManager.connect(knownPeripheral, options: nil)
                //                self.connected = true
                //                self.connectedMacAddr = savedMacAddr
                deviceArray = []
                foundMacAddrs = []
            }
        } else {
            print("saved UUID and MacAddr NOT found.")
        }
    }
    
    func bluetoothManager(_ manager: BluetoothManager, center centerManager: CBCentralManager, didConnect peripheral: CBPeripheral, isOatMode isOtaMode: Bool) {
        print("Smart Watch Connected!!")
        print("uuid: \(peripheral.identifier.uuidString)")
        self.sbMgrText = "接続完了"
        self.connected = true
        self.connectedDeviceUuid = peripheral.identifier
        self.connectedDeviceUuidStr = peripheral.identifier.uuidString
        
        /*
         // Save the UUID of the connected device
         let uuidString = peripheral.identifier.uuidString
         let defaults = UserDefaults.standard
         defaults.set(uuidString, forKey: "SavedUUID")
         */
        
        BluetoothManager.shareInstance().delegate = nil
        CommandProvider.syncConfig()
        CommandProvider.getBatteryCommand { type, dict in
            if let d = dict as? [String: Any] {
                print("getBatteryCommand = \(d)")
            }
        }
        CommandProvider.listenDevceReportCommand{ command, result in
            var dict: [String: Any] = ["": ""]
            if let d = result as? [String:Any] {
                dict = d
            }
            print("IN: listenDeviceReportCommand")
            switch command {
            case .realStep:
                print("realStep = \(dict)")
            case .findPhone:
                print("FindPhone = \(dict)")
                print("uuid2: \(self.connectedDeviceUuidStr)")
                
                self.sbMgrText = "スマホを探す"
                //self.triggerVibration()
                //self.playSound()
                self.playSoundRepeatedly(for: 5)
                self.triggerVibrationRepeatedly(for: 5)
                
            @unknown default:
                print("Other Event = \(dict)")
                break
            }
        }
        
        // サクナビ通知テスト
        let push = CommandProvider.calculationPushValue(1, select: [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1])
        print("pushの値：\(push)")
        CommandProvider.setPushCommandPushValue(push) { type in
            if (type == .SUCCESS_TYPE) {
                print("通知設定成功！")
            }
        }

    }
    /*
     func getConnectedDeviceMacAddr() -> String {
     return connectedMacAddr
     }
     
     func getConnectedDeviceUuid() -> UUID? {
     print("IN: getConnectedUuid()")
     return self.connectedDeviceUuid
     /*
      if let uuid = self.connectedDeviceUuid {
      return uuid
      }
      */
     }
     
     func getConnectedDeviceUuidStr() -> String {
     print("IN: getConnectedUuidStr()")
     return self.connectedDeviceUuidStr
     /*
      if let uuid = self.connectedDeviceUuid {
      return uuid
      }
      */
     }
     */
    
    func disconnect(){
        self.sbMgrText = "接続解除"
        self.connected = false
        if (BluetoothManager.shareInstance().connected){
            BluetoothManager.shareInstance().cancelCurrentPeripheralConnection()
            print("disconnect! 接続解除！")
        }else{
            BluetoothManager.shareInstance().startAndStopReconnect(true)
            print("reconnect! 接続！")
        }
        
        BluetoothManager.shareInstance().delegate = self
    }
    
    func disconnectSmartBand(){
        self.connected = false
        BluetoothManager.shareInstance().cancelCurrentPeripheralConnection()
        print("disconnect! recoonet test!")
    }
    
    func cancelFindPhone(){
        self.sbMgrText = "スマホを探す解除"
        CommandProvider.cancelFindPhoneCommand()
    }
    
    func findWatch() {
        self.sbMgrText = "スマートバンドを探す"
        CommandProvider.findDeviceCommand()
    }
    
    func getBatteryInfo() {
        CommandProvider.getBatteryCommand { type, dict in
            if let d = dict as? [String: Any] {
                self.sbMgrText = d.description
                print("getBatteryCommand = \(d)")
            }
        }
    }
    func getRealTimeStep() {
        CommandProvider.getRealTimeDataCommandType(3) {type, dict in
            if let d = dict as? [String:Any] {
                print("getRealTimeDataCommandType = \(d)")
                self.sbMgrText = d.description
            }
        }
    }
    func getTodaysStep() {
        let calendar: Calendar = Calendar.current
        let now = Date()
        let year = calendar.component(.year, from: now)
        let month = calendar.component(.month, from: now)
        let day = calendar.component(.day, from: now)
        CommandProvider.getHealthDataCommandType(3, year: year, month: month, day: day) { type, dict in
            if let d = dict as? [String: Any] {
                print("getHealthDataCommandType = \(d)")
                self.sbMgrText = d.description
            }
            
        }
    }
    
    // type: 3: 歩数　4: 運動
    func getTodaysData(type: Int) {
        let calendar: Calendar = Calendar.current
        let now = Date()
        let year = calendar.component(.year, from: now)
        let month = calendar.component(.month, from: now)
        let day = calendar.component(.day, from: now)
        CommandProvider.getHealthDataCommandType(type, year: year, month: month, day: day) { type, dict in
            if let d = dict as? [String: Any] {
                print("getHealthDataCommandType = \(d)")
                self.sbMgrText = d.description
            }
            
        }
        
    }
    
    // 日付指定を変えても、返却されるデータは変わらない模様
    func getHistoricalData(type: Int){
        //for i in 0...10 {
        let i = 0 // 指定日によって返却データが変わる想定でループさせていたが、変わらないので固定値に。
        let calendar: Calendar = Calendar.current
        let now = Date()
        let daysBefore = 0 - i
        if let targetDay = Calendar.current.date(byAdding: .day, value: daysBefore , to: now) {
            let year = calendar.component(.year, from: targetDay)
            let month = calendar.component(.month, from: targetDay)
            let day = calendar.component(.day, from: targetDay)
            CommandProvider.getHealthDataCommandType(type, year: year, month: month, day: day) { type, dict in
                if let d = dict as? [String: Any] {
                    print("##### \(year) / \(month) / \(day)#######")
                    print("getHealthDataCommandType = \(d)")
                    self.sbMgrText = d.description
                }
            }
        }
        //}
    }
    
    func getFirmwareInfo(){
        CommandProvider.getFirmwareInfoCommand { type, dict in
            if let d = dict as? [String: Any] {
                print("getFirmwareInfoCommand = \(d)")
                self.sbMgrText = d.description
            }
        }
    }
    
    func updateFirmware(){
        print("IN: updateFirmware()")
        guard
            let filePath = Bundle.main.path(forResource: "C102D3_20883_OTA_APP_Patch_1.47.49.13_ImgPacketFi", ofType: "bin"),
            let peripheral = BluetoothManager.shareInstance().currenPeripheral?.peripheral else {
            self.sbMgrText = "OTA 失敗(ペリフェラル取得失敗）"
            print(sbMgrText)
            return
        }
        
        self.sbMgrText = "OTA実行準備完了 filePath: \(filePath.description) peripheral: \(peripheral.name)"
        print(sbMgrText)
        /** クロージャ内のパラメータ数がIntegration Guideと異なる。問い合わせ中  */
        BLEOTAManager.shareInstance().startOTAUpgrade(with: peripheral,filePath: filePath){ state, length, totalLength, fileIndex, fileTotal in
            switch state {
            case .FAIL:
                self.sbMgrText = "OTA失敗（アップデート失敗）"
                print(self.sbMgrText)
                BLEOTAManager.shareInstance().clear()
            case .SUCCESS:
                self.sbMgrText = "OTA成功"
                print(self.sbMgrText)
                BLEOTAManager.shareInstance().clear()
            case .ING:
                let progress = (Float(length) / Float(totalLength))
                self.sbMgrText = "OTA実行中: \(progress)% (\(fileIndex)/\(fileTotal))"
                print(self.sbMgrText)
            @unknown default:
                break
            } }
        
    }
    
    func setTime(isSync: Bool){
        let calendar: Calendar = Calendar.current
        let now = Date()
        var year = calendar.component(.year, from: now)
        var month = calendar.component(.month, from: now)
        var day = calendar.component(.day, from: now)
        let hour = calendar.component(.hour, from: now)
        let minute = calendar.component(.minute, from: now)
        let second = calendar.component(.second, from: now)
        
        if (isSync != true) {
            year -= 1
            if (month > 1) {
                month -= 1
            }
            if (day > 1) {
                day -= 1
            }
        }
        CommandProvider.setDateCommandYear(year, month: month, day: day, hour: hour, min: minute, second: second, is12Hour: false) { type in
            if type == .SUCCESS_TYPE {
                print("時刻同期成功 \(year)/\(month)/\(day) \(hour):\(minute):\(second)")
                
            }
        }
        
    }
    
    // 指定間隔経過後の0秒のタイミングでアラームが表示される
    func setSedentaryReminder(isOn: Bool, interval: Int){
        print("起立アラームセット: \(isOn)")
        let cycleValue = CommandProvider.calculationCycleValue([1, 1, 1, 1, 1, 1, 1])
        CommandProvider.setSedentaryCommandIsOpen(isOn, startHour: 0, endHour: 24, cycle: cycleValue, sittingTime: interval, sittingThreshold: 100) { type in
            if (type == .SUCCESS_TYPE) {
                print("起立アラームセット成功")
            }
        }
    }
    
    // 指定間隔経過後の0秒のタイミングでアラームが表示される
    func setDrinkReminder(isOn: Bool, interval: Int){
        print("ドリンクアラームセット: \(isOn)")
        let cycleValue = CommandProvider.calculationCycleValue([1, 1, 1, 1, 1, 1, 1])
        CommandProvider.setDrinkRemindCommandIsOpen(isOn, startHour: 0, startMin: 0, endHour: 23, endMin: 59, cycle: cycleValue, interval: interval) { type in
            if (type == .SUCCESS_TYPE) {
                print("ドリンクアラームセット成功")
            }
        }
    }
    
    // 0 歩数, 1: 徒歩 2:ランニング
    func setSportTarget(mode: Int, value: Int){
        print("目標設定: type: \(mode), value: \(value)")
        CommandProvider.setSportTargetCommandStep(2000, sportMode: 0) { type in
            if type == .SUCCESS_TYPE {
                print("目標セット成功")
            }
        }
    }
    
    func setNotification(pushValue: Int){
        print("IN: setNotification pushValue: \(pushValue)")
        CommandProvider.setPushCommandPushValue(pushValue) { type in
            if (type == .SUCCESS_TYPE) {
                print("PushCommand Success.")
            } else {
                print("PushCommand Failed.")
            }
        }
    }
    
    func setUserInfo(gender: Int, age: Int, height: Int, weight: Int){
        print("IN: setUserInfo gender: \(gender) age: \(age) height: \(height) weight: \(weight)")
        CommandProvider.setUserInfoCommandGender(gender, age: age, height: height, weight: weight, goal: 100, bmi: 20) { type in
            if type == .SUCCESS_TYPE {
                print("ユーザ情報設定成功")
            }
        }
        
    }
    /*
     func setCallNotification(isOn: Bool) {
     var pushValue: Int
     if( isOn == true) {
     pushValue = 1
     print("Push Value: 0, Call Should be ON.")
     } else {
     pushValue = 0
     print("Push Value: 1, Call Should be OFF.")
     }
     CommandProvider.setPushCommandPushValue(pushValue) { type in
     if (type == .SUCCESS_TYPE) {
     print("PushCommand Success.")
     } else {
     print("PushCommand Failed.")
     }
     }
     /*
      let f = CommandProvider.isOpen(0, pushType: 11)
      print("LINE: Open? \(f)")
      
      let currentPushState = CommandProvider.getPushSwitchState(toPassPushValue: 0)
      print("getPushSwitchState: \(currentPushState)")
      var newPushState = currentPushState
      if (isOn) {
      newPushState[11] = 1
      } else {
      newPushState[11] = 0
      }
      print("newPushSwitchState: \(newPushState)")
      let pushValue = CommandProvider.calculationPushValue(1, select: newPushState)
      print("Push Value: \(pushValue)")
      CommandProvider.setPushCommandPushValue(pushValue) { type in
      if (type == .SUCCESS_TYPE) {
      print("PushCommand Success.")
      let f_after = CommandProvider.isOpen(2049, pushType: 11)
      print("LINE: Open? (After) \(f_after)")
      
      let currentPushState_after = CommandProvider.getPushSwitchState(toPassPushValue: 999999999);
      print("getPushSwitchState(After): \(currentPushState_after)")
      }
      }
      */
     
     
     
     }
     */
    
    func playSound() {
        AudioServicesPlaySystemSound(1005) // This is the system sound id for the alarm sound
    }
    
    /*
     func playSound() {
     guard let url = Bundle.main.url(forResource: "mySound", withExtension: "wav") else { return }
     
     do {
     // Create AVAudioPlayer object
     let player = try AVAudioPlayer(contentsOf: url, fileTypeHint: AVFileType.wav.rawValue)
     
     // Play sound
     player.play()
     
     } catch let error {
     print("Can't play the audio file. Failed with an error \(error.localizedDescription)")
     }
     }
     */
    
    func triggerVibration() {
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate)
    }
    
    func playSoundRepeatedly(for seconds: TimeInterval) {
        let systemSoundID: SystemSoundID = 1005
        let deadlineTime = DispatchTime.now() + seconds
        
        func playUntilDeadline() {
            if DispatchTime.now() < deadlineTime {
                AudioServicesPlaySystemSound(systemSoundID)
                DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1.0, execute: playUntilDeadline)
            }
        }
        
        playUntilDeadline()
    }
    
    func triggerVibrationRepeatedly(for seconds: TimeInterval) {
        let deadlineTime = DispatchTime.now() + seconds
        
        func vibrateUntilDeadline() {
            if DispatchTime.now() < deadlineTime {
                AudioServicesPlaySystemSound(kSystemSoundID_Vibrate)
                DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1.0, execute: vibrateUntilDeadline)
            }
        }
        
        vibrateUntilDeadline()
    }
    
    // CBCentralManagerDelegateを継承するために必要な実装
    // 継承不要であれば削除する
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
        case .poweredOn:
            print("Bluetooth is On.")
            // Now you can start scanning or connecting to peripherals.
            bluetoothOn = true
            break
        case .poweredOff:
            print("Bluetooth is Off.")
            bluetoothOn = false
            break
            // ... (handle other states) ...
        default:
            print("Central Manager did change state")
        }
    }
    
    
    
}
