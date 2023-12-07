//#include "HID.h"
#include "Adafruit_TinyUSB.h"

//#define SSS
#define DEADZONE 1
#define ADCDIV 16
#define ADCRES 12
#define ADCMAX (2032/ADCDIV) //+-127
#define ADCMIN 0

#define PTHRESH 8
#define PTHRESHR 3
#define THRESH 40
#define THRESHR 30
#define ZTHRESH 40
#define ZTHRESHR 30

#define DOF 6

const int pb1 = 15;
const int pb2 = 14;
const int pb3 = 8;
bool activeState = false;

int x1origin;
int y1origin;
int x2origin;
int y2origin;

uint8_t btnn[3];


static const uint8_t desc_hid_report[] PROGMEM = {
  0x05, 0x01,           //  Usage Page (Generic Desktop)
  0x09, 0x08,           //  0x08: Usage (Multi-Axis)
  0xa1, 0x01,           //  Collection (Application)
  0xa1, 0x00,           // Collection (Physical)
  0x85, 0x01,           //  Report ID
  0x16, 0x00, 0x80,     //logical minimum (-500)
  0x26, 0xff, 0x7f,     //logical maximum (500)
  0x36, 0x00, 0x80,     //Physical Minimum (-32768)
  0x46, 0xff, 0x7f,     //Physical Maximum (32767)
  0x09, 0x30,           //    Usage (X)
  0x09, 0x31,           //    Usage (Y)
  0x09, 0x32,           //    Usage (Z)
  0x75, 0x10,           //    Report Size (16)
  0x95, 0x03,           //    Report Count (3)
  0x81, 0x02,           //    Input (variable,absolute)
  0xC0,                 //  End Collection
  0xa1, 0x00,           // Collection (Physical)
  0x85, 0x02,           //  Report ID
  0x16, 0x00, 0x80,     //logical minimum (-500)
  0x26, 0xff, 0x7f,     //logical maximum (500)
  0x36, 0x00, 0x80,     //Physical Minimum (-32768)
  0x46, 0xff, 0x7f,     //Physical Maximum (32767)
  0x09, 0x33,           //    Usage (RX)
  0x09, 0x34,           //    Usage (RY)
  0x09, 0x35,           //    Usage (RZ)
  0x75, 0x10,           //    Report Size (16)
  0x95, 0x03,           //    Report Count (3)
  0x81, 0x02,           //    Input (variable,absolute)
  0xC0,                 //  End Collection
/* 
  0xa1, 0x00,           // Collection (Physical)
  0x85, 0x03,           //  Report ID
  0x15, 0x00,           //   Logical Minimum (0)
  0x25, 0x01,           //    Logical Maximum (1)
  0x75, 0x01,           //    Report Size (1)
  0x95, 32,             //    Report Count (24)
  0x05, 0x09,           //    Usage Page (Button)
  0x19, 1,              //    Usage Minimum (Button #1)
  0x29, 32,             //    Usage Maximum (Button #24)
  0x81, 0x02,           //    Input (variable,absolute)
  0xC0,
*/
  0xC0,
  //TUD_HID_REPORT_DESC_KEYBOARD(0x04)
0x05, 0x01,                         // Usage Page (Generic Desktop)
0x09, 0x06,                         // Usage (Keyboard)
0xA1, 0x01,                         // Collection (Application)
0x85, 0x03,           //  Report ID
//0x85, 0x04,           //  Report ID
0x05, 0x07,                         //     Usage Page (Key Codes)
0x19, 0xe0,                         //     Usage Minimum (224)
0x29, 0xe7,                         //     Usage Maximum (231)
0x15, 0x00,                         //     Logical Minimum (0)
0x25, 0x01,                         //     Logical Maximum (1)
0x75, 0x01,                         //     Report Size (1)
0x95, 0x08,                         //     Report Count (8)
0x81, 0x02,                         //     Input (Data, Variable, Absolute)

0x95, 0x01,                         //     Report Count (1)
0x75, 0x08,                         //     Report Size (8)
0x81, 0x01,                         //     Input (Constant) reserved byte(1)

0x95, 0x05,                         //     Report Count (5)
0x75, 0x01,                         //     Report Size (1)
0x05, 0x08,                         //     Usage Page (Page# for LEDs)
0x19, 0x01,                         //     Usage Minimum (1)
0x29, 0x05,                         //     Usage Maximum (5)
0x91, 0x02,                         //     Output (Data, Variable, Absolute), Led report
0x95, 0x01,                         //     Report Count (1)
0x75, 0x03,                         //     Report Size (3)
0x91, 0x01,                         //     Output (Data, Variable, Absolute), Led report padding

0x95, 0x06,                         //     Report Count (6)
0x75, 0x08,                         //     Report Size (8)
0x15, 0x00,                         //     Logical Minimum (0)
0x25, 0x65,                         //     Logical Maximum (101)
0x05, 0x07,                         //     Usage Page (Key codes)
0x19, 0x00,                         //     Usage Minimum (0)
0x29, 0x65,                         //     Usage Maximum (101)
0x81, 0x00,                         //     Input (Data, Array) Key array(6 bytes)


0x09, 0x05,                         //     Usage (Vendor Defined)
0x15, 0x00,                         //     Logical Minimum (0)
0x26, 0xFF, 0x00,                   //     Logical Maximum (255)
0x75, 0x08,                         //     Report Count (2)
0x95, 0x02,                         //     Report Size (8 bit)
0xB1, 0x02,                         //     Feature (Data, Variable, Absolute)

0xC0,                                // End Collection (Application)


    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x04,           //  Report ID
    0x09, 0x01,                    //   USAGE (Pointer)
    0xA1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM
    0x29, 0x03,                    //     USAGE_MAXIMUM
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Const,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7F,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xC0,                          //   END_COLLECTION
    0xC0,                          // END COLLECTION


};
 

Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 4, false);

