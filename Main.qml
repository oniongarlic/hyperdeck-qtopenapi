import QtCore
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import org.tal.hyperdeck
import org.tal.camera
import org.tal.webpresenter

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("HyperDeck API Tester")

    CameraApi {
        id: caa
        hostname: "192.168.0.141"

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

            onLensFocusDoAutoFocusPutErrorOccurred: (type, error) => { console.debug("AutoFocus failed", type, error) }
            onLensFocusDoAutoFocusPutFinished: () => {
                                                   console.debug("AutoFocused")
                                                   cla.lensFocusGet()
                                               }

            onLensFocusPutErrorOccurred: (type, error) => { console.debug("Focus failed", type, error) }
            onLensFocusPutFinished: console.debug("Focused")

            onLensFocusGetFinished: (f) => {
                                        console.debug("Focus:", f.getFocusValue)
                                    }

            onLensZoomGetFinished: (z) => {
                                       console.debug("Zoom:", z.getNormalisedValue)
                                   }
            onLensIrisGetFinished: (z) => {
                                       console.debug("Iris:", z.getNormalisedValue)
                                   }
        }

        CameraTransportApi {
            id: cta

            onTransports0RecordPutFinished: console.debug("Record")
            onTransports0RecordPutErrorOccurred: console.debug("Record error")

        }

        CameraVideoApi {
            id: cva

            onVideoIsoGetFinished: (z) => { console.debug("ISO", z.getIsoValue) }
        }

    }

    HyperdeckApi {
        id: hdd
        hostname: "192.168.0.233"
        Component.onCompleted: {

        }
        onConnectionError: {
            console.debug("Error connecting")
        }

        HyperdeckSystem {
            id: hdSystem

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

        HyperdeckTransport {
            id: hdTransport

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

        HyperdeckNAS {
            id: hdNas
        }

    }

    WebpresenterApi {
        id: wpa
        hostname: "192.168.0.234"
        debug: true
        Component.onCompleted: {

        }
        onConnectionError: {
            console.debug("Error connecting")
        }

        onStreamInfo: {
            // console.debug(getStatus(), getBitrate(), "/" , getCache())
        }

        onProductInformation: {
            console.debug(getProduct(), getDevice(), getVersion())
        }

        onPlatforms: console.debug(getPlatsforms())

        WebpresenterSystem {
            id: wps

            onSystemSupportedVideoFormatsGetFinished: (vf) => {
                                                          console.debug(vf.getFormatsValue)
                                                      }

            onSystemSupportedVideoFormatsGetErrorOccurred: (et, es) => { console.debug("Error", et, es) }
        }

        WebpresenterEvent {
            id: wpe
        }

        WebpresenterLiveStream {
            id: wpls

            onLivestreamsCustomPlatformsGetFinished: (vf) =>{
                                                         console.debug(vf)
                                                         livestreamsCustomPlatformsFilenameGet(vf)
                                                     }

            onLivestreamsCustomPlatformsFilenameGetFinished: (summary) => {
                                                                 console.debug(summary)

                                                             }

            onLivestreamsCustomPlatformsGetErrorOccurred: (et, es) => { console.debug("Error", et, es) }

            onLivestreamsPlatformsGetFinished: (vf) => {
                                                   console.debug(vf)
                                               }

            onLivestreamsPlatformsGetErrorOccurred: (et, es) => { console.debug("Error", et, es) }
        }
    }

    header: ToolBar {
        RowLayout {
            ToolButton {
                text: "Codec"
                onClicked: {
                    console.debug("Codec")
                    hdSystem.systemCodecFormatGet()
                }
            }
            ToolButton {
                text: "Codecs"
                onClicked: {
                    hdSystem.systemSupportedCodecFormatsGet()
                }
            }
            ToolButton {
                text: "Uptime"
                onClicked: {
                    console.debug("Uptime")
                    hdSystem.systemUptimeGet();
                }
            }
            ToolButton {
                text: "Get Stop"
                onClicked: {
                    hdTransport.transports0StopGet();
                }
            }
            ToolButton {
                text: "NAS"
                onClicked: {
                    hdNas.mediaNasBookmarksGet();
                }
            }
            ToolSeparator {}
            ToolButton {
                text: "CamCodec"
                onClicked: {
                    console.debug("CamVideo")
                    csa.systemFormatGet()
                }
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            Label {
                text: caa.timecode
            }
            Label {
                text: "ISO: "+caa.iso
            }
            Label {
                text: "G: "+caa.gain
            }
            Label {
                text: caa.shutter
            }
            Label {
                text: caa.whiteBalance
            }
            Label {
                text: caa.tint
            }
            Label {
                text: caa.zoom
            }
            Label {
                text: caa.focus
            }
            Label {
                text: caa.iris
            }
            Label {
                text: wpa.bitrate
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 16

        ColumnLayout {
            spacing: 8

            Label {
                text: "Camera"
            }
            Button {
                text: "Connect..."
                onClicked: caa.open();
            }

            Button {
                text: "AutoFocus"
                onClicked: cla.lensFocusDoAutoFocusPut();
            }
            Button {
                text: "Get Focus"
                onClicked: cla.lensFocusGet();
            }

            Button {
                text: "Get Zoom"
                onClicked: cla.lensZoomGet()
            }
            Button {
                text: "Get Iris"
                onClicked: cla.lensIrisGet()
            }
            Button {
                text: "Get ISO"
                onClicked: cva.videoIsoGet()
            }
            RowLayout {
                Layout.fillWidth: true
                Button {
                    text: "200"
                    onClicked: cva.setIso(200)
                }
                Button {
                    text: "400"
                    onClicked: cva.setIso(400)
                }
                Button {
                    text: "500"
                    onClicked: cva.setIso(500)
                }
            }

            Button {
                text: "Record"
                onClicked: cta.transports0RecordPut()
            }

            Slider {
                from: 0
                to: 1
                live: false
                stepSize: 0.05
                wheelEnabled: true
                onValueChanged: cla.setZoom(value)
            }

            Slider {
                from: 0
                to: 1
                live: false
                stepSize: 0.05
                wheelEnabled: true
                onValueChanged: cla.setFocus(value)
            }
        }

        ColumnLayout {
            spacing: 8

            Label {
                text: "Webpresenter"
            }
            Button {
                text: "Connect..."
                onClicked: wpa.open();
            }

            Button {
                text: "Formats"
                onClicked: wps.systemSupportedVideoFormatsGet();
            }

            Button {
                text: "CustomPlatforms"
                onClicked: wpls.livestreamsCustomPlatformsGet()
            }
            Button {
                text: "Platforms"
                onClicked: wpls.livestreamsPlatformsGet()
            }
            Button {
                text: "Start"
                onClicked: wpls.livestreams0StartPut()
            }
            Button {
                text: "Stop"
                onClicked: wpls.livestreams0StopPut()
            }
        }

        ColumnLayout {
            spacing: 8
            Label {
                text: "Hyperdeck"
            }
            Button {
                text: "Connect..."
                onClicked: hdd.open();
            }

            Button {
                text: "Play"
                onClicked: {
                    hdTransport.transports0PlayPost();
                }
            }
            Button {
                text: "Record"
                onClicked: {
                    hdTransport.transports0RecordPost();
                }
            }
            Button {
                text: "Stop"
                onClicked: {
                    hdTransport.transports0StopPost();
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

}
