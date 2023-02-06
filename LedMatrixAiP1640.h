#include <Arduino.h>

class LedMatrixAiP1640
{
private:
  bool debug;
  int pinClock;
  int pinData;

  void I2CStart();
  void I2CSend(unsigned char data);
  void I2CEnd();

public:
  LedMatrixAiP1640(int iPinClock, int iPinData);

  // Init
  void init();

  // Debug
  void setDebug(bool dbg);
  void display(unsigned char entries[]);
};
