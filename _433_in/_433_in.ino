// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
#include <VirtualWire.h>
//Светодиод на 13 пине Arduino загорается, когда приходит '1' и тухнет, когда поступает '0'.
// Tx на пине D12
void setup()
{
  vw_set_ptt_inverted(true); // необходимо для модуля DR3100
  vw_set_rx_pin(12);
  vw_setup(4000); // бит в секунду
  pinMode(13, OUTPUT);
  vw_rx_start(); // запуск фазовой автоподстройки частоты (ФАПЧ)
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Не блокируется
  {
    if (buf[0] == '1') {
      digitalWrite(13, 1);
    }
    if (buf[0] == '0') {
      digitalWrite(13, 0);
    }
  }
}
