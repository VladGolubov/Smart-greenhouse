/*   --------------------------------------------------
     | Имя    : Smart Greenhouse                      |
     | Автор  : Влад Голубов                          |
     | Дата   : 24 ноября 2017                        |
     | Версия : 2.1                                   |
     --------------------------------------------------
     Функции:
     Контроль значений влажности почвы, воздуха, освещения, показ времени с момента включения.
    Материалы:
    датчик DS18B20, сервопривод SG90, датчик влажности , датчик освещенности CJMCU-TEMT6000 или фоторезистор, насосы для обогревателя почвы, двухстрочный lcd дисплей 1602.
*/
//----------Объявление библиотек----------
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
//Разкоментировать если используем экран
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10
#define sensor  10
#define hgPin  A0
#define hPin  A1
#define lPin  A2
/*#define butt_hold 500
  #define butt_double_timer 100*/
#define delay_time 200
//----------Обьявление переменных----------
unsigned long time;
unsigned long last_time;
boolean butt_flag = 0;
boolean butt = 0;
boolean windowButt1;
boolean windowButt2;
boolean windowButt3;
boolean windowButt4;
boolean butt_flagres = 0;
boolean butt_reset;
int hgvalue = 0;
//----------Обьявление массивов----------
int FanBoiler[] = {35, 36};
int Window[] = {31, 32, 33, 34};
int Pump[] = {39, 40, 37, 38};
//----------Обьявление переменных----------
int maxHumidity = 100;
int minHumidity = 80;
int maxTemperature = 20;
int minTemperature = 16;
int minTemperatureBoiler = 30;
int maxTemperatureBoiler = 100;
//----------Инициализация ----------
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x85, 0xD9 };
byte ip[] = { 192, 168, 0, 112 };
byte subnet[] = { 255, 255, 255, 0 };
byte gateway[] = { 192, 168, 0, 1 };
EthernetServer server(80);
//----------Обьявление пинов----------
//Разкоментировать если используем экран
LiquidCrystal_I2C lcd(0x27,16,2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Адреса датчиков dallas ds18b20
DeviceAddress Thermometer1 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 1 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer2 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 2 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer3 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 3 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer4 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 4 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer5 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 5 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer6 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 6 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer7 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 7 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer8 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 8 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer9 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 9 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer10 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 10 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer11 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 11 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer12 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 12 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer13 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 13 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer14 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 14 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer15 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 15 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer16 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 16 датчика DS18B20 280054B604000092:
DeviceAddress Thermometer17 = {
  0x28, 0x00, 0x54, 0xB6, 0x04, 0x00, 0x00, 0x92
}; // адрес 17 датчика DS18B20 280054B604000092:

void setup() {
  //----------Подключение интернета----------
  Serial.begin(9600);
  while (!Serial) {}
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //----------Объявление входов/выходов----------
  pinMode(Window[0, 1, 2, 3], OUTPUT);
  pinMode(FanBoiler[0, 1], OUTPUT);
  pinMode(Pump[0, 1, 2, 3], OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(hgPin, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  //----------Приветствие----------
  /*Разкоментировать если используем экран
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print( "Hello, user" );
    lcd.setCursor(0, 2);
    lcd.print("Smart greenhouse");
    lcd.clear();
    lcd.print("Light Side");
    lcd.setCursor(0, 2);
    lcd.print("Workshop");
    lcd.clear();*/
  //----------Считывание значений датчиков температуры----------
  sensors.begin();
  sensors.setResolution(Thermometer1, 10);
  sensors.setResolution(Thermometer2, 10);
  sensors.setResolution(Thermometer3, 10);
  sensors.setResolution(Thermometer4, 10);
  sensors.setResolution(Thermometer5, 10);
  sensors.setResolution(Thermometer6, 10);
  sensors.setResolution(Thermometer7, 10);
  sensors.setResolution(Thermometer8, 10);
  sensors.setResolution(Thermometer9, 10);
  sensors.setResolution(Thermometer10, 10);
  sensors.setResolution(Thermometer11, 10);
  sensors.setResolution(Thermometer12, 10);
  sensors.setResolution(Thermometer13, 10);
  sensors.setResolution(Thermometer14, 10);
  sensors.setResolution(Thermometer15, 10);
  sensors.setResolution(Thermometer16, 10);
  sensors.setResolution(Thermometer17, 10);
}
void printTemperature(DeviceAddress deviceAddress) {
  float tempC = sensors.getTempC(deviceAddress);
}
void(* resetFunc) (void) = 0;

void loop() {
  //----------Управление температурой открывания окон----------
  void readTemperature(DeviceAddress deviceAddress);

  float temp4 = sensors.getTempC(Thermometer4);
  if (float temp4 = sensors.getTempC(Thermometer4) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[0], HIGH);
  } else if (float temp4 = sensors.getTempC(Thermometer4) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[0], LOW);
  }
  float temp6 = sensors.getTempC(Thermometer6);
  if (float temp6 = sensors.getTempC(Thermometer6) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[5], HIGH);
  } else if (float temp6 = sensors.getTempC(Thermometer6) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[5], LOW);
  }
  float temp8 = sensors.getTempC(Thermometer8);
  if (float temp8 = sensors.getTempC(Thermometer8) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[1], HIGH);
  } else if (float temp8 = sensors.getTempC(Thermometer8) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[1], LOW);
  }
  float temp9 = sensors.getTempC(Thermometer9);
  if (float temp9 = sensors.getTempC(Thermometer9) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[2], HIGH);
  } else if (float temp9 = sensors.getTempC(Thermometer9) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[2], LOW);
  }
  float temp10 = sensors.getTempC(Thermometer10);
  if (float temp10 = sensors.getTempC(Thermometer10) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[3], HIGH);
  } else if (float temp10 = sensors.getTempC(Thermometer10) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[3], LOW);
  }
  float temp13 = sensors.getTempC(Thermometer13);
  if (float temp13 = sensors.getTempC(Thermometer13) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[4], HIGH);
  } else if (float temp13 = sensors.getTempC(Thermometer13) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[4], LOW);
  }
  float temp14 = sensors.getTempC(Thermometer14);
  if (float temp14 = sensors.getTempC(Thermometer14) <  minTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[4], HIGH);
  } else if (float temp14 = sensors.getTempC(Thermometer14) >  maxTemperature && millis() - last_time > delay_time) {
    digitalWrite(Window[4], LOW);
  }

  //----------Управление влажностью почвы----------
  void readHumidity_ground();
  hgvalue = analogRead(hgPin);
  hgvalue = map(hgvalue, 0, 1024, 0, 100);
  if (hgvalue <= maxHumidity){
    digitalWrite(Pump[4, 3, 2, 1], HIGH);
  } else {
    digitalWrite(Pump[4, 3, 2, 1], LOW);
  }
  //----------Управление котлом----------
  void control_Fan();
  float temp1 = sensors.getTempC(Thermometer1);
  if (float temp1 = sensors.getTempC(Thermometer1) <  minTemperatureBoiler && millis() - last_time > delay_time) {
    digitalWrite(FanBoiler[0], HIGH);
  } else if (float temp1 = sensors.getTempC(Thermometer1) >  maxTemperatureBoiler && millis() - last_time > delay_time) {
    digitalWrite(FanBoiler[0], LOW);
  };
  //----------Контроль значенний----------
