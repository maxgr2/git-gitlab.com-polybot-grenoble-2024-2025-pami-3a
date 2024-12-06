#include <Arduino.h>
#include "Servo.h"


//                 Initialisation des variable pour manipuler les servos moteurs
Servo droite; // servo à droite
Servo gauche; // servo à gauche
int valeur_avance=5;



//---------------Initialisation de variables pour le suiveur de ligne

#define SEUIL 200
const int Pin1_detecteur_ligne = PA0; // PIN capteur de ligne
const int Pin2_detecteur_ligne = PA1; // PIN capteur de ligne
int detecteur_gauche;                 // détecteur du suiveur de ligne
int detecteur_droite;                 //détecteur du suiveur de ligne



//------------------------Initialisation des variables capteur ultra song

#define DISTANCE_SEUIL 15      // distance ou est instauré un arrêt d'urgence
const int trigPin = PB7;
const int echoPin = PB6;

float temps_onde , distance_cm;


void setup()
{
  
  droite.attach(PA8);          // attache le servo au pin 8
  gauche.attach(PA11);         // attache le servo au pin 11
  droite.writeMicroseconds(1500); //initialisation du servo pour eviter qu'il touen en continue
  gauche.writeMicroseconds(1500);
  Serial.begin(9600);         // est ici pour l'ffichage sur terminal A_ENLEVER
  pinMode(trigPin, OUTPUT);    // configuration des pins capteur ultrason
  pinMode(echoPin, INPUT);
   
}


int evitement_obstacle();
int direction();

void loop()
{
//if (evitement_obstacle() != 1)
  {
    //distance = evitement_obstacle();
    int dir = direction();

    Serial.print(" detecteur droit : ");
    Serial.print(detecteur_droite);
    Serial.print(" detecteur gauche : ");
    Serial.print(detecteur_gauche);
    Serial.print(" distance:");
    Serial.println(distance_cm);
    Serial.print(" dir : ");
    Serial.println(dir);
    if (dir == 1)
    { // ligne pour aller à droite
      droite.write(0);
      gauche.write(90);
      delay(10);
    }
    if (dir == 2)
    { // pour aller à gauche
      gauche.write(0);
      droite.write(90);
      delay(10);
    }
    if (dir == 4)
    {
      droite.write(0);
      gauche.write(180);
    }
    if (dir == 3) // censé être le cas perpendiculaire à voir comment on le gère rajoute t'on un tof pour pas gerer cette exption ???
    {
      droite.write(0);
      gauche.write(180);
    }
    //delay(2000);
  }

gauche.write(0);
droite.write(0);
}

//--------------------------Fonction qui utlise le cpateur de couleur (suiveur de ligne)
int direction()
{
  detecteur_gauche = Pin1_detecteur_ligne;
  detecteur_droite = (Pin2_detecteur_ligne);

  if (detecteur_droite < SEUIL && detecteur_gauche < SEUIL)
  { // aller tous droit
    return 3;
  }
  else
  {
    if (detecteur_gauche > SEUIL && detecteur_droite > SEUIL)
    {
      return 4;
    }
    if (detecteur_gauche > SEUIL)
    {
      return 2;
    }
    if (detecteur_droite > SEUIL)
    {
      return 1;
    }
    else
    {
      return 5;
    }
  }
}

int evitement_obstacle()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // mesurer la duree d'impulsion dans la broche d'arduino
  temps_onde = pulseIn(echoPin, HIGH);

  // calculer distance (cm)
  distance_cm = 0.017 * temps_onde; // temps_onde : temps de parcours de l'onde 

  // afficher la valeur de la distance
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

 
  if (distance_cm <= DISTANCE_SEUIL)
  {
    return distance_cm;
  }
  else
  {
    return distance_cm;
  }
}