/*
  ****************************************
    Mesh_NFC_Node.ino
    sleepdeficit 11/2017
  ****************************************
*/

/* **************************** Configuration ***************************** */
/* ************** Wire Config *** */
#include <SPI.h>
#include <PN532_SPI.h>

PN532_SPI pn532spi(SPI, 5);

/* ****************************** */


/* ************** Mesh Config *** */
#include <painlessMesh.h>

#define   MESH_PREFIX     "meshxmeshx"
#define   MESH_PASSWORD   "meshxmeshx"
#define   MESH_PORT       5555

painlessMesh  mesh;

/* ****************************** */


/* *************** NFC Config *** */
#include <NdefMessage.h>
#include <emulatetag.h>

EmulateTag nfc(pn532spi);

uint8_t ndefBuf[120];
NdefMessage message;
int messageSize;

uint8_t uid[3] = { 0x12, 0x34, 0x56 };

const char * uriRecord = "{'recipientID': 'Axxxx', 'amount': '100000000' }";

bool nfcShouldEmulate = false;
bool nfcShouldConfirm = false;
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
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.onReceive(&receivedCallback);
}
/* ******************************* */

/* **************** NFC Setup ***  */
void setupNFC()
{ Serial.println("\n ------- Setup NFC --------");
  message = NdefMessage();
  message.addUriRecord(uriRecord);
  messageSize = message.getEncodedSize();
  if (messageSize > sizeof(ndefBuf))
  { Serial.println("ndefBuf is too small"); while (1) {} }
  Serial.print("\n Ndef encoded message size: "); Serial.println(messageSize);
  message.encode(ndefBuf);
  nfc.setNdefFile(ndefBuf, messageSize);
  nfc.setUid(uid);
  nfc.init();
}
/* ******************************* */
/* **************************** /Library Setup ***************************** */



/* ******************************* Functions ******************************* */

/* *************** Mesh Functions *** */
/* ******** Receive Callback *** */
void receivedCallback( uint32_t from, String &msg )
{
  if ((msg.indexOf("/nfc/request") != -1) && (from != mesh.getNodeId()))
  { Serial.print("\n *** receivedCallback /nfc/request *** \n");

    nfcShouldEmulate = true;
  }
  else if (msg.indexOf("/nfc/wasRequested/") != -1)
  {
    nfcShouldConfirm = false;
  }
  else
  {
    Serial.printf("echo-nfc-Node: Received from %u msg=%s\n", from, msg.c_str());
    mesh.sendSingle(from, msg);
  }
}
/* ******************************* */

/* *************** Update Mesh *** */
void updateMeshForNFC()
{ 
  for (int i = 0; i < 3; i++)
  {
    if (millis() % 100 == 0)
    {
      mesh.update(); // stack several every pass for NFC emulation
    }
  }
}
/* ******************************* */
/* ***************** /Mesh Functions *** */


/* ******************* NFC Functions *** */
/* ***************** Check NFC *** */
void checkNFC()
{ 
  if (nfcShouldEmulate == true)
  { Serial.print("\n *** nfcShouldEmulate == true *** \n");
  
    nfc.emulate(0, updateMeshForNFC);
    nfcScheduleStop();
  }
  else { mesh.update(); }

  if (nfcShouldConfirm == true)
  { Serial.println("\n *** send WasRequested msg *** \n");
  
    String msg2 = "/nfc/wasRequested/";
    Serial.printf(msg2.c_str());
    mesh.sendBroadcast(msg2);
    nfcShouldConfirm = false;
  }
}
/* ******************************* */

/* ******** Stop Emulating NFC *** */
void nfcScheduleStop()
{
    if (last == 0) { last = millis(); }
    else if (millis() - last > 5000)
    {
      Serial.println("\n ------- Stop Emulating NFC --------");
      nfcShouldConfirm = true;
      nfcShouldEmulate = false;
      last = 0;
    }
}
/* ******************************* */
/* ****************** /NFC Functions *** */
/* ****************************** /Functions ******************************* */



/* ******************************* Board Setup ****************************** */
void setup()
{
  Serial.begin(115200);
  setupMesh();
  setupNFC();
}
/* ****************************** /Board Setup ****************************** */



/* ********************************** Loop ********************************** */
void loop()
{
  checkNFC();
  mesh.update(); 
}
/* ********************************* /Loop ********************************** */
