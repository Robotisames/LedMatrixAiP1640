#include <LedMatrixAiP1640.h>

/**
 * @brief Constructeur de la classe LedMatrixAiP1640.
 * 
 * @see https://fr.wikipedia.org/wiki/I2C
 * 
 * @param iPinClock le numéro de la broche SCL (Serial Clock Line) pour la synchronisation
 * @param iPinData le numéro de la broche SDA (Serial Data Line) pour les données
 */
LedMatrixAiP1640::LedMatrixAiP1640(int iPinClock, int iPinData)
{
  debug = false;
  pinClock = iPinClock;
  pinData = iPinData;
}

/**
 * @brief Initialisation de la matrice de LEDs.
 * Cette méthode doit être appelée dans la méthode setup de votre sketch Arduino.
 */
void LedMatrixAiP1640::init()
{
  pinMode(pinClock, OUTPUT);
  pinMode(pinData, OUTPUT);
}

/**
 * @brief Active/désactive le mode debug.
 * 
 * @param dbg true = active.
 */
void LedMatrixAiP1640::setDebug(bool dbg)
{
  debug = dbg;
}

/**
 * @brief Initialise/débute la communication maître-esclave suivant le protocole I2C.
 * 
 * @see https://fr.wikipedia.org/wiki/I2C
 */
void LedMatrixAiP1640::I2CStart()
{
  digitalWrite(pinClock, HIGH);
  delayMicroseconds(3);
  digitalWrite(pinData, HIGH);
  delayMicroseconds(3);
  digitalWrite(pinData,LOW);
  delayMicroseconds(3);
}

/**
 * @brief Termine la communication maître-esclave suivant le protocole I2C.
 * 
 * @see https://fr.wikipedia.org/wiki/I2C
 */
void LedMatrixAiP1640::I2CEnd()
{
  digitalWrite(pinClock, LOW);
  delayMicroseconds(3);
  digitalWrite(pinData, LOW);
  delayMicroseconds(3);
  digitalWrite(pinClock, HIGH);
  delayMicroseconds(3);
  digitalWrite(pinData, HIGH);
  delayMicroseconds(3);
}

/**
 * @brief Définit l'affichage de la matrice de LEDs.
 * 
 * @see http://dotmatrixtool.com/
 * 
 * @param entries un tableau de 16 x 8 bits.
 */
void LedMatrixAiP1640::display(unsigned char entries[])
{
  I2CStart();
  I2CSend(0xc0);
  for(int i = 0 ; i < 16 ; i++)
  {
    I2CSend(entries[i]);
  }

  I2CEnd();
  
  I2CStart();
  I2CSend(0x8A);
  I2CEnd();
}

/**
 * @brief Envoie des données vers la matrice de LEDs.
 * 
 * @param data des données codées sur 8 bits.
 */
void LedMatrixAiP1640::I2CSend(unsigned char data)
{
  for(char i = 0 ; i < 8 ; i++)
  {
    digitalWrite(pinClock, LOW);
    delayMicroseconds(3);

    if(data & 0x01)
    {
      digitalWrite(pinData, HIGH);
    }
    else
    {
      digitalWrite(pinData, LOW);
    }
    delayMicroseconds(3);

    digitalWrite(pinClock, HIGH);
    delayMicroseconds(3);

    data = data >> 1;
  }
}