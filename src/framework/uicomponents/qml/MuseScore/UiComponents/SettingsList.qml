import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2

import MuseScore.UiComponents 1.0

Item {
    id:root

    property string keyMatch: "";
    property string moduleMatch: "";

    property int labelControlSpacing: 2
    property int controlControlSpacing: 4

    property real controlHeight: 32
    property real controlWidth: 150

    property var color: ui.theme.backgroundPrimaryColor

    property real leftMargin: 8
    property real rightMargin: 8

    SettingsListModel {
        id: settingsModel
    }

    Component.onCompleted: {
        settingsModel.load(keyMatch, moduleMatch);
    }

    ListView {
        anchors.fill: parent

        model: settingsModel

        spacing: controlControlSpacing

        delegate: Rectangle {
            id: containerRect

            anchors.left: parent ? parent.left : undefined
            anchors.right: parent ? parent.right : undefined
            anchors.leftMargin: root.leftMargin
            anchors.rightMargin: root.rightMargin
            height: childrenRect.height
            color: root.color

            StyledTextLabel {
                width:parent.width
                height:root.controlHeight
                horizontalAlignment: Qt.AlignLeft

                text: keyRole

                font.capitalization: Font.AllUppercase

                id: label
            }

            Item {
                id: control
                anchors.top: label.bottom
                anchors.margins: root.labelControlSpacing
                height: childrenRect.height
                width: parent.width

                Loader {
                    id: loader
                    property var val: valRole
                    property var info: infoRole
                    sourceComponent: root.componentByType(typeRole)
                    onLoaded: {
                        loader.item.val = loader.val
                        loader.item.info = loader.info;
                    }
                    onValChanged: {
                        if (loader.item) {
                            loader.item.val = loader.val
                        }
                    }
                }

                Connections {
                    target: loader.item
                    function onChanged(newVal) {
                        settingsModel.changeVal(model.index, newVal)
                    }
                }

            }

        }
    }

    function componentByType(type) {
        switch (type) {
        case "Undefined": return textComp;
        case "Bool": return boolComp;
        case "Int": return intComp;
        case "Double": return doubleComp;
        case "String": return textComp;
        case "Color": return colorComp;
        case "RadioButtonGroup": return radioButtonComp;
        case "NumberSpinner": return numberSpinnerComp;
        case "Checkbox": return checkboxComp;
        }

        return textComp;
    }

    function forceFullHeight(type) {
        switch(type) {
        case "RadioButtonGroup":
            return true;
        }

        return false;
    }

    Component {
        id: textComp

        Rectangle {
            id: textControl
            property var val
            property var info
            signal changed(var newVal)
            anchors.fill: parent
            border.width: 1
            border.color: ui.theme.strokeColor
            TextEdit {
                anchors.fill: parent
                anchors.margins: 2
                verticalAlignment: Text.AlignVCenter
                text: val
                onEditingFinished: textControl.changed(text)
            }
        }
    }

    Component {
        id: colorComp
        Rectangle {
            id: colorControl
            property var val
            property var info
            signal changed(var newVal)
            anchors.fill: parent
            color: val

            ColorDialog {
                id: colorDialog
                title: "Please choose a color"
                onAccepted: colorControl.changed(colorDialog.color)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: colorDialog.open()
            }
        }
    }

    Component {
        id: intComp
        SpinBox {
            id: spinbox
            property var val
            property var info
            signal changed(var newVal)
            width:root.controlWidth
            height: root.controlHeight
            value: val
            stepSize: 1
            textFromValue: function(value, locale) { return String(value) }
            valueFromText: function(text, locale) { return Number(text) }
            onValueModified: spinbox.changed(Number(spinbox.value))
        }
    }

    Component {
        id: doubleComp
        SpinBox {
            id: spinbox
            property var val
            property var info
            width:root.controlWidth
            height: root.controlHeight
            signal changed(var newVal)
            anchors.centerIn: parent
            value: val * 10
            stepSize: 10
            from: -1000
            to: 1000

            property int decimals: 1
            property real realValue: value / 10

            textFromValue: function(value, locale) {
                return Number(value / 10).toLocaleString(locale, 'f', spinbox.decimals)
            }

            valueFromText: function(text, locale) {
                return Number.fromLocaleString(locale, text) * 10
            }
        }
    }

    Component {
        id: boolComp
        CheckBox {
            id: checkbox
            property var val
            property var info
            signal changed(var newVal)
            width:root.controlWidth
            height:root.controlHeight
            checked: val ? true : false
            onClicked: checkbox.changed(!checkbox.checked)
        }
    }

    Component {
        id: radioButtonComp

        RadioButtonGroup {
            id: radioButtonGroup

            property var val
            property var info

            orientation: Qt.Vertical

            signal changed(var newVal)

            model: info.labels

            width: 600
            height: childrenRect.height

            delegate: RoundedRadioButton {
                ButtonGroup.group: radioButtonGroup.radioButtonGroup

                checked: radioButtonGroup.val.toString() === modelData["valueRole"].toString()

                onToggled: {
                    radioButtonGroup.val = modelData["valueRole"].toString();
                    changed(parseInt(modelData["valueRole"]));
                }

                StyledTextLabel {
                    text: modelData["textRole"]
                    horizontalAlignment: Qt.AlignLeft
                }
            }
        }

    }

    Component {
        id: numberSpinnerComp

        IncrementalPropertyControl {
            id: spinBox

            width: root.controlWidth
            height: root.controlHeight

            property var val
            property var info

            signal changed(var newVal)

            currentValue: val

            minValue: info.min
            maxValue: info.max
            step: info.step
            measureUnitsSymbol: info.suffix

            iconMode: iconModeEnum.hidden

            onValueEdited: {
                currentValue = newValue;
                changed(newValue);
            }

        }
    }

    Component {
        id: checkboxComp

        CheckBox {
            id: checkbox

            property var val
            property var info

            signal changed(var newVal)

            width:600
            height:root.controlHeight

            checked: val

             onClicked: {
                 checkbox.checked = !checkbox.checked
                 console.info(checkbox.checked)
                 checkbox.changed(checkbox.checked)
             }

             text: info.option.toString()
        }
    }

}
