# pico-hid-bridge

Проект для Raspberry Pi Pico W, который:
- подключается к игровому ПК по USB как HID-устройство,
- принимает простые сетевые команды от Raspberry Pi 4,
- эмулирует движения мыши и клики.

## Текущий статус

Мы начали с CircuitPython MVP, но упёрлись в нестабильное поведение Wi‑Fi на Pico W.
Поэтому основная ветка проекта теперь смещается в сторону:

- `Pico SDK + C/C++`
- `TinyUSB` для HID
- `cyw43/lwIP` для Wi‑Fi и TCP listener

CircuitPython-заготовка остаётся в репозитории как быстрый прототип и историческая reference-ветка.

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

### На Pico W, целевое направление
- Pico SDK
- TinyUSB HID Mouse
- cyw43 Wi‑Fi
- lwIP TCP listener

### На Pico W, временный MVP
- CircuitPython
- USB HID Mouse
- Wi-Fi client
- TCP command listener

### На Raspberry Pi 4
- .NET service или Python daemon / API
- TCP client to Pico W

## Структура проекта

- `firmware/` — ранний CircuitPython MVP
- `firmware-c/` — новое основное направление на Pico SDK / C
- `protocol/` — описание текстового протокола
- `notes/` — инженерные заметки и дальнейшие шаги
- `docs/` — инструкции по запуску и эксплуатации

## Быстрый старт

Для раннего CircuitPython MVP:
- `docs/quickstart.md`

Для нового направления на Pico SDK:
- `docs/pico-sdk-plan.md`
- `docs/build-windows.md`
- `docs/first-build-goal.md`

Для `firmware-c/` пока добавлен scaffold.
Следующим шагом нужно будет поднять полноценную сборку через Pico SDK и довести до первого HID + TCP handshake.

## Ограничения первой версии

- без клавиатуры,
- без абсолютного позиционирования,
- только relative mouse move,
- без TLS,
- без сложной auth-модели,
- одна активная TCP-сессия.

## Следующие шаги

1. Довести `firmware-c/` до собираемого состояния через Pico SDK.
2. Поднять первый USB HID mouse report на TinyUSB.
3. Поднять первый TCP listener через lwIP.
4. Принять первую команду `MOVE 10 0`.
5. Проверить первый клик `CLICK LEFT`.
6. После этого добавлять keyboard, queue и safety-ограничения.
