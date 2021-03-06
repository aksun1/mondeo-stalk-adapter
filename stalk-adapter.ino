/*
 * ESP32 Radio Stalk Bluetooth Media Controller
 * designed for Mondeo mk2 radio stalk and ESP-WROOM-32 dev board. 
 * Maintainer: https://github.com/aksun1
 * 
 * History:
 * 1.0.0  3/21    Basic media controls implementation.
 * 
 * To be implemented: telephone controls (+siri?), Ford ACP integration.
 * 
*/
#include <Button2.h>
#include <BleKeyboard.h>

//#define CONN_1 12
//#define CONN_2 14
#define AM_FM 27
#define SEEK_DOWN 26
#define SEEK_UP 25
#define VOL_UP 33
#define VOL_DOWN 32

BleKeyboard bleKeyboard("rattiohjain", "aksun", 100);

Button2 am_fm = Button2(AM_FM);
Button2 seek_down = Button2(SEEK_DOWN);
Button2 seek_up = Button2(SEEK_UP);
Button2 vol_up = Button2(VOL_UP);
Button2 vol_down = Button2(VOL_DOWN);


void setup() {
  bleKeyboard.begin();

  // configure stalk features:
  // following configuration omits press duration
  am_fm.setTapHandler(play_pause);

  // following configuration allows for continous press and short single presses
  vol_up.setClickHandler(increase_volume);
  vol_up.setDoubleClickTime(0);
  vol_up.setLongClickDetectedHandler(increase_volume);
  vol_up.setLongClickDetectedRetriggerable(true);
  
  vol_down.setClickHandler(decrease_volume);
  vol_down.setDoubleClickTime(0);
  vol_down.setLongClickDetectedHandler(decrease_volume);
  vol_down.setLongClickDetectedRetriggerable(true);

  seek_up.setTapHandler(next_track);

  seek_down.setTapHandler(previous_track);
}

// the loop routine runs over and over again forever:
void loop() {
  if(bleKeyboard.isConnected()) {
    am_fm.loop();
    vol_up.loop();
    vol_down.loop();
    seek_up.loop();
    seek_down.loop();
  }
}

void play_pause(Button2& btn) {
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void increase_volume(Button2& btn) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}
void decrease_volume(Button2& btn) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}

void next_track(Button2& btn) {
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}
void previous_track(Button2& btn) {
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}