//Разкоментировать если используем экран
  void valueLCD();
  lcd.print("Time:");
  time = millis();
  lcd.println(time);
  lcd.clear();
  unsigned long last_timeLCD;
  butt = !digitalRead(3);
  if (butt == 1 && butt_flag == 0 && millis() - last_timeLCD > 500) {
    switch (last_timeLCD) {
      case 3000: {
          lcd.print("1 теплица °С");
          lcd.println(sensors.getTempC(Thermometer5));
          break;
        }
      case 6000:{
          lcd.print("2 теплица °С");
          lcd.println(sensors.getTempC(Thermometer16));
          break;
        }
       case 9000:{
          lcd.print("3 теплица °С");
          lcd.println(sensors.getTempC(Thermometer7));
          break;
        }
       case 12000:{
          lcd.print("4 теплица °С");
          lcd.println(sensors.getTempC(Thermometer11));
          break;
        }
       case 15000:{
          lcd.print("5 теплица °С");
          lcd.println(sensors.getTempC(Thermometer12));
          break;
        }
      case 18000:{
          lcd.print("6 теплица °С");
          lcd.println(sensors.getTempC(Thermometer17));
          break;
        }
      case 21000:{
          lcd.print("7 теплица °С");
          lcd.println(sensors.getTempC(Thermometer15));
          break;
        }
        //----------Контроль температуры котла----------
        lcd.print("Выход котла 1");
        lcd.println(sensors.getTempC(Thermometer1));
        lcd.clear();
        delay(100);
        lcd.print("Выход котла 2");
        lcd.println(sensors.getTempC(Thermometer2));
        lcd.clear();
        delay(100);
        lcd.print("Вход котла");
        lcd.println(sensors.getTempC(Thermometer2));
        lcd.clear();
        delay(100);
    }
  }
    void Reset_Button();
    butt = !digitalRead(4);
    if (butt_reset == 1 && butt_flagres == 0) {
      resetFunc();
    }
    //----------Контроль значенний----------
    EthernetClient client = server.available();
    if (client) {
      Serial.println("Новый клиент");
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          char d = client.read();
          char b = client.read();
          char a = client.read();
          if (windowButt1 && c == ' ') {
            windowButt1 = 0;
          }
          if (c == '$') {
            windowButt1 = 1;
          }
          if (windowButt1 == 1) {
            Serial.println(c);
            if (c == '1') {
              Serial.println("ON");
              digitalWrite(Window[0], HIGH);
            }
            if (c == '2') {
              Serial.println("OFF");
              digitalWrite(Window[0], LOW);
            }
          }
          if (windowButt2 && d == ' ') {
            windowButt2 = 0;
          }
          if (d == '&') {
            windowButt2 = 1;
          }
          if (windowButt2 == 1) {
            Serial.println(d);
            if (d == '1') {
              Serial.println("ON");
              digitalWrite(Window[1], HIGH);
            }
            if (d == '2') {
              Serial.println("OFF");
              digitalWrite(Window[1], LOW);
            }
          }
          //Serial.write(c);
          if (c == '\n' && currentLineIsBlank) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 10");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Ethernet control greenhouse</title>");
            client.println("<meta http-equiv=\"refresh\" content=\"1\">");
            client.println("<body bgcolor = #0B0705>");
            client.println("<body text = #FFFFFF>");
            client.println("<a href=</http://vk.com/light_side_diy</a>");
            client.print("<a href=\"/$1\"><button>On</button></a>");       //кнопка включить
            client.print("<a href=\"/$2\"><button>Off</button></a>");      //кнопка выключить
            client.print("<a href=\"/&1\"><button>On</button></a>");       //кнопка включить
            client.print("<a href=\"/&2\"><button>Off</button></a>");      //кнопка выключить
            client.println();
            client.println("Выход котла 1 ");
            client.print(sensors.getTempC(Thermometer1));
            client.println("<br />");
            client.print("Выход котла 2 ");
            client.print(sensors.getTempC(Thermometer2));
            client.println("<br />");
            client.print("Вход котла 3");
            client.print(sensors.getTempC(Thermometer3));
            client.println("<br />");
          }
          client.println("</body>");
          client.println("</head>");
          client.println("</html>");
          break;
          if (c == '\n') {
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }

      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
    /*Разкоментировать если используем экран
      lcd.println("client disconnected");*/
  }


