# Build on Windows with Pico SDK

Инструкция для сборки `firmware-c/` на Windows.

## Что понадобится

Минимальный набор:
- `git`
- `cmake`
- `ninja` или `make`
- `ARM GNU Toolchain (arm-none-eabi-gcc)`
- `pico-sdk`

## Рекомендуемый путь

Если хочется быстро и без ручного ада, лучше ставить:
- `Git for Windows`
- `CMake`
- `Ninja`
- `ARM GNU Toolchain`

И работать либо из:
- `Developer PowerShell`
- обычного `PowerShell`
- либо `Git Bash`

## 1. Клонировать репозиторий

```powershell
git clone https://github.com/transystor/pico-hid-bridge.git
cd pico-hid-bridge
```

## 2. Получить Pico SDK

Например так:

```powershell
git clone https://github.com/raspberrypi/pico-sdk.git C:\dev\pico-sdk
cd C:\dev\pico-sdk
git submodule update --init
```

## 3. Поставить переменную `PICO_SDK_PATH`

В текущую сессию PowerShell:

```powershell
$env:PICO_SDK_PATH = "C:\dev\pico-sdk"
```

Проверка:

```powershell
$env:PICO_SDK_PATH
```

## 4. Проверить toolchain

Должны работать команды:

```powershell
cmake --version
ninja --version
arm-none-eabi-gcc --version
```

Если какой-то команды нет, сначала нужно поставить соответствующий инструмент и открыть новое окно терминала.

## 5. Создать build directory

Из корня репозитория:

```powershell
cd firmware-c
mkdir build
cd build
```

## 6. Сгенерировать build system

Для Ninja:

```powershell
cmake -G Ninja ..
```

Если всё ок, CMake найдёт Pico SDK через `PICO_SDK_PATH`.

## 7. Собрать проект

```powershell
ninja
```

Ожидаемый результат, после успешной сборки появятся файлы:
- `pico_hid_bridge.uf2`
- `pico_hid_bridge.elf`
- `pico_hid_bridge.bin`

## 8. Залить `.uf2` на Pico W

1. Зажать `BOOTSEL`
2. Подключить Pico W по USB
3. Появится диск `RPI-RP2`
4. Скопировать туда:

```text
firmware-c/build/pico_hid_bridge.uf2
```

## Важные замечания

## Это пока scaffold
Текущий `firmware-c/` ещё не финален и может не собраться с первого раза без дополнительных правок по зависимостям и конфигу Pico SDK/TinyUSB/lwIP.

Эта инструкция нужна, чтобы:
- зафиксировать build path,
- собрать toolchain,
- и дальше уже быстро довести код до реального first build.

## Если `pico_sdk_import.cmake` ругается
Скорее всего не задан:
- `PICO_SDK_PATH`

Проверь:

```powershell
$env:PICO_SDK_PATH
```

## Если не найден `arm-none-eabi-gcc`
Нужно поставить ARM GNU Toolchain и перезапустить терминал.

## Если не найден `ninja`
Поставь Ninja или используй другой generator CMake.

## Следующий шаг после первого build path
После того как toolchain готов, нужно будет:
1. довести `firmware-c/` до первой успешной сборки,
2. потом до первого USB HID detection,
3. потом до первого TCP listener.
