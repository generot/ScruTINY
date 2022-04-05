# ScruTINY

[![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)](http://cppreference.com/)
[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)

![logo](https://github.com/generot/ScruTINY-online/blob/main/client/static/css/logo3.png?raw=true)

## Какво е ScruTINY?
ScruTINY е преносима система за защита, може да бъде поставена на всякъде, по всяко време. 
Тя е приспособена за безжична комуникация със собственика си.

## Как работи?
Това се постига чрез връзка, посредством Wi-Fi мрежа. Системата трябва първоначално да бъде 
конфигурирана с компютър/лаптоп, за да може да осъществява връзка с дадена (по време на конфигурацията) 
Wi-Fi мрежа. ScruTINY осъществява предназначението си чрез засичане на движение. 
При смущаване на сензора на системата (засечено движение в стаята), тя изпраща информация за смута на 
[**онлайн сървър**](https://github.com/generot/ScruTINY-online), от който собственикът може да види пратената информация, независимо къде се намира на 
света (стига да има връзка с Интернет). <br><br>

Освен това, се активира и звуковата аларма на системата, която се състои от един зумер 
(buzzer - високоговорител, който издава пищящ звук), с цел да разобличи 
случващото се на хора в периметъра.

## Използвани технологии
Дадена е и хардуерната, и софтуерната технология.

### Хардуер
- [Arduino - микроконтролер](https://www.arduino.cc/)
- [ESP8266 - Wi-Fi модул](https://erelement.com/wireless/wi-fi-esp8266)
- [HC-SR04 - ултразвуков сензор](https://www.sparkfun.com/products/15569)

### Софтуер
- [WiFiEsp - библиотека за работа с Wi-FI модула(като shield)](https://github.com/bportaluri/WiFiEsp)

## Автор на проекта
- Мартин Наков(10 клас)