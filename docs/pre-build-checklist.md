# Pre-build checklist for firmware-c

Короткий чеклист перед первой попыткой сборки `firmware-c`.

## 1. Локальный config создан
Должен существовать файл:

```text
firmware-c/src/config.h
```

Он создаётся из:

```text
firmware-c/src/config.h.example
```

## 2. Wi‑Fi значения заполнены
В `config.h` должны быть реальные значения:
- `PICO_HID_BRIDGE_WIFI_SSID`
- `PICO_HID_BRIDGE_WIFI_PASSWORD`

## 3. `PICO_SDK_PATH` задан
Проверка в PowerShell:

```powershell
$env:PICO_SDK_PATH
```

## 4. Инструменты видны из PATH
Проверка:

```powershell
cmake --version
ninja --version
arm-none-eabi-gcc --version
```

## 5. Ожидания по результату правильные
Текущая цель первой сборки не TCP и не full bridge.

Текущая цель:
- собрать `.uf2`
- прошить Pico W
- увидеть HID mouse detection
- увидеть demo mouse movement

## 6. Если сборка упадёт
Это не провал. На этом этапе мы как раз собираем первый feedback loop по реальному Pico SDK проекту.

Лучше сразу сохранить:
- текст ошибки CMake
- текст ошибки компилятора
- на каком файле упало

И уже по этому быстро дожмём.
