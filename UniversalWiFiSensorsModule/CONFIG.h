#pragma once
#include <Arduino.h>
//--------------------------------------------------------------------------------------------------------------------------------------
// настройки прошивки
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define _DEBUG // закомментировать для выключения отладочного режима (плюётся в Serial отладочной информацией на скорости 57600)
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки интервала обновления по умолчанию. Интервал можно также установить отсылом команды SET=INTERVAL|value\r\n, где value - значение в миллисекундах, \r\n - символы перевода строки
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define UPDATE_INTERVAL 10000 // интервал обновления показаний с датчиков, мс
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки коннекта по умолчанию. Параметры доступа п контроллеру можно также установить путём отправки в UART строки SET=ROUTER|id|pass\r\n, где id = адрес точки доступа
// контроллера, pass - пароль к точке доступа, \r\n - символы перевода строки
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CONTROLLER_SSID "TEPLICA" // имя сети Wi-Fi контроллера
#define CONTROLLER_PASSWORD "12345678" // пароль к сети Wi-Fi контроллера
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SEND_PACKET_DELAY 1000 // задержка после записи данных одного датчика на контроллер, для того, чтобы быть уверенными, что контроллер обработал данные (мс)
#define CLIENT_FLUSH_DELAY 100 // задержка после закрытия клиента, который отсылал очередной пакет данных, мс
#define CONNECT_TIMEOUT 30000 // таймаут коннекта, мс
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// режим глубокого сна (максимальный промежуток между пробуждениями - 35 минут)
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// для поддержки режима глубокого сна надо соединить GPIO16 (на NodeMCU - пин D0) с выводом RST на плате.
// при включенной подержке глубокого сна ESP после отправки данных засыпает, потом - рестартует сначала (с функции setup).
#define USE_DEEP_SLEEP // закомментировать, если не надо использовать режим глубокого сна
//#define DEEP_SLEEP_OFF_PIN D8 // номер пина для контроля запрещения режима сна (например, для настройки модуля). Закомментировать, если не надо использовать пин выключения режима сна.
// уровень на пине, при котором режим сна выключен. Настройка работает только совместно с USE_DEEP_SLEEP.
// На примере переключателя: подключили пин D8 через переключатель к земле, и подтянули к питанию резистором. Если переключатель выкл - режим сна работает. 
// Если переключаль при старте контроллера вкл - режим сна будет выключен, и можно беспрепятственно настраивать контроллер.
#define DEEP_SLEEP_SIGNAL_LEVEL LOW
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки датчиков
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// датчики прописываются через запятую, одна запись имеет вид
// { тип, индексВконтроллере, параметр1, параметр2, параметр3 }, где
// тип - тип датчика, индексВконтроллере - индекс датчика в контроллере, параметрN - необязательные параметры, зависящие от типа датчика.
// Для датчика DS18B20:
// { sensor_DS18B20, НОМЕР_ПИНА, РАЗРЕШЕНИЕ }, где РАЗРЕШЕНИЕ - одно из значений
// temp9bit, temp10bit, temp11bit, temp12bit
// ПРИМЕРЫ:
// { sensor_DS18B20, 3, D5, temp12bit } // датчик DS18B20 с индексом в контроллере 3, на пине D5, с разрешением 12 бит
// {sensor_BH1750, 3, BH1750Address1 } // датчик освещённости BH1750 с адресом 1 на шине I2C, индекс в контроллере - 3
// {sensor_BH1750, 5, BH1750Address2 } // датчик освещённости BH1750 с адресом 2 на шине I2C, индекс в контроллере - 5
// {sensor_Si7021, 4 } // датчик Si7021 на шине I2C, индекс в контроллере - 4
#define SENSORS { sensor_DS18B20, 3, D5, temp12bit },  { sensor_DS18B20, 4, D6, temp12bit }, {sensor_BH1750, 5, BH1750Address2 }, {sensor_Si7021, 4 }
//--------------------------------------------------------------------------------------------------------------------------------------
// дальше лазить - неосмотрительно :)
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// ||
// \/
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define NO_TEMPERATURE_DATA -128
#define NO_LUMINOSITY_DATA -1
//--------------------------------------------------------------------------------------------------------------------------------------
typedef enum
{
  sensor_NoSensor,
  sensor_DS18B20,
  sensor_DS18S20,
  sensor_BH1750,
  sensor_Si7021,
  
} SensorType;
//--------------------------------------------------------------------------------------------------------------------------------------
struct SensorSettings
{
  SensorType type;
  uint8_t targetIndex;
  uint8_t param1;
  uint8_t param2;
  uint8_t param3;
  void* data;

  SensorSettings()
  {
    type = sensor_NoSensor;
    param1 = param2 = param3 = 0;
    targetIndex = 0;
    data = NULL;
  }

  SensorSettings(SensorType t = sensor_NoSensor, uint8_t ti = 0, uint8_t p1 = 0, uint8_t p2 = 0, uint8_t p3 = 0, void* d = NULL)
  {
    type = t;
    targetIndex = ti;
    param1 = p1;
    param2 =  p2;
    param3 = p3;
    data = d;
    
  }
  
};
//--------------------------------------------------------------------------------------------------------------------------------------

