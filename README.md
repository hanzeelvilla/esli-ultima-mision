# ESLI: Última Misión

Repo oficial del mejor juego de la decada creado por **Esli Laboratorios**.
![Logo Esli Laboratorios](/assets/logo_equipo.jpg)

## Requerimentos
- 1 Raspberry Pi Pico RP2040 W
- Pantalla OLED 128x64
- 8 push buttons
- 1 Leds rojo
- 1 Led azul
- 2 Resistencias de 330 ohms
- 1 Protoboard

## Conexiones

| Componente | Pin ESP32 (u otro microcontrolador) | Descripción        |
|------------|-------------------------------------|--------------------|
| LED (+)    | GPIO 15                             | Señal de encendido |
| LED (–)    | GND                                 | Tierra             |
| Resistencia (220Ω - 330Ω) | Entre GPIO 15 y el ánodo del LED | Limita la corriente |

> [!WARNING]
> La resistencia se coloca en serie con el LED para evitar que se queme por exceso de corriente.

## Configuración 

1. Clona el repositorio
```bash
git clone git@github.com:hanzeelvilla/esli-ultima-mision.git
```

2. Ingresar al directorio
```bash
cd esli-ultima-mision
```

3. Cambia de nombre el archivo `config_template.h` a `config.h` e ingresa tus creedenciales de internet.
4. Sube el código a la placa

## Repos relacionados

### Página Web
- [Front](https://github.com/angelverduzco/esli-game-page)
- [Back](https://github.com/angelverduzco/esli-game-api)

### Librerías
- [MyLedIO](https://github.com/hanzeelvilla/MyLedIO)
- [MyButtonIO](MyButtonIO)