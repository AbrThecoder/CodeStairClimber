//@Author:Codabrainy

#include <Arduino.h>
#include "SoftwareSerial.h"

int DPins[] = {3,4,5,6,8,9,10,11,12,13};
int APins[] = {A0,A1,A2,A3,A5};
int mot1=5, mot2=6, mot3=9, mot4=10, mot56=3;
SoftwareSerial bluetooth(1, 0);
char etat = 'A';

const int echoD = 7;
const int trigD = 8;

const int echoG = 2;
const int trigG = 4; 

#define pinCNYD A1;
#define pinCNYG A2;


void setup() {
bluetooth.begin(9600);
delay(25);
pinMode(A4,OUTPUT);
while(etat!='M'){
	delay(25);
	if(bluetooth.available()){
		etat = bluetooth.read();	
	}
	if (analogRead(A5)<50)
	{
		etat='M';
	}
}
for (int i = 0; i < sizeof(DPins);i++)
{
	pinMode(DPins[i],OUTPUT);
}
for(int i=0; i < sizeof(APins); i++)
{
	pinMode(APins[i],INPUT);
}
pinMode(2,INPUT);
pinMode(7,INPUT);
}

void loop() {
	
}

void AvanceA(int moteur, int vitesse){
	switch (moteur) {
		case 1:analogWrite(mot1,vitesse);break;
		case 2:analogWrite(mot2,vitesse);break;
		case 3:analogWrite(mot3,vitesse);break;
		case 4:analogWrite(mot4,vitesse);break;
		break;
		default:
		break;
	}
}

void ArretA(int moteur){
	switch (moteur) {
		case 1:analogWrite(mot1,0);break;
		case 2:analogWrite(mot2,0);break;
		case 3:analogWrite(mot3,0);break;
		case 4:analogWrite(mot4,0);break;
		break;
		default:
		break;
	}
}

void AvanceB(int vitesse){
	digitalWrite(A3,HIGH);
	digitalWrite(12,LOW);
	analogWrite(mot56,vitesse);
}

void ReculeB(int vitesse){
	digitalWrite(A3,LOW);
	digitalWrite(12,HIGH);
	analogWrite(mot56,vitesse);
}
void ArretB(int vitesse){
	digitalWrite(A3,LOW);
	digitalWrite(12,LOW);
}

long microsecondsToCentimeters(long microseconds)
{
	return microseconds / 29 / 2;
}
//1 droite, 2 gauche. 
int Lecture_US(int US) 
{
	if (US==1)
	{
		digitalWrite(trigD, LOW);
		delayMicroseconds(2);
		digitalWrite(trigD, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigD, LOW);
		int duration = pulseIn(echoD, HIGH);
		int distance = microsecondsToCentimeters(duration);
		return distance;
	}
	else if (US==2)
	{
		digitalWrite(trigG, LOW);
		delayMicroseconds(2);
		digitalWrite(trigG, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigG, LOW);
		int duration = pulseIn(echoG, HIGH);
		int distance = microsecondsToCentimeters(duration);
		return distance;
	}
}
bool Seuil_US(int US, int seuil)
{
	return Lecture_US(1) > seuil;
}

int Lecture_CNY(int pin)
{
	if(pin == 1){
		return analogRead(A1);
	}
	else if(pin == 2){
		return analogRead(A2);
	}
}
bool Seuil_CNY(int pin, int seuil)
{
	return Lecture_CNY(pin) < seuil;
}
	
