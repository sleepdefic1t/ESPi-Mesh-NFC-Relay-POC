/*
  ****************************************
    Mesh_Relay_Node.ino
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


/* *************** Pin Config *** */
#define RELAY_SIG  (15)
/* ****************************** */


/* ****************** Counter *** */
unsigned long last = 0; // milli counter
/* ****************************** */
/* **************************** /Configuration ***************************** */



/* ***************************** Library Setup ***************************** */
/* **************** Mesh Setup *** */
void setupMesh()
{
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
}
/* ******************************* */

/* ***************** Pin Setup *** */
void setupPins()
{
  pinMode(RELAY_SIG, OUTPUT); // prepare GPIO
  digitalWrite(RELAY_SIG, LOW);
}
/* ******************************* */
/* **************************** /Library Setup ***************************** */



/* ******************************* Functions ******************************* */
/* ******** Receive Callback *** */
void receivedCallback( uint32_t from, String &msg )
{
  if (msg.indexOf("/relay/toggle") != -1)
  {
    Serial.printf("toggled");
    digitalWrite(RELAY_SIG, HIGH);
    delay(500);
    digitalWrite(RELAY_SIG, LOW);
  }
  else
  {
    Serial.printf("echo-relay-Node: Received from %u msg=%s\n", from, msg.c_str());
    mesh.sendSingle(from, msg);
  }
}
/* ******************************* */
/* ****************************** /Functions ******************************* */



/* ******************************* Board Setup ****************************** */
void setup() {
  Serial.begin(115200);
  setupMesh();
  setupPins();
}
/* ****************************** /Board Setup ****************************** */



/* ********************************** Loop ********************************** */
void loop() {
  mesh.update();
}
/* ********************************* /Loop ********************************** */
