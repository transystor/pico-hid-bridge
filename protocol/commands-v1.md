# Commands v1

Минимальный текстовый протокол между Raspberry Pi 4 и Pico W.

## Transport

- TCP
- UTF-8 text
- одна команда на строку
- разделитель строк: `\n`

## Общие правила

- Pico W читает строку целиком
- выполняет команду
- отвечает одной строкой
- успешный ответ: `OK`
- ошибка: `ERR <reason>`

## Supported commands

### Health

```text
PING
```

Response:

```text
OK PONG
```

---

### Relative mouse move

```text
MOVE <dx> <dy>
```

Примеры:

```text
MOVE 10 0
MOVE -5 12
```

Response:

```text
OK
```

---

### Mouse click

```text
CLICK LEFT
CLICK RIGHT
```

Response:

```text
OK
```

---

### Mouse button down

```text
DOWN LEFT
DOWN RIGHT
```

Response:

```text
OK
```

---

### Mouse button up

```text
UP LEFT
UP RIGHT
```

Response:

```text
OK
```

---

## Validation rules

- `dx`, `dy` в MVP ограничить диапазоном `-127..127`
- неизвестная команда -> `ERR unknown_command`
- неверный аргумент -> `ERR bad_argument`
- внутренняя ошибка -> `ERR internal`

## Future extensions

Потом можно добавить:
- `WHEEL <delta>`
- `KEY_TAP <key>`
- `KEY_DOWN <key>`
- `KEY_UP <key>`
- `HOTKEY CTRL+SHIFT+S`
- `VERSION`
- `RESET`
