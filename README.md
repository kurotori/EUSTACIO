# EUSTACIO
## _Explorador UltraSónico Terrestre de Ambientes Cerrados Inalámbricamente Operado_

**EUSTACIO** es un proyecto personal para desarrollar un sistema robótico semi-autónomo capaz de orientarse y navegar una habitación o habitaciones, detectando los obstáculos y registrando la ubicación de los mismos en un archivo.

El sistema estará compuesto de la siguiente manera:

1) _**El robot semi-autónomo EUSTACIO**_
2) _**El sistema de análisis y navegación PyLOTO** (nombre provisorio)_


### El robot EUSTACIO
Esta basado en un chasis de dos ruedas barato y de amplia difusión (con algunas modificaciones para acomodar ciertos aspectos del sistema) y se trata de un robot móvil con sensores de orientación (un magnetómetro), movimiento (un acelerómetro y sensores de movimiento de las ruedas) y cercanía (un sensor de distancia ultrasónico y sensores mecánicos de choque), comunicación inalámbrica (WiFi y/o Bluetooth), y almacenamiento de datos (un lector de tarjetas SD).
Este robot se esta diseñando con un enfoque modular, haciendo uso de varias placas _Arduino Nano_ y _Espressif ESP32 DevkitC v4_, de forma que las mismas se ocupen de diferentes aspectos del funcionamiento del mismo.

> El uso de estas placas y no otras, más potentes (como ser _Raspberry Pi_), se debe a que **son los recursos que tengo en mi posesión y con los que estoy más familiarizado**. De todas maneras, **este hecho no descarta** la inclusión de hardware más potente en etapas posteriores, u otras iteraciones, de este proyecto.

**EUSTACIO** contará con un nivel discreto de autonomía, de forma que, por su cuenta, al activarse:
- Determine su capacidad de exploración (movilidad, objetos cercanos, conexión de red, carga de baterías, etc.)
- Intente conectarse al sistema **PyLOTO** a travez de una red inalámbrica indicada en sus archivos de configuración en la tarjeta SD de a bordo.
- Comience la exploración de su entorno, con o sin asistencia del sistema **PyLOTO**

### El sistema PyLOTO
Un sistema de navegación que probablemente será desarrollado en _Python_ más adelante. Este sistema se ocupará de establecer un servicio en la red (probablemente en la forma de un _webservice_) a la espera de que **EUSTACIO** se conecte al mismo y comience a enviarle telemetría. Con dicha información, **PyLOTO** analizará y determinará la ubicación actual y el rumbo que debe tomar **EUSTACIO**.
> Si bien la expectativa es el desarrollo de este software en Python, no se puede descartar cambios, ya que se trata de un paso a desarrollarse muy adelante, sobre el cual no hay ningún detalle en firme. Incluso el nombre del software podría cambiar, eventuálmente.

**PyLOTO** actuará como una inteligencia artificiál remota para **EUSTACIO**, permitiendo, a su vez, el registro y visualización del entorno detectado por el robot, con miras a que el sistema, eventuálmente, sea capaz de identificar una zona ya explorada previamente.
