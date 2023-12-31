#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int restartBtn = 2;
const int pausaBtn = 3;
const int enciendeLuzBtn = 4;
const int ledPin = 5;
const int piezoPin = 6;
const int luzDisplayPin = 13;

unsigned long tiempoInicial;
unsigned long tiempoActual;
unsigned long tiempoTranscurrido;
unsigned long momentoEncendidoDisplay = 0;
const int SegEncendidoLuz = 10;
const unsigned long tiempoMantenerEncendidoDisplay = SegEncendidoLuz * 1000;
const int minInicialDescanso = 5;
const int minInicialTrabajo = 25;
const int minInicialDescansoLargo = 30;
int minutos = minInicialTrabajo;
int segundos = 1;
int cicloActual = 1;
bool trabajando = true;
bool enPausa = false;
bool ledOn = false;

byte play[8] = {
    0b10000,
    0b11000,
    0b11100,
    0b11110,
    0b11110,
    0b11100,
    0b11000,
    0b10000,
};

byte pausa[8] = {
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
};

void setup()
{
  pinMode(restartBtn, INPUT);
  digitalWrite(restartBtn, LOW);

  pinMode(pausaBtn, INPUT);
  digitalWrite(pausaBtn, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(luzDisplayPin, OUTPUT);
  digitalWrite(luzDisplayPin, HIGH);

  pinMode(enciendeLuzBtn, INPUT);
  digitalWrite(enciendeLuzBtn, HIGH);

  lcd.begin(16, 2);

  lcd.createChar(0, play);
  lcd.createChar(1, pausa);

  tiempoInicial = millis();
}

void loop()
{
  tiempoActual = millis();
  tiempoTranscurrido = tiempoActual - tiempoInicial;

  // Boton de luz display
  if (digitalRead(enciendeLuzBtn) == HIGH)
  {
    delay(50);
    encenderLuzDisplay();    
  }

  // Boton de reseteo
  if (digitalRead(restartBtn) == HIGH)
  {
    delay(50);
    encenderLuzDisplay();
    while(digitalRead(restartBtn) == HIGH){};
    minutos = minInicialTrabajo;
    segundos = 1;
    trabajando = true;
    cicloActual = 1;
    lcd.clear();
  }

  // Boton de Play/Pausa
  if (digitalRead(pausaBtn) == HIGH)
  {
    delay(50);
    encenderLuzDisplay();
    while(digitalRead(pausaBtn) == HIGH){};
    enPausa = !enPausa;
  }

  // Control de tiempo de encendido de luz display
  if (digitalRead(luzDisplayPin) == HIGH && millis() - momentoEncendidoDisplay > tiempoMantenerEncendidoDisplay)
  {
    digitalWrite(luzDisplayPin, LOW);
  }

  // Inscripcion simbolo play/pausa
  if (enPausa)
  {
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    ledIntermitente(1);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
  }

  // Transcurrido 1 seg se ejecuta el bloque de codigo
  if (!enPausa && tiempoTranscurrido >= 1000)
  {

    // resta un segundo
    segundos--;

    // resta un minuto - reinicia seg
    if (segundos == -1)
    {
      segundos = 59;
      minutos--;
    }

    // Impresion del tiempo por pantalla
    lcd.setCursor(5, 0);
    if (minutos < 10)
    {
      lcd.print("0");
    }
    lcd.print(minutos);

    lcd.print(":");

    lcd.setCursor(8, 0);
    if (segundos < 10)
    {
      lcd.print("0");
    }
    lcd.print(segundos);

    lcd.setCursor(14, 0);
    lcd.print(cicloActual);

    // Impresion del modo: trabajo/descanso
    if (trabajando == true)
    {
      lcd.setCursor(3, 1);
      lcd.print("TRABAJANDO");
    }
    else
    {
      lcd.setCursor(4, 1);
      lcd.print("DESCANSO");
    }

    // Condicion de cambio de modo [Trabajo / Descanso]
    if (minutos == 0 && segundos == 0)
    {
      if (trabajando)
      {
        if (cicloActual % 4 == 0)
        {
          minutos = minInicialDescansoLargo;
        }
        else
        {
          minutos = minInicialDescanso;
        }
      }
      else
      {
        cicloActual++;
        minutos = minInicialTrabajo;
      }

      trabajando = !trabajando;
      encenderLuzDisplay();
      alarma();
      lcd.clear();
    }

    tiempoInicial = millis();
  }
}

// Encendido de luz de display
void encenderLuzDisplay()
{
  digitalWrite(luzDisplayPin, HIGH);
  momentoEncendidoDisplay = millis();
}

// Intermitencia del Led
void ledIntermitente(int repeticiones)
{
  for (int i = 0; i < (repeticiones); i++)
  {
    if (!ledOn)
    {
      digitalWrite(ledPin, HIGH);
    }
    delay(400);
    digitalWrite(ledPin, LOW);
    ledOn = !ledOn;
  }
}

// Sonido 8bit de alarma [Mario Bros]
void alarma()
{
  ledIntermitente(4);

  tone(piezoPin, 130, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 261, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 110, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 220, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 116, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 233, 192.857142857);
  delay(214.285714286);

  ledIntermitente(4);

  tone(piezoPin, 130, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 261, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 110, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 220, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 116, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 233, 192.857142857);
  delay(214.285714286);

  ledIntermitente(4);

  tone(piezoPin, 87, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 174, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 73, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 146, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 77, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 155, 192.857142857);
  delay(214.285714286);

  ledIntermitente(4);

  tone(piezoPin, 87, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 174, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 73, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 146, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 77, 192.857142857);
  delay(214.285714286);
  tone(piezoPin, 155, 192.857142857);
  delay(214.285714286);
}
