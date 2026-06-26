# pico-hid-bridge

MVP-проект для Raspberry Pi Pico W, который:
- подключается к игровому ПК по USB как HID-устройство,
- принимает простые сетевые команды от Raspberry Pi 4,
- эмулирует движения мыши и клики.

## Архитектура первой версии

```text
[ AI / orchestration ]
          |
          v
[ Raspberry Pi 4 ] -- Wi-Fi --> [ Pico W ] -- USB HID --> [ PC ]
```

В первой версии делаем только мышь:
- `MOVE dx dy`
- `CLICK LEFT`
- `CLICK RIGHT`
- `DOWN LEFT`
- `UP LEFT`
- `DOWN RIGHT`
- `UP RIGHT`
- `PING`

## Почему не HTTP API на Pico

На Pico W лучше держать минимальную прошивку:
- меньше памяти,
- проще отладка,
- меньше точек отказа.

Поэтому для MVP используем очень простой текстовый TCP-протокол.

## План по стеку

### На Pico W
- CircuitPython
- USB HID Mouse
- Wi-Fi client
- TCP command listener

### На Raspberry Pi 4
- Python daemon / API
- TCP client to Pico W

## Структура проекта

- `firmware/` — прошивка для Pico W
- `protocol/` — описание текстового протокола
- `notes/` — инженерные заметки и дальнейшие шаги

## Ограничения первой версии

- без клавиатуры,
- без абсолютного позиционирования,
- только relative mouse move,
- без TLS,
- без сложной auth-модели,
- одна активная TCP-сессия.

## Следующие шаги

1. Поднять прошивку Pico W на CircuitPython.
2. Проверить, что ПК видит Pico как мышь.
3. Поднять Wi-Fi соединение Pico W.
4. Принять первую команду `MOVE 10 0`.
5. Проверить первый клик `CLICK LEFT`.
6. После этого добавлять keyboard и safety-ограничения.
