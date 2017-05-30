#include <CapacitiveSensor.h>

#define range 300
long r1, r2, r3, r4, r5, r6;
int state8 = LOW, state9 = LOW, state10 = LOW, state11 = LOW;
//hand-regulating mode on true
bool thisGlobalMode = true;
//otherwise -> outoregulting (modules merge needed from here)
//for testing purposes in this module when thisGlobalMode = false
//it makes both brightness and colors on outstandingly high level

//######## SENSORS ########

//REGULATE BRIGHTNESS (1 PANEL)
//off
CapacitiveSensor   cs_1_1 = CapacitiveSensor(12, 2);
//50%
CapacitiveSensor   cs_1_2 = CapacitiveSensor(12, 3);
//100%
CapacitiveSensor   cs_1_3 = CapacitiveSensor(12, 4);

//REGULATE COLORS' INTENSITIES (2 PANEL)
//white (Wh)
CapacitiveSensor   cs_2_1 = CapacitiveSensor(12, 5);
//50/50 (Wh+Ye)
CapacitiveSensor   cs_2_2 = CapacitiveSensor(12, 6);
//yellow (Ye)
CapacitiveSensor   cs_2_3 = CapacitiveSensor(12, 7);

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  cs_1_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  r1 = range + cs_1_1.capacitiveSensor(30);
  r2 = range + cs_1_2.capacitiveSensor(30);
  r3 = range + cs_1_3.capacitiveSensor(30);
  r4 = range + cs_2_1.capacitiveSensor(30);
  r5 = range + cs_2_2.capacitiveSensor(30);
  r6 = range + cs_2_3.capacitiveSensor(30);
}

void loop()
{
  long _p1_k1 =  cs_1_1.capacitiveSensor(30);
  long _p1_k2 =  cs_1_2.capacitiveSensor(30);
  long _p1_k3 =  cs_1_3.capacitiveSensor(30);
  long _p2_k1 =  cs_2_1.capacitiveSensor(30);
  long _p2_k2 =  cs_2_2.capacitiveSensor(30);
  long _p2_k3 =  cs_2_3.capacitiveSensor(30);

  bool key1_1, key1_2, key1_3, key2_1, key2_2, key2_3;

  key1_1 = (_p1_k1 > r1);
  key1_2 = (_p1_k2 > r2);
  key1_3 = (_p1_k3 > r3);
  key2_1 = (_p2_k1 > r4);
  key2_2 = (_p2_k2 > r5);
  key2_3 = (_p2_k3 > r6);

#define p1Act (key1_1 || key1_2 || key1_3)
#define p2Act (key2_1 || key2_2 || key2_3)
  bool change = p1Act && p2Act;
  //if both panels are active we gonna change the mode!
  if (change) {
    thisGlobalMode = !thisGlobalMode;
  }

//  if (thisGlobalMode && !change) {
    if (key1_1) {
      state8 = LOW;
      state10 = LOW;
      state9 = LOW;
      state11 = LOW;
    } else if (key1_2) {
	if (state8 == LOW && state9 == LOW && state10 == LOW && state11 == LOW) {
          state8 = HIGH;
          state10 = HIGH;
      	} else {
      	  if (state10 == HIGH || state11 == HIGH) {
      	    state10 = HIGH;
      	    state11 = LOW;
      	  }
      	  if (state8 == HIGH || state9 == HIGH) {
      	    state8 = HIGH;
      	    state9 = LOW;
      	  }
	}
    }  else if (key1_3) {
      if (state8 == LOW && state9 == LOW && state10 == LOW && state11 == LOW) {
        state9 = HIGH;
        state11 = HIGH;
      } else {
        if (state10 == HIGH || state11 == HIGH) {
          state10 = LOW;
          state11 = HIGH;
        }
        if (state8 == HIGH || state9 == HIGH) {
          state8 = LOW;
          state9 = HIGH;
        }
      }
    } else if (key2_1) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = LOW;
        state9 = LOW;
        state10 = HIGH;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = LOW;
        state10 = LOW;
        state11 = HIGH;
      }
    } else if (key2_2) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = HIGH;
        state9 = LOW;
        state10 = HIGH;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = HIGH;
        state10 = LOW;
        state11 = HIGH;
      }
    } else if (key2_3) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = HIGH;
        state9 = LOW;
        state10 = LOW;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = HIGH;
        state10 = LOW;
        state11 = LOW;
      }
    }
  } else {
    //todo: automatic regulatings here in future //note: yes, I can boogie
    state8 = LOW;
    state10 = LOW;
    state9 = HIGH;
    state11 = HIGH;
  }
  if (state8 == LOW) {
    digitalWrite(8, state8);
    digitalWrite(10, state10);
  } else {
    digitalWrite(10, state10);
    digitalWrite(8, state8);
  }
  if (state9 == LOW) {
    digitalWrite(9, state9);
    digitalWrite(11, state11);
  } else {
    digitalWrite(11, state11);
    digitalWrite(9, state9);
  }
//  delay(50);
}
