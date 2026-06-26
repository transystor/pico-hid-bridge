# Этот файл обычно копируют из Pico SDK examples.
# Для первого scaffold держим его как тонкую обёртку, чтобы структура проекта была полной.

if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

if (NOT PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not set. Point it to your pico-sdk checkout.")
endif ()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
