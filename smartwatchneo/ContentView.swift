//
//  ContentView.swift
//  smartwatchneo
//
//  Created by 管理者 on 2023/09/15.
//

import SwiftUI

struct ContentView: View {
    @StateObject var viewModel = InitialSettingController()
    @StateObject private var bleManager = SmartBandManager()
    
    var body: some View {
        ZStack {
            VStack {
                VStack {
                    Form {
                        Section {
                            TextField("InitSetting Popup view:", text: $viewModel.viewId)
                        }
                        HStack {
                            Spacer()
                            Button("show popup view") { // Button title
                                // Button action
                                Task {
                                   try? await Task.sleep(nanoseconds: 1_000_000_000)
                                    
                                    //isTapped.toggle()
                                    if bleManager.bluetoothOn {                      viewModel.viewId = "S-02-2"
                                        viewModel.setShowPopup()
                                        
                                        print(viewModel.buttonTapped)
                                        
                                        
                                        if viewModel.buttonTapped{
                                            print(viewModel.viewId)
                                            viewModel.viewId = "S-02-4"
                                            viewModel.setShowPopup()
                                            
                                        }
                                    }
                                    else {
                                        viewModel.viewId = "S-02-3"
                                        viewModel.setShowPopup()
                                    }
                                }
                                viewModel.viewId = "S-02-1"
                                viewModel.setShowPopup()
                                
                            }
                            .frame(width:200, height:50)
                            Spacer()
                        }//: HSTACK
                    }//: FORM
                }
            }//: VSTACK
            .overlay {
                if viewModel.shown {
                    InitialSettingView(shown: $viewModel.shown,
                                       viewId: $viewModel.viewId,
                                       alert: viewModel.alert!,
                                       buttonTapped: $viewModel.buttonTapped
                                       )
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView().environment(\.locale, Locale(identifier: "ja_JP"))
    }
}

