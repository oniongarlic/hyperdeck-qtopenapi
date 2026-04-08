import QtCore
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    Connections {
        target: system

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
        target: transport

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

    Connections {
        target: event
    }

    header: ToolBar {
        RowLayout {
            ToolButton {
                text: "Codec"
                onClicked: {
                    console.debug("Codec")
                    system.systemCodecFormatGet()
                }
            }
            ToolButton {
                text: "Codecs"
                onClicked: {
                    system.systemSupportedCodecFormatsGet()
                }
            }
            ToolButton {
                text: "Uptime"
                onClicked: {
                    console.debug("Uptime")
                    system.systemUptimeGet();
                }
            }
            ToolButton {
                text: "Record"
                onClicked: {
                    transport.transports0RecordPost();
                }
            }
            ToolButton {
                text: "Stop"
                onClicked: {
                    transport.transports0StopPost();
                }
            }
            ToolButton {
                text: "Get Stop"
                onClicked: {
                    transport.transports0StopGet();
                }
            }
        }
    }

}
