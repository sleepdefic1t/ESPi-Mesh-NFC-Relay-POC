/*
  ****************************************
    Mesh_Pi_Node.ino
    sleepdeficit 11/2017
  ****************************************
*/


/* **************************** Configuration ***************************** */
/* ************** Mesh Config *** */
#include <painlessMesh.h>

#define   MESH_PREFIX     "meshxmeshx"
#define   MESH_PASSWORD   "meshxmeshx"
#define   MESH_PORT       5555

painlessMesh  mesh;

/* ****************************** */


/* ************ Button Config *** */
#define NFC_BUTTON  (14)
#define RELAY_BUTTON  (12)

int nfc_button_value = 0;
int relay_button_value = 0;

/* ******************************* */


/* **************** LED Config *** */
#define LED_RED  (0)
#define LED_BLUE  (2)
/* ******************************* */
/* *************************** /Configuration ***************************** */




/* ******************************** Setup ********************************* */
/* **************** Mesh-Setup *** */
void setupMesh()
{
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
}
/* ******************************* */


/* ***************** Pin-Setup *** */
void setupPins()
{
  pinMode(NFC_BUTTON, INPUT);
  pinMode(RELAY_BUTTON, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, HIGH);
}
/* ******************************* */
/* ******************************* /Setup ********************************* */




/* ******************************* Functions ******************************* */
/* ************* Mesh Callback *** */
void receivedCallback( uint32_t from, String &msg )
{
  if (msg.indexOf("/nfc/wasRequested/") != -1)
  {
    relay_button_value = 1;
   }
}
/* ******************************* */


/* **************** Poll Tasks *** */
void pollTasks()
{ 
  nfc_button_value = digitalRead(NFC_BUTTON);
  relay_button_value = digitalRead(RELAY_BUTTON);
  
  unsigned long now = millis();
  if ((now % 1000) == 0) // run every 1-second
  {
    Serial.print("\n pollTasks = ");
    Serial.print(now);
    checkNFC();
    checkRelay();
  }
}
/* ******************************** */


/* ****************** NFC-Check *** */
void checkNFC()
{
  nfc_button_value = digitalRead(NFC_BUTTON);   // read NFC_MESH_BUTTON 
  Serial.print("nfc: "); Serial.print(nfc_button_value);
  if (nfc_button_value != 0) { sendNFCRequest(); }
  else {
    digitalWrite(LED_RED, HIGH);
    delay(500);
    digitalWrite(LED_RED, LOW);
  }
}
/* ******************************* */


/* *************** Relay-Check *** */
void checkRelay()
{ 
  relay_button_value = digitalRead(RELAY_BUTTON);   // read RELAY_MESH_BUTTON
  Serial.print("\n relay: "); Serial.print(relay_button_value);  
  if (relay_button_value != 0) { sendRelayRequest(); }
  else {
    digitalWrite(LED_RED, HIGH);
    delay(500);
    digitalWrite(LED_RED, LOW);
  }
}
/* ******************************* */


/* ********** Send NFC Request *** */
void sendNFCRequest()
{
  String msg = "/nfc/request/";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );

  nfc_button_value = 0;
  pinMode(NFC_BUTTON, OUTPUT);  // sets the digital pin 4 as output
  digitalWrite(NFC_BUTTON, 0);
  pinMode(NFC_BUTTON, INPUT);  // sets the digital pin 4 as input
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  digitalWrite(LED_BLUE, HIGH); 
}
/* ******************************* */


/* ******** Send Relay Request *** */
void sendRelayRequest()
{
  String msg = "/relay/toggle/";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );

  relay_button_value = 0; 
  pinMode(RELAY_BUTTON, OUTPUT);  // sets the digital pin 4 as input
  digitalWrite(RELAY_BUTTON, 0);
  pinMode(RELAY_BUTTON, INPUT);  // sets the digital pin 4 as input
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  digitalWrite(LED_BLUE, HIGH);
}
/* ****************************** */
/* ******************************* /Functions ******************************* */


/* ******************************* Board Setup ****************************** */
void setup()
{
  Serial.begin(115200);
  setupMesh();
  setupPins();
}
/* ****************************** /Board Setup ****************************** */


/* ********************************** Loop ********************************** */
void loop()
{
  mesh.update();
  pollTasks();
}
/* ********************************* /Loop ********************************** */
