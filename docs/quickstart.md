# Quickstart

Пошаговый запуск MVP на Raspberry Pi Pico W.

## Что понадобится

- Raspberry Pi Pico W
- USB-кабель с передачей данных
- ПК для прошивки Pico W
- Wi-Fi сеть 2.4 GHz
- игровой ПК или обычный ПК для проверки HID-мыши

## 1. Установить CircuitPython на Pico W

1. Отключи Pico W.
2. Зажми кнопку `BOOTSEL`.
3. Подключи Pico W по USB к ПК.
4. Отпусти `BOOTSEL`.
5. Pico появится как накопитель `RPI-RP2`.
6. Скачай актуальный `CircuitPython` для `Raspberry Pi Pico W`.
7. Скопируй `.uf2` файл на `RPI-RP2`.
8. После перезагрузки появится диск `CIRCUITPY`.

## 2. Скопировать файлы прошивки

Из этого репозитория нужны:

- `firmware/code.py`
- `firmware/settings.toml.example`

На диске `CIRCUITPY`:

1. скопируй `code.py` в корень,
2. `settings.toml.example` переименуй в `settings.toml`,
3. тоже положи в корень `CIRCUITPY`.

Итог на устройстве:

```text
CIRCUITPY/
  code.py
  settings.toml
```

## 3. Заполнить `settings.toml`

Пример:

```toml
WIFI_SSID = "MyWifi"
WIFI_PASSWORD = "SuperSecretPassword"
LISTEN_PORT = "5000"
```

## 4. Установить библиотеку HID

На `CIRCUITPY` должна быть библиотека `adafruit_hid`.

Обычно это делается так:
1. скачать `Adafruit CircuitPython Bundle`,
2. из папки `lib` взять `adafruit_hid`,
3. скопировать её в `CIRCUITPY/lib/`.

Итог:

```text
CIRCUITPY/
  code.py
  settings.toml
  lib/
    adafruit_hid/
```

## 5. Проверить, что Pico W загрузился

Открой serial console CircuitPython и посмотри вывод.
Ожидаемо увидеть что-то вроде:

```text
Connecting to Wi-Fi: MyWifi
Wi-Fi connected, IP: 192.168.0.50
Listening on 192.168.0.50:5000
```

Если `wifi.radio.connect(...)` у твоей точки доступа кидает исключение, но IP уже реально выдан, новая версия прошивки это покажет в логе и попробует продолжить работу.

## 6. Подключить Pico W к целевому ПК

На первом этапе проверь даже на обычном ПК:
- система должна увидеть HID-мышь,
- после сетевой команды курсор должен начать двигаться.

## 7. Послать первую команду

С Raspberry Pi 4, Linux-машины или любого ПК в той же сети:

```bash
printf 'PING\n' | nc 192.168.0.50 5000
```

Ожидаемый ответ:

```text
OK PONG
```

Дальше:

```bash
printf 'MOVE 20 0\n' | nc 192.168.0.50 5000
```

Ожидаемый результат:
- курсор сдвинется вправо,
- в ответ придёт `OK`.

Клик:

```bash
printf 'CLICK LEFT\n' | nc 192.168.0.50 5000
```

## 8. Проверка основных команд

### Move

```bash
printf 'MOVE 10 5\n' | nc <PICO_IP> 5000
```

### Left click

```bash
printf 'CLICK LEFT\n' | nc <PICO_IP> 5000
```

### Right click

```bash
printf 'CLICK RIGHT\n' | nc <PICO_IP> 5000
```

### Hold left button

```bash
printf 'DOWN LEFT\n' | nc <PICO_IP> 5000
printf 'UP LEFT\n' | nc <PICO_IP> 5000
```

## 9. Типичные проблемы

### Нет `CIRCUITPY`
Скорее всего CircuitPython не прошился или USB-кабель только для питания.

### Не импортируется `adafruit_hid`
Не скопирована библиотека `adafruit_hid` в `lib/`.

### Не подключается к Wi-Fi
- неверный SSID или пароль,
- сеть не 2.4 GHz,
- слабый сигнал.

### Нет движения курсора
- Pico не определился как HID,
- ошибка в `code.py`,
- TCP-команда не дошла,
- целевой ПК не принимает HID как ожидается.

## 10. Что дальше

После успешного MVP:
1. добавить команды keyboard,
2. добавить `VERSION` и `RESET`,
3. сделать маленький Python client на Raspberry Pi 4,
4. добавить safety-ограничения по частоте и амплитуде движения.
