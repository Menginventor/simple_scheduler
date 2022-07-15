#include "simple_scheduler.h"
#define LED1_PIN 7
#define LED2_PIN 6
#define LED3_PIN 5
#define GREEN_LED_PIN 4
Task_list job_queue;


void setup()
{

  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // setInterval will run repeatly for every given time period (ms)
  job_queue.setInterval(blink_green, 1000);
  job_queue.setInterval(led1_on, 2000);
}

unsigned long timer = millis();
void loop()
{
  job_queue.update();
 
}
void led1_on(){
  digitalWrite(LED1_PIN, HIGH);
  job_queue.setTimeout(led1_off, 250); //setTimeout will run once after given time period (ms)
}
void led1_off(){
  digitalWrite(LED1_PIN, LOW);
  job_queue.setTimeout(led2_on, 250);//setTimeout will run once after given time period (ms)
}
void led2_on(){
  digitalWrite(LED2_PIN, HIGH);
  job_queue.setTimeout(led2_off, 250);//setTimeout will run once after given time period (ms)
}
void led2_off(){
  digitalWrite(LED2_PIN, LOW);
  job_queue.setTimeout(led3_on, 250);//setTimeout will run once after given time period (ms)
}

void led3_on(){
  digitalWrite(LED3_PIN, HIGH);
  job_queue.setTimeout(led3_off, 250);//setTimeout will run once after given time period (ms)
}
void led3_off(){
  digitalWrite(LED3_PIN, LOW);
}



void blink_green() {
  digitalWrite(GREEN_LED_PIN,HIGH);
  job_queue.setTimeout(blink_green_off, 500);
}

void blink_green_off() {
  digitalWrite(GREEN_LED_PIN,LOW);
}
