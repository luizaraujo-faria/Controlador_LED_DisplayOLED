#include <Wire.h>
// BIBLIOTECAS DO DISPLAY OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// CONFIGURAÇÕES DA TELA
#define LARGURA_TELA 128
#define ALTURA_TELA 64

// LED E BUZZER
const int ledVerde = 2;
const int ledAzul = 3;
const int ledVermelho = 4;
const int buzzer = 5;

// APLICA CONFIGURAÇÕES NA TELA
Adafruit_SSD1306 tela(
  LARGURA_TELA,
  ALTURA_TELA,
  &Wire,
  -1
);

// RECEBE O SINAL ENVIADO
char sinal;

void setup() {
  Serial.begin(9600); // INICIA O MONITOR SERIAL

  Serial.println("Sistema iniciado!");
  Serial.println("Digite '0' para apagar o led");
  Serial.println("Digite '1' para acender o led");
  Serial.println("Digite '2' para piscar o led");

  // Serial.println("\nDigite 'm-<Mensagem>' para enviar uma mensagem ao display");

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!tela.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {
      // Para aqui se o display não for inicializado.
    }
  }
  
  // LIMPA TELA DO DISPLAY
  tela.clearDisplay();

  tela.setTextSize(1);
  tela.setTextColor(SSD1306_WHITE);
  
  // DEFINE A POSIÇÃO PARA ESCREVER NO OLED
  tela.setCursor(0, 0);
  // ESCREVE NO OLED
  tela.println("Ola, Shaolin!");

  tela.setCursor(0, 16);
  tela.println("Sistema com led");

  tela.display();
  inativo();
}

void loop() {
  
  // VERIFICA SE O TERMINAL RECEBEU ALGO
  if (Serial.available() > 0) {
    
    // ATRIBUI A LEITURA DO SERIAL À VARIAVEL
    char recebido = Serial.read(); 

    // EVITA CAPURAR MENSAGEM FALSA
    if (recebido != '\n' && recebido != '\r') {
      sinal = recebido;

      Serial.print("Voce enviou: ");
      Serial.println(sinal);

      atualizarDisplay(sinal);
    }
  }

  if(sinal == '1'){
    apagarLeds();
    acenderLed();
  }
  
  if(sinal == '2'){
    apagarLeds();
    piscarLed();
  }

  if(sinal == '0'){
    apagarLeds();
    inativo();
  }
}

void piscarLed(){
  // ACENDE O LED
  digitalWrite(ledVermelho, HIGH);
  // APITA O BUZZER
  tone(buzzer, 3200);
  delay(500);
  // APAGA O LED
  digitalWrite(ledVermelho, LOW);
  // DESLIGA O BUZZER
  noTone(buzzer);
  delay(500);
}

void acenderLed(){
  digitalWrite(ledVerde, HIGH);
  tone(buzzer, 3200);
  delay(1000);
  noTone(buzzer);
  delay(1000);
}

void inativo(){
  digitalWrite(ledAzul, HIGH);
  noTone(buzzer);
}

void apagarLeds(){
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
}

void atualizarDisplay(char sinal){
  tela.clearDisplay();

  tela.setCursor(0, 0);
  tela.println("SISTEMA COM LED");

  tela.setCursor(0, 16);
  tela.print("Sinal enviado: ");
  tela.println(sinal);

  tela.display();
}