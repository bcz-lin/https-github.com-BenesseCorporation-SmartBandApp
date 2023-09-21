//
//  InitialSettingController.swift
//  smartwatchneo
//
//  Created by 林国平 on 20.9.2023.
//

import Foundation
import SwiftUI

class InitialSettingController: ObservableObject {
    @Published var shown = false // trigger
    @Published var viewId = ""
    @Published var alert: Alert?
    @Published var buttonTapped = false
    
    func scan() {
       
    }
    
    func connectSmartWatch() {
        
    }
    
    func saveMacAddress() {
        
    }
    
    func setShowPopup() {
        guard popupViewType else { return }
        
    }
    
    var popupViewType: Bool {
        shown = true
        print("case:"+viewId)
        switch viewId {
            case "S-02-1":
                alert = AlertContext.confirming
                return false
            case "S-02-2":
                alert = AlertContext.confirmed
                return false
            case "S-02-3":
                alert = AlertContext.bluetoothOFF
                return false
            case "S-02-4":
                alert = AlertContext.scan
                return false
            case "S-02-5":
                alert = AlertContext.connected
                return false
            case "S-02-6":
                alert = AlertContext.resetting
                return false
            default:
                print("その他のview")
        }
        
        return true
    }
    
    func setNeedsToHideDialog() {
        shown = false
        print("tap dialog")
    }
    
    func setOk() {
        shown = false
        print("tap OK")
    }
}

struct Alert {
    var title: String
    var message: String
    var subMessage: String
    var imageName: String
    var button: String
    var buttonEnable: Bool
    var listHidden: Bool
}

struct AlertContext {
    static let confirming = Alert(
        title: NSLocalizedString("PopupTitle1", comment: ""),
        message: NSLocalizedString("PopupMessage1", comment: ""),
        subMessage: "", imageName: SFSymbolString.sucess.rawValue,
        button:NSLocalizedString("PopupButtonNext", comment: ""),
        buttonEnable: true,
        listHidden: true
        
    )
    static let confirmed = Alert(
        title: NSLocalizedString("PopupTitle2", comment: ""),
        message: NSLocalizedString("PopupMessage2", comment: ""),
        subMessage: "", imageName: SFSymbolString.sucess.rawValue,
        button:NSLocalizedString("PopupButtonNext", comment: ""),
        buttonEnable: false, listHidden: true
    )
    static let bluetoothOFF = Alert(
        title: NSLocalizedString("PopupTitle3", comment: ""),
        message: NSLocalizedString("PopupMessage3", comment: ""),
        subMessage: "", imageName: SFSymbolString.sucess.rawValue,
        button:NSLocalizedString("PopupButtonSettingNext", comment: ""),
        buttonEnable: false,
        listHidden: true
    )
    static let scan = Alert(title: NSLocalizedString("PopupTitle4", comment: ""), message: NSLocalizedString("PopupMessage4", comment: ""), subMessage: "", imageName: SFSymbolString.sucess.rawValue,button:NSLocalizedString("PopupButtonSettingNext", comment: ""), buttonEnable: true, listHidden: true
    )
    static let connected = Alert(title: NSLocalizedString("PopupTitle5", comment: ""), message: "", subMessage: NSLocalizedString("PopupSubMessage5", comment: ""), imageName: SFSymbolString.sucess.rawValue, button:NSLocalizedString("PopupButtonConnecting", comment: ""),
        buttonEnable: false,
        listHidden: false
    )
    static let resetting = Alert(
        title: NSLocalizedString("PopupTitle6", comment: ""),
        message: NSLocalizedString("PopupMessage6", comment: ""),
        subMessage: NSLocalizedString("PopupSubMessage6", comment: ""),
        imageName: SFSymbolString.sucess.rawValue,
        button:NSLocalizedString("PopupButtonResetting", comment: ""),
        buttonEnable: false,
        listHidden: true
    )
    static let finished = Alert(
        title: NSLocalizedString("PopupTitle6", comment: ""),
        message: NSLocalizedString("PopupMessage6", comment: ""),
        subMessage: NSLocalizedString("PopupButtonResetting", comment: ""),
        imageName: SFSymbolString.sucess.rawValue,
        button:NSLocalizedString("PopupButtonSettingNext", comment: ""),
        buttonEnable: false,
        listHidden: true
    )
    /*
    static let invalidData = Alert(title: "Failer", message: "Something went wrong.", imageName: SFSymbolString.failer.rawValue)
    
    static let finished = Alert(title: NSLocalizedString("PopupTitle1", comment: ""), message: "Data storing is sucess!!", imageName: SFSymbolString.sucess.rawValue)
    */
}

enum SFSymbolString: String {
    case sucess = "checkmark.circle.fill"
    case failer = "xmark.circle.fill"
}

extension InitialSettingController: PopupViewDelegate {
    func backgroundViewDidTap() {
        //setNeedsToHideDialog()
    }
}
