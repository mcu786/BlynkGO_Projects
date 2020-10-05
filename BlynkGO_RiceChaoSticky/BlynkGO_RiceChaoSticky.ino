/***********************************************
 * 
 * ตัวอย่างโปรเจค
 *    เลื่อนนิ้วปาดขึ้น เพิ่มค่า  ปาดลง ลดค่า
 *    กดปุ่ม + เพิ่มค่า  กดปุ่ม - ลดค่า
 * 
 * ออกแบบสำหรับจอ 3.5นิ้ว, 4 นิ้ว
 * 
 ***********************************************/

#include <BlynkGO.h>

FONT_DECLARE(kanitlight_num_70);
IMG_DECLARE(pic_rice_chao);
IMG_DECLARE(pic_rice_sticky);

GImage rice_chao(pic_rice_chao);
GImage rice_sticky(pic_rice_sticky);

GLabel lb_chao_info("ข้าวเจ้า");
GLabel lb_sticky_info("ข้าวเหนียว");
GLabel lb_chao(rice_chao);
GLabel lb_sticky(rice_sticky);

GButton btn_chao[2];
GButton btn_sticky[2];

int16_t rice_chao_num;
int16_t rice_sticky_num;

void setup() {
  Serial.begin(115200); Serial.println();
  BlynkGO.begin();

  rice_chao.align(ALIGN_CENTER, - rice_chao.width()/2-10);
  rice_sticky.align(ALIGN_CENTER,  rice_chao.width()/2 + 10);

//  rice_chao.filter(TFT_WHITE, 100);  
  rice_chao.font(kanitlight_num_70, TFT_BLACK);
  rice_sticky.linkStyle(rice_chao);
  
  lb_chao   = String(rice_chao_num);
  lb_sticky = String(rice_sticky_num);

  lb_chao_info.align(rice_chao, ALIGN_TOP);
  lb_sticky_info.align(rice_sticky, ALIGN_TOP);

  rice_chao.clickable(true);
  rice_chao.gesture(true);
  rice_chao.onGesture([](GWidget*w){
    gesture_dir_t gesture = w->touch_gesture();
    switch(gesture){
      case GESTURE_DIR_TOP:     rice_chao_plus();    break;
      case GESTURE_DIR_BOTTOM:  rice_chao_minus();   break;
    }
  });
  rice_sticky.clickable(true);
  rice_sticky.gesture(true);
  rice_sticky.onGesture([](GWidget*w){
    gesture_dir_t gesture = w->touch_gesture();
    switch(gesture){
      case GESTURE_DIR_TOP:       rice_sticky_plus();   break;
      case GESTURE_DIR_BOTTOM:    rice_sticky_minus();  break;
    }
  });
  btn_chao[0] = "-";
  btn_chao[0].size(60,60);
  btn_chao[0].color(TFT_RED);
  btn_chao[0].rounded(true);
  btn_chao[0].onPressed(btn_pressed);
  btn_chao[0].onPressing(btn_pressing);
  btn_chao[0].onLongPressed(btn_long_pressed);
  
  btn_chao[1] = "+";
  btn_chao[1].size(60,60);
  btn_chao[1].rounded(true);
  btn_chao[1].color(TFT_GREEN);
  btn_chao[1].onPressed(btn_pressed);
  btn_chao[1].onPressing(btn_pressing);
  btn_chao[1].onLongPressed(btn_long_pressed);

  btn_chao[0].align(rice_chao, ALIGN_BOTTOM_LEFT,10);
  btn_chao[1].align(rice_chao, ALIGN_BOTTOM_RIGHT,-10);

  btn_sticky[0] = "-";
  btn_sticky[0].size(60,60);
  btn_sticky[0].rounded(true);
  btn_sticky[0].color(TFT_RED);
  btn_sticky[0].onPressed(btn_pressed);
  btn_sticky[0].onPressing(btn_pressing);
  btn_sticky[0].onLongPressed(btn_long_pressed);
  
  btn_sticky[1] = "+";
  btn_sticky[1].size(60,60);
  btn_sticky[1].rounded(true);
  btn_sticky[1].color(TFT_GREEN);
  btn_sticky[1].onPressed(btn_pressed);
  btn_sticky[1].onPressing(btn_pressing);
  btn_sticky[1].onLongPressed(btn_long_pressed);

  btn_sticky[0].align(rice_sticky, ALIGN_BOTTOM_LEFT,10);
  btn_sticky[1].align(rice_sticky, ALIGN_BOTTOM_RIGHT,-10);
  
}

void loop() {
  BlynkGO.update();
}

uint32_t deboucing_time;
uint32_t timer;
void btn_pressing(GWidget*w){
  if(timer >  millis()) return;
  timer = millis() + deboucing_time;
  
  if( btn_chao[1] == w)   { rice_chao_plus();   }else
  if( btn_chao[0] == w)   { rice_chao_plus();   }else
  if( btn_sticky[1] == w) { rice_sticky_plus(); }else
  if( btn_sticky[0] == w) { rice_sticky_minus(); }
}

void btn_pressed(GWidget*w ){
  deboucing_time = 100;
  if(timer >  millis()) return;
  timer = millis() + deboucing_time;
  if( btn_chao[1] == w)   { rice_chao_plus();   }else
  if( btn_chao[0] == w)   { rice_chao_plus();   }else
  if( btn_sticky[1] == w) { rice_sticky_plus(); }else
  if( btn_sticky[0] == w) { rice_sticky_minus(); }
}

void btn_long_pressed(GWidget*w){
  deboucing_time = 50;
}

void rice_chao_plus(){
  lb_chao = String(++rice_chao_num);
}

void rice_chao_minus(){
  rice_chao_num--; if(rice_chao_num < 0) rice_chao_num = 0;
  lb_chao = String(rice_chao_num);
}

void rice_sticky_plus(){
  lb_sticky = String(++rice_sticky_num);
}

void rice_sticky_minus(){
  rice_sticky_num--; if(rice_sticky_num < 0) rice_sticky_num = 0;
  lb_sticky = String(rice_sticky_num);
}
