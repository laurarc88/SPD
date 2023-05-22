// C++ code
//

//Pines anodos
#define led_uno 4
#define led_dos 5
#define led_tres 6
#define led_cuatro 7

//Pines catodos
#define hora_decena A5
#define hora_unidad A4
#define minutos_decena A3
#define minutos_unidad A2

//Pulsadores
#define aumenta_minuto A0
#define disminuye_minuto A1

int minutos = 57; // Almacena minutos actuales
int hora = 13; // Almacena hora actual
unsigned long ultima_hora = 0; // Almacena la última actualización de la hora

//Almacena el valor de la columna decena/unidad de las horas/minutos
int columna_hora_decena = 0;
int columna_hora_unidad = 0;
int columna_minutos_decena = 0; 
int columna_minutos_unidad = 0;

void setup() 
{
  // Configuro pines como entradas o salidas
  pinMode(led_uno, OUTPUT);
  pinMode(led_dos, OUTPUT);
  pinMode(led_tres, OUTPUT);
  pinMode(led_cuatro, OUTPUT);
  
  pinMode(hora_decena, OUTPUT);
  pinMode(hora_unidad, OUTPUT);
  pinMode(minutos_decena, OUTPUT);
  pinMode(minutos_unidad, OUTPUT);
  
  pinMode(aumenta_minuto, INPUT_PULLUP);
  pinMode(disminuye_minuto, INPUT_PULLUP);
  
  Serial.begin(9600); 
}

void loop()
{
   unsigned long tiempo = millis(); // Tiempo actual en milisegundos
  
// Compruebo si pasó un minuto desde la última actualización de la hora para actualizar la hora e incrementar los minutos
  if (tiempo - ultima_hora >= 60000)
  {
    ultima_hora = tiempo; 
    minutos++; 
  }

  // Si se presionó el pulsador de aumentar minuto, llamo a la función que incrementa los minutos y muestra la hora actualizada
  if (digitalRead(aumenta_minuto) == LOW)
  {
    delay(150); 
    incrementar_minutos(); 
    mostrar_hora(minutos, hora); 
  }

  // Si se presionó el pulsador de disminuir minuto, llamo a la función que disminuye los minutos y muestra la hora actualizada
  if (digitalRead(disminuye_minuto) == LOW)
  {
    delay(150); 
    disminuir_minutos(); 
    mostrar_hora(minutos, hora); 
  }

  //Da los valores a las columnas correspondientes a decena/unidad hora/minuto
  columna_hora_decena = obtener_decena(hora); 
  columna_hora_unidad = obtener_unidad(hora); 
  columna_minutos_decena = obtener_decena(minutos); 
  columna_minutos_unidad = obtener_unidad(minutos); 
  
  //Prende/Apaga las columnas correspondientes a decena/unidad hora/minuto
  apagar_prender_columna(hora_decena, columna_hora_decena);
  apagar_prender_columna(hora_unidad, columna_hora_unidad);
  apagar_prender_columna(minutos_decena, columna_minutos_decena);
  apagar_prender_columna(minutos_unidad, columna_minutos_unidad); 
}

//Controlan se mantenga el formato 24hs
void incrementar_minutos()
{
  minutos++;
  if (minutos >= 60)
  {
    minutos = 0;
    incrementar_hora();
  }
}

void disminuir_minutos()
{
  minutos--;
  if (minutos < 0)
  {
    minutos = 59;
    disminuir_hora();
  }
}

void incrementar_hora()
{
  hora++;
  if (hora >= 24)
  {
    hora = 0;
  }
}

void disminuir_hora()
{
  hora--;
  if (hora < 0)
  {
    hora = 23;
  }
}

// Mostrar la hora en el monitor en serie
void mostrar_hora(int min, int hr)
{
  Serial.print("Hora: ");
  if (hr < 10)
  {
    Serial.print("0");
  }
  Serial.print(hr);
  Serial.print(":");
  if (min < 10)
  {
    Serial.print("0");
  }
  Serial.println(min);
}

// Encender o apagar los leds correspondientes a una columna
void apagar_prender_columna(int led, unsigned int numero)
{
  prender_led(numero);
  
  digitalWrite(led, LOW);
  
  delay(5);
  
  digitalWrite(led, HIGH); 
}

// Da la decena/unidad de un número
int obtener_decena(int numero)
{
  int decena = numero / 10;
  return decena;
}

int obtener_unidad(int numero)
{
  int decena = obtener_decena(numero);
  int unidad = numero - decena * 10;
  return unidad;
}

// Encender los LED correspondientes a un número
void prender_led(unsigned int numero)
{
  switch(numero)
  {
    case 0:
      digitalWrite(led_uno, LOW);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, LOW);
      break;
    case 1:
      digitalWrite(led_uno, HIGH);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, LOW);
      break;
    case 2:
      digitalWrite(led_uno, LOW);
      digitalWrite(led_dos, HIGH);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, LOW);
      break;
    case 3:
      digitalWrite(led_uno, HIGH);
      digitalWrite(led_dos, HIGH);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, LOW);
      break;
    case 4:
      digitalWrite(led_uno, LOW);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, HIGH);
      digitalWrite(led_cuatro, LOW);
      break;
    case 5:
      digitalWrite(led_uno, HIGH);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, HIGH);
      digitalWrite(led_cuatro, LOW);
      break;
    case 6:
      digitalWrite(led_uno, LOW);
      digitalWrite(led_dos, HIGH);
      digitalWrite(led_tres, HIGH);
      digitalWrite(led_cuatro, LOW);
      break;
    case 7:
      digitalWrite(led_uno, HIGH);
      digitalWrite(led_dos, HIGH);
      digitalWrite(led_tres, HIGH);
      digitalWrite(led_cuatro, LOW);
      break;
    case 8:
      digitalWrite(led_uno, LOW);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, HIGH);
      break;
    case 9:
      digitalWrite(led_uno, HIGH);
      digitalWrite(led_dos, LOW);
      digitalWrite(led_tres, LOW);
      digitalWrite(led_cuatro, HIGH);
      break;
  }
}
