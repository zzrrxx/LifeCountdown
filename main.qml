import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0 as Controls
import Qt.labs.platform 1.0

import my.controls 1.0

Window {
    id: mainWindow
    visible: true
    minimumHeight: 50
    minimumWidth: 120
    width: Screen.desktopAvailableWidth / 14
    height: width * 3 / 7
    title: qsTr("tiny monitor")
    
    flags: Qt.FramelessWindowHint | Qt.WindowSystemMenuHint
            | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint
    
    color: Qt.rgba(0.5, 0.5, 0.5, 0.9)
    
    
    property var birthDay: new Date('1994-11-11T00:00:00')
    property var deathDay: birthDay.setFullYear(birthDay.getFullYear() + 65)
    
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: mainWindow.width
        height: mainWindow.height
        
        
        SevenSegmentDisplay {
            id: display
            anchors.fill: parent
            //digitSize: 200 * sliderDigitSize.value
            digitCount: 20
            precision: 20
            bgColor: "transparent"
            onColor: "red"
            offColor: "transparent"
            verticalAlignment: SevenSegmentDisplay.AlignCenter
            horizontalAlignment: SevenSegmentDisplay.AlignCenter

            value: 0
            onOverflow: {
                //display.digitCount += 1
                //display.precision += 1
            }
        }
        SevenSegmentDisplay {
            id: display1
            digitSize: 14
            digitCount: 3
            precision: 3
            bgColor: "transparent"
            onColor: "red"
            offColor: "transparent"
            verticalAlignment: SevenSegmentDisplay.AlignCenter
            horizontalAlignment: SevenSegmentDisplay.AlignCenter

            value: 001
            onOverflow: {
                //display.digitCount += 1
                //display.precision += 1
            }
        }
        
        Timer {
            interval: 1
            repeat: true
            running: true
            onTriggered: {
                display.value = Math.ceil(deathDay - Math.abs(Date.now()) / 1000)
            }
        }
    }

    ParallelAnimation {
        id: moveAnimation
        running: false
        PropertyAnimation {
            target: mainWindow
            property: 'x'
            easing.type: Easing.Linear
            duration: 100
        }
        PropertyAnimation {
            target: mainWindow
            property: 'y'
            easing.type: Easing.Linear
            duration: 100
        }
    }
    
    MouseArea {
        property point clickPos: "0,0"
        id: dragRegion
        anchors.fill: parent
        drag.minimumX: 0
        drag.maximumX: Screen.desktopAvailableWidth - mainWindow.width
        drag.minimumY: 0
        drag.maximumY: Screen.desktopAvailableHeight - mainWindow.heigh
        onPressed: {
            mainWindow.requestActivate()
            clickPos = Qt.point(mouseX, mouseY)
        }

        onPositionChanged: {
            moveAnimation.stop()
            //鼠标偏移量
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            console.log(delta.x + "  " + delta.y)
            mainWindow.x += delta.x
            mainWindow.y += delta.y
            moveAnimation.start()
        }
        //添加右键菜单
        acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键（别落下这个）
        onClicked: {
            if (mouse.button === Qt.RightButton) {
                // 右键菜单
                contentMenu.popup()
            }
        }
    }
    Controls.Menu {
        id: contentMenu
        Controls.MenuItem {
            id:hideItem
            text: qsTr("隐藏")
            onTriggered: {
                if(trayIcon==null){
                    console.log("系统托盘不存在");
                    contentMenu.removeItem(hideItem);
                    return;
                }else{
                    if(trayIcon.available){
                        console.log("系统托盘存在");
                    }else{
                        console.log("系统托盘不存在");
                        contentMenu.removeItem(hideItem)
                    }
                }
                mainWindow.hide()
            }
        }
        Controls.MenuItem {
            text: qsTr("退出")
            onTriggered: Qt.quit()
        }
    }

   
    Menu {
        id: systemTrayMenu
        MenuItem {
            text: qsTr("隐藏")
            //shortcut: "Ctrl+z"
            onTriggered: mainWindow.hide()
        }
        MenuItem {
            text: qsTr("退出")
            onTriggered: Qt.quit()
        }
    }

    SystemTrayIcon {
        id:trayIcon
        visible: true
        //iconSource: "qrc:/images/TraffickingIn.svg"
        tooltip: "tiny-流量监控软件"
        onActivated: {
            mainWindow.show()
            mainWindow.raise()
            mainWindow.requestActivate()
        }
        menu: systemTrayMenu
    }
}
