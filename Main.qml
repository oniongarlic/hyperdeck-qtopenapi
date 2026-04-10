import QtCore
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import org.tal.hyperdeck

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("HyperDeck API Tester")

    HyperDeckDevice {
        id: hdd
        Component.onCompleted: {
            setServer("192.168.0.233", "http");
            hdd.open();            
        }                
    }

    Connections {
        target: hdd.system

        function onSystemCodecFormatGetFinished(summary) {
            console.debug(summary)
            console.debug("onSystemCodecFormatGetFinished:", summary.getCodecValue, summary.getContainerValue )
        }

        function onSystemCodecFormatGetErrorOccurred(type, error) {
            console.debug("Error getting codec format",type,error)
        }

        function onSystemUptimeGetFinished(summary) {
            console.debug("systemUptimeGetFinished", summary.getUptimeSecondsValue)
        }

        function onSystemSupportedCodecFormatsGetFinished(summary) {
            console.debug("onSystemSupportedCodecFormatsGetFinished")
            var c=summary.getCodecsValue;
            console.debug(c, c.length)
        }
        function onSystemSupportedCodecFormatsGetErrorOccurred(type, error) {
            console.debug("Error getting codec format",type,error)
        }
    }

    Connections {
        target: hdd.transport

        function onTransports0RecordPostFinished() {
            console.debug("Recording...")
        }

        function onTransports0RecordPostErrorOccurred(e,s) {
            console.debug("Recording failed", e, s)
        }

        function onTransports0StopGetFinished(s) {
            console.debug("Stopped:", s)
        }

        function onTransports0StopPostFinished() {
            console.debug("Stopped")
        }
    }

    header: ToolBar {
        RowLayout {
            ToolButton {
                text: "Codec"
                onClicked: {
                    console.debug("Codec")
                    hdd.system.systemCodecFormatGet()
                }
            }
            ToolButton {
                text: "Codecs"
                onClicked: {
                    hdd.system.systemSupportedCodecFormatsGet()
                }
            }
            ToolButton {
                text: "Uptime"
                onClicked: {
                    console.debug("Uptime")
                    hdd.system.systemUptimeGet();
                }
            }
            ToolButton {
                text: "Get Stop"
                onClicked: {
                    hdd.transport.transports0StopGet();
                }
            }
            ToolButton {
                text: "NAS"
                onClicked: {
                    hdd.nas.mediaNasBookmarksGet();
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 16
        Button {
            text: "Play"
            onClicked: {
                hdd.transport.transports0PlayPost();
            }
        }
        Button {
            text: "Record"
            onClicked: {
                hdd.transport.transports0RecordPost();
            }
        }
        Button {
            text: "Stop"
            onClicked: {
                hdd.transport.transports0StopPost();
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                id: clipsList

                Layout.fillHeight: true
                Layout.fillWidth: true

                model: hdd.getClipsModel()
                clip: true

                delegate: ItemDelegate {
                    required property int clipUniqueId;
                    required property string durationTimecode;
                    required property int frameCount;
                    width: ListView.width
                    text: clipUniqueId+" - "+durationTimecode+" ("+frameCount+")"
                }

                onCountChanged: console.debug("model:", count)

                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }

    }

}
