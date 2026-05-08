import QtCore
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import org.tal.hyperdeck

import org.tal.camera

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("HyperDeck API Tester")

    CameraApi {
        id: caa
        hostname: "192.168.0.141"

        Component.onCompleted: {            
            caa.open();
            csa.systemGet();
            csa.systemFormatGet();
        }

        CameraSystemApi {
            id: csa

            onSystemFormatGetErrorOccurred: (type, error) => {
                console.debug("Error getting video format", type, error)
            }

            onSystemCodecFormatGetFinished: (summary) => {
                console.debug(summary)
                console.debug("onSystemCodecFormatGetFinished:", summary.getCodecValue, summary.getContainerValue )
            }

            onSystemFormatGetFinished: (summary) => {
                console.debug(summary)
                console.debug("onSystemFormatGetFinished:", summary.getNameValue)
            }

            onSystemCodecFormatGetErrorOccurred: (type, error) => {
                console.debug("Error getting codec format", type, error)
            }

        }

        CameraLensApi {
            id: cla

            onLensFocusDoAutoFocusPutErrorOccurred: (type, error) => { console.debug("Focus failed", type, error) }
            onLensFocusDoAutoFocusPutFinished: () => {
                console.debug("Focused")
                cla.lensFocusGet()
            }

            onLensFocusGetFinished: (f) => {
                console.debug("Focus:", f.getFocusValue)
            }

            onLensZoomGetFinished: (z) => {
                console.debug("Zoom:", z.getNormalisedValue)
            }
        }

        CameraTransportApi {
            id: cta

        }

        CameraVideoApi {
            id: cva

        }

    }

    HyperdeckApi {
        id: hdd
        Component.onCompleted: {
            setServer("192.168.0.233", "http");
            hdd.open();            
        }
        onConnectionError: {
            console.debug("Error connecting")
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
            ToolSeparator {}
            ToolButton {
                text: "CamCodec"
                onClicked: {
                    console.debug("CamVideo")
                    caa.system.systemFormatGet()
                }
            }
            ToolButton {
                text: "Focus"
                onClicked: cla.lensFocusDoAutoFocusPut()
            }
            ToolButton {
                text: "Zoom"
                onClicked: cla.lensZoomGet()
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            Label {
                text: caa.timecode
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
