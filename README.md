# Arduino MQTT Pump Control

This Arduino sketch connects to an MQTT broker and subscribes to a topic to control a pump. The pump can be turned on or off by sending a message to the subscribed topic with the payload "{'pump': 'on'}" or "{'pump': 'off'}".

## Dependencies

- [PubSubClient](https://github.com/knolleary/pubsubclient): A client library for MQTT communication.
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson): A library for parsing and generating JSON data.

## Hardware Requirements

- An ESP32-DEVKIT V1 board (e.g. NodeMCU).
- A pump connected to a digital pin (default is `WATER_PIN`).
- A switch connected to a digital pin (default is `SWITCH_PIN`).

## Installation

1. Clone or download this repository.
2. Open the `mqtt_pump_control.ino` file in the Arduino IDE.
3. Install the PubSubClient and ArduinoJson libraries (if not already installed).
4. Modify the `config.h` file to include your MQTT server, user ID, and device ID.
5. Upload the sketch to your ESP8266 board.

## Usage

1. Power on your ESP32-DEVKIT V1 board.
2. The board will attempt to connect to the WiFi network.
3. Once connected, the board will attempt to connect to the MQTT broker.
4. Once connected, the board will subscribe to the MQTT topic.
5. To control the pump remotely, publish a message to the subscribed topic with the payload "{'pump': 'on'}" or "{'pump': 'off'}".
6. To control the pump locally, toggle the switch connected to the `SWITCH_PIN` digital pin.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.


------
# 아두이노 MQTT 펌프 제어

이 아두이노 스케치는 MQTT 브로커에 연결하여 펌프를 제어하는 예제입니다. 
원격으로 켜거나 끌수 있으며 스위치로 수동으로 켜고 끌 수 있게 구성하였습니다. 
## 의존성 라이브러리

- [PubSubClient](https://github.com/knolleary/pubsubclient) : MQTT 통신을 위한 클라이언트 라이브러리
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) : JSON 데이터를 파싱하고 생성하기 위한 라이브러리

## 하드웨어 요구사항

- ESP32 기반 보드 (ESP32-DEVKIT V1)
- 디지털 핀에 연결된 펌프 (기본값은 `WATER_PIN`)
- 디지털 핀에 연결된 스위치 (기본값은 `SWITCH_PIN`)

## 설치 방법

1. 이 저장소를 복제하거나 다운로드합니다.
2. 아두이노 IDE에서 `mqtt_pump_control.ino` 파일을 엽니다.
3. PubSubClient 및 ArduinoJson 라이브러리를 설치합니다 (미설치된 경우).
4. `config.h` 파일을 수정하여 MQTT 서버, 사용자 ID 및 디바이스 ID를 포함합니다.
5. 스케치를 ESP32-DEVKIT V1 보드에 업로드합니다.

## 사용 방법

1. ESP32-DEVKIT V1 보드의 전원을 켭니다.
2. 보드가 WiFi 네트워크에 연결을 시도합니다.
3. 연결되면 보드가 MQTT 브로커에 연결을 시도합니다.
4. 연결되면 보드가 MQTT 토픽을 구독합니다.
5. 펌프를 원격으로 제어하려면 구독한 토픽으로 "{'pump': 'on'}" 또는 "{'pump': 'off'}" 페이로드를 사용하여 메시지를 게시합니다.
6. 펌프를 로컬에서 제어하려면 `SWITCH_PIN` 디지털 핀에 연결된 스위치를 토글합니다.

## 라이선스

이 프로젝트는 MIT 라이선스에 따라 라이선스가 부여됩니다. 자세한 내용은 [LICENSE.md](LICENSE.md) 파일을 참조하십시오.