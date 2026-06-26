import os
import time
import socketpool
import wifi
import usb_hid

from adafruit_hid.mouse import Mouse


mouse = Mouse(usb_hid.devices)

WIFI_SSID = os.getenv("WIFI_SSID")
WIFI_PASSWORD = os.getenv("WIFI_PASSWORD")
LISTEN_PORT = int(os.getenv("LISTEN_PORT", "5000"))


LEFT = Mouse.LEFT_BUTTON
RIGHT = Mouse.RIGHT_BUTTON


def connect_wifi():
    if not WIFI_SSID or not WIFI_PASSWORD:
        raise RuntimeError("WIFI_SSID or WIFI_PASSWORD is not set in settings.toml")

    print(f"Connecting to Wi-Fi: {WIFI_SSID}")
    wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
    print(f"Wi-Fi connected, IP: {wifi.radio.ipv4_address}")



def parse_button(value: str):
    upper = value.upper()
    if upper == "LEFT":
        return LEFT
    if upper == "RIGHT":
        return RIGHT
    raise ValueError("bad_button")



def handle_command(command: str):
    command = command.strip()
    if not command:
        return "ERR empty"

    parts = command.split()
    op = parts[0].upper()

    if op == "PING":
        return "OK PONG"

    if op == "MOVE":
        if len(parts) != 3:
            return "ERR bad_argument"

        try:
            dx = int(parts[1])
            dy = int(parts[2])
        except ValueError:
            return "ERR bad_argument"

        if dx < -127 or dx > 127 or dy < -127 or dy > 127:
            return "ERR bad_argument"

        mouse.move(x=dx, y=dy)
        return "OK"

    if op == "CLICK":
        if len(parts) != 2:
            return "ERR bad_argument"

        try:
            button = parse_button(parts[1])
        except ValueError:
            return "ERR bad_argument"

        mouse.click(button)
        return "OK"

    if op == "DOWN":
        if len(parts) != 2:
            return "ERR bad_argument"

        try:
            button = parse_button(parts[1])
        except ValueError:
            return "ERR bad_argument"

        mouse.press(button)
        return "OK"

    if op == "UP":
        if len(parts) != 2:
            return "ERR bad_argument"

        try:
            button = parse_button(parts[1])
        except ValueError:
            return "ERR bad_argument"

        mouse.release(button)
        return "OK"

    return "ERR unknown_command"



def run_server():
    pool = socketpool.SocketPool(wifi.radio)
    server = pool.socket(pool.AF_INET, pool.SOCK_STREAM)
    server.setsockopt(pool.SOL_SOCKET, pool.SO_REUSEADDR, 1)
    server.bind((str(wifi.radio.ipv4_address), LISTEN_PORT))
    server.listen(1)

    print(f"Listening on {wifi.radio.ipv4_address}:{LISTEN_PORT}")

    while True:
        client, addr = server.accept()
        print("Client connected:", addr)

        try:
            buffer = b""
            while True:
                data = client.recv(64)
                if not data:
                    break

                buffer += data

                while b"\n" in buffer:
                    raw_line, buffer = buffer.split(b"\n", 1)
                    line = raw_line.decode("utf-8", errors="ignore")
                    print("Command:", line)

                    try:
                        response = handle_command(line)
                    except Exception as ex:
                        print("Internal error:", ex)
                        response = "ERR internal"

                    client.send((response + "\n").encode("utf-8"))
        finally:
            client.close()
            print("Client disconnected")



def main():
    while True:
        try:
            connect_wifi()
            run_server()
        except Exception as ex:
            print("Fatal loop error:", ex)
            time.sleep(3)


main()