void setup() {

  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ) delay(1);

  pinMode(pb1, INPUT_PULLUP);
  pinMode(pb2, INPUT_PULLUP);
  pinMode(pb3, INPUT_PULLUP);

  analogReadResolution(ADCRES);
  delay(10);  
  y1origin = analogRead(A0); //y1 rot 
  x1origin = analogRead(A1); //x1 rot 
  y2origin = analogRead(A2); //y2 pan
  x2origin = analogRead(A3); //x2 pan

  //static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  //HID().AppendDescriptor(&node);
  //delay(300);
  //for (int i = 0; i < DOF; i++) {
  //  origin[i] = analogRead(port[i]);
  //}
#ifdef SSS
  Serial.begin(9600);
  Serial.println("HID Composite test\n");
#endif
}
 
void send_command(int16_t x, int16_t y, int16_t z, int16_t rx, int16_t ry, int16_t rz) {

  while(!usb_hid.ready());
  uint8_t trans[6] = { x & 0xFF, x >> 8, y & 0xFF, y >> 8, z & 0xFF, z >> 8 };
  usb_hid.sendReport(1,trans, sizeof(trans));
  //HID().SendReport(1, trans, 6);
  while(!usb_hid.ready());
  uint8_t rot[6] = { rx & 0xFF, rx >> 8, ry & 0xFF, ry >> 8, rz & 0xFF, rz >> 8 };
  usb_hid.sendReport(2,rot, sizeof(rot));
  //HID().SendReport(2, rot, 6);
}
/*
void send_btn(){
  while(!usb_hid.ready());
  usb_hid.sendReport(3,btnn, sizeof(btnn));
}
*/
void send_btn(){
  uint8_t keycode[6] = { 0 };
  keycode[0] = HID_KEY_A;
  while(!usb_hid.ready());
  //usb_hid.sendReport(3,btnn, sizeof(btnn));
  usb_hid.keyboardReport(3, 0, keycode);
}
 
