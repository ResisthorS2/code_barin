/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Février 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 9600        // Fréquence de transmission sérielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message

int ledState = 0;
int potValue = 0;

const int pinLED = 37;
const int pinPOT = A0;
const int pinBoutonQ = 51;
const int pinBoutonW = 29;
const int pinBoutonA = 27;
const int pinBoutonS = 23;
const int pinBoutonD = 25;

const int ledCount = 10;   // the number of LEDs in the bar graph

int ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};  // an array of pin numbers to which LEDs are attached


/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup() {
  Serial.begin(BAUD);               // Initialisation de la communication sérielle
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, ledState);
  pinMode(pinBoutonQ, INPUT);
  pinMode(pinBoutonW, INPUT);
  pinMode(pinBoutonA, INPUT);
  pinMode(pinBoutonS, INPUT);
  pinMode(pinBoutonD, INPUT);

  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

/* Boucle principale (infinie) */
void loop() {
  StaticJsonDocument<500> doc;
  if(digitalRead(pinBoutonQ) == LOW)
  {
    while(digitalRead(pinBoutonQ) == LOW);
    doc["bouton"] = 'Q';
    serializeJson(doc, Serial);
    Serial.println();
  }
  else if(digitalRead(pinBoutonW) == LOW)
  {
    while(digitalRead(pinBoutonW) == LOW);
    doc["bouton"] = 'W';
    serializeJson(doc, Serial);
    Serial.println();
  }
  else if(digitalRead(pinBoutonA) == LOW)
  {
    while(digitalRead(pinBoutonA) == LOW);
    doc["bouton"] = 'A';
    serializeJson(doc, Serial);
    Serial.println();
  }
  else if(digitalRead(pinBoutonS) == LOW)
  {
    while(digitalRead(pinBoutonS) == LOW);
    doc["bouton"] = 'S';
    serializeJson(doc, Serial);
    Serial.println();
  }
  else if(digitalRead(pinBoutonD) == LOW)
  {
    while(digitalRead(pinBoutonD) == LOW);
    doc["bouton"] = 'D';
    serializeJson(doc, Serial);
    Serial.println();
  }
  delay(10);

  /*if(shouldRead_){
    readMsg();
    sendMsg();
  }

  potValue = analogRead(pinPOT);
  //Serial.println(potValue);          // debug
  delay(10);  // délai de 10 ms

  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(potValue, 0, 1023, 0, ledCount);

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }*/
}

/*---------------------------Définition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }

/*---------------------------Définition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  // Éléments du message
  doc["time"] = millis();
  doc["analog"] = potValue;

  // Sérialisation
  serializeJson(doc, Serial);

  // Envoi
  Serial.println();
  shouldSend_ = false;
}

/*---------------------------Définition de fonctions ------------------------
Fonction de réception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg(){
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Sériel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message
  parse_msg = doc["led"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED,doc["led"].as<bool>());
  }
}