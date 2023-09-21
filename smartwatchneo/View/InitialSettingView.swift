//
//  InitialSettingView.swift
//  smartwatchneo
//
//  Created by 林国平 on 20.9.2023.
//

import SwiftUI

struct InitialSettingView: View {
    @StateObject private var bleManager = SmartBandManager()
    @StateObject var viewModel = InitialSettingController()
    @Binding var shown:Bool
    @Binding var viewId:String
    var alert: Alert
    @Binding var buttonTapped:Bool
    
    var isEnable:Bool = true        //tmp:for view list
    @State var showingAlert:Bool = false
    
    var body: some View {
        InitialSettingBaseView(delegate: viewModel) {
            VStack(spacing: 20) {
                Text(alert.title)
                    .font(.title3).fontWeight(.bold)
                    .multilineTextAlignment(.center)
                Text(alert.message)
                    .multilineTextAlignment(.center)
                Text(alert.subMessage)
                    .font(.system(size: 11))
                    .multilineTextAlignment(.center)
                ScrollViewReader { reader in
                    List(1..<5) { index in
                        HStack{
                            Text("Item \(index)")
                                .font(.system(size: 11))
                            Spacer()
                            Button("選択") {
                                print("selected")
                            }
                            .font(.system(size: 11))
                            .buttonBorderShape(.capsule)
                            .buttonStyle(.borderedProminent)
                            .frame(height: 10)
                            .disabled(isEnable)
                        }
                    }
                    .listStyle(.plain)
                    .frame(height: 80)
                    .opacity(alert.listHidden ? 0 : 1)
                    .frame(alignment: .trailing)
                }
                
                Button(
                    action:{
                        shown.toggle()
                        buttonTapped.toggle();
                        buttonAction(viewID: viewId)
                        //if (viewId == "S-02-2"){
                        //    bleManager.scan()
                        //}
                        showingAlert = true
                    },
                    label:{
                        Text(alert.button)
                            .font(.title3)
                            .frame(width: 150, height: 30)
                    }
                )
                .tint(.blue)
                .buttonBorderShape(.capsule)
                .buttonStyle(.borderedProminent)
                .disabled(alert.buttonEnable)
               
                Button(
                    action:{
                        shown.toggle()
                    },
                    label:{
                        Text("PopupButtonUndo")
                            .underline()
                    }
                )
                .tint(.black)
            }
        }
    }
}

func buttonAction(viewID: String){
    switch viewID {
    case "S-02-2":
        //scanView()
        print(viewID)
    case "S-02-3":
        UIApplication.shared.open(URL(string: UIApplication.openSettingsURLString)!)
    case "S-02-4":
        
        print(viewID)
    case "S-02-5":
        print(viewID)
    case "S-02-6":
        print(viewID)
    default:
        print("その他:"+viewID)
    }
 }
 