void loop() {
  //int sv[DOF]; // sensor value
  int mv[DOF]; // motion vector
  //int moveFlag = false;

  uint8_t trans[]= {0,0,0,0,0,0};
  uint8_t rot[]= {0,0,0,0,0,0};
  static uint8_t ad;
  static bool j1HoldP;
  static bool j2HoldP;

  bool btn1_pressed = (digitalRead(pb1) == activeState);
  bool btn2_pressed = (digitalRead(pb2) == activeState);
  bool btn3_pressed = (digitalRead(pb3) == activeState);
  static bool has_key = false;

  int x1pos = (analogRead(A1)-x1origin)/ADCDIV; //rot //右正
  int y1pos = (analogRead(A0)-y1origin)/ADCDIV; //rot //上正
  int x2pos = (analogRead(A3)-x2origin)/ADCDIV; //pan //右正
  int y2pos = (analogRead(A2)-y2origin)/ADCDIV; //pan //下正

#ifdef SSS
  Serial.println("x1");
  Serial.println(x1pos);
  Serial.println(y1pos);
  Serial.println(x2pos);
  Serial.println(y2pos);
#endif

  if(abs(x1pos)< DEADZONE){x1pos=0;}
  if(abs(y1pos)< DEADZONE){y1pos=0;}
  if(abs(x2pos)< DEADZONE){x2pos=0;}
  if(abs(y2pos)< DEADZONE){y2pos=0;}
#if 0
  if(abs(x1pos)>=PTHRESH || abs(y1pos)>=PTHRESH){
    j1HoldP = true;
  }else if(abs(x1pos)<PTHRESHR && abs(y1pos)<PTHRESHR){
    j1HoldP = false;
  }
  if(abs(x2pos)>=PTHRESH || abs(y2pos)>=PTHRESH){
    j2HoldP = true;
  }else if(abs(x2pos)<PTHRESHR && abs(y2pos)<PTHRESHR){
    j2HoldP = false;
  }
#else
  uint16_t x1poss= abs(x1pos)*abs(x1pos);
  uint16_t y1poss= abs(y1pos)*abs(y1pos);
  uint16_t x2poss= abs(x2pos)*abs(x2pos);
  uint16_t y2poss= abs(y2pos)*abs(y2pos);
  if(x1poss+y1poss >= PTHRESH*PTHRESH){
    j1HoldP = true;
  }else if(x1poss+y1poss < PTHRESHR*PTHRESHR){
    j1HoldP = false;
  }
  if(x2poss+y2poss >= PTHRESH*PTHRESH){
    j2HoldP = true;
  }else if(x2poss+y2poss < PTHRESHR*PTHRESHR){
    j2HoldP = false;
  }

#endif

  if(j1HoldP && j2HoldP){
    mv[0] = x1pos;  // x
    mv[1] = 0;      // y
    mv[2] = -y1pos;  // z

    mv[3] = 0;  // rz
    mv[4] = 0;  // ry
    mv[5] = 0;  // rx

  }else{

    if(abs(y2pos)>=abs(x2pos)){
      x2pos = 0;
    }else{
      y2pos = 0;
    }

    mv[0] = 0;  // x
    mv[1] = y2pos;  // y zoom
    mv[2] = 0;  // z

    mv[3] = -y1pos;  // rz
    mv[4] = -x2pos;  // ry
    mv[5] = -x1pos;  // rx
  }


  btnn[0]=0x03;
  btnn[1]=0;
  btnn[2]=0;

  if(btn1_pressed){
    btnn[1]=btnn[1]|0x03;
    //btnn[2]=btnn[2]|0x80;
#ifdef SSS
  Serial.println("btn1");
#endif
  }

  if(btn2_pressed){
    btnn[1]=btnn[1]|0x04;
    //btnn[2]=btnn[2]|0x02;
#ifdef SSS
  Serial.println("btn2");
#endif
  }

  if(btn3_pressed){
    btnn[1]=btnn[1]|0x01;
    //btnn[2]=btnn[2]|0x01;
#ifdef SSS
  Serial.println("btn3");
#endif
    send_btn();
    has_key = true;
  }else if(has_key){
    while(!usb_hid.ready());
    usb_hid.keyboardRelease(3);
    has_key = false;
  }


/*
  mv[0] = x1pos;  // x
  mv[1] = 0;  // y
  mv[2] = y1pos;  // z
  mv[3] = -y2pos;  // rz
  mv[4] = 0;  // ry
  mv[5] = -x2pos;  // rx
*/

  send_command(mv[0], mv[1], mv[2], mv[3], mv[4], mv[5]);
  //send_btn();
}