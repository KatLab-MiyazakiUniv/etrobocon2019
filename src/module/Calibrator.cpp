/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& con_, Display& dis_)
    : con(con_), dis(dis_){}

bool Calibrator::calibration() {
  dis.print(2, "now calibration...");
  isFinish = false;

  isFinish = setLRCource();
  isFinish = setBrightness(Brightness::WHITE);
  isFinish = setBrightness(Brightness::BLACK);

  return isFinish;
}

bool Calibrator::setLRCource() {
  char cource[8] = "Left";

  while (!con.buttonIsPressedEnter()) {
    if (isLeft) {
      std::strcpy(cource,"Left");
    } else {
      std::strcpy(cource,"Right");
    }
    dis.print(3, "Set LRCource: %s ?", cource);

    if (con.buttonIsPressedLeft() || con.buttonIsPressedRight()) {
      isLeft = !isLeft;
    }
    con.tslpTsk(4);
  }

  return true;
}

bool Calibrator::setBrightness(Brightness b) { 
  int tmp_color = 0;
  char name[8] = "none";

  if(b == Brightness::WHITE){
    std::strcpy(name, "White");
  }else if(b == Brightness::BLACK){
    std::strcpy(name, "Black");
  }else{
    return false;
  }

  con.tslpTsk(500);

  while (1) {
    // ENTERボタンが押されたらループを抜ける
    if(con.buttonIsPressedEnter()) {
      con.speakerPlayToneFS6(100);
      break;
    }

    tmp_color = con.getBrightness();
    dis.print(3, "Set brightness of %s: %d ?", name, tmp_color);

    con.tslpTsk(4);
  }

  int mean_brightness = 0;
  int times = 10;
  for(int i = 0; i < times; i++) {
    mean_brightness += con.getBrightness();
    con.tslpTsk(4);
  }
  con.speakerPlayToneFS6(200);

  if(b == Brightness::WHITE){
    brightnessOfWhite = mean_brightness / times;
  }else{
    brightnessOfBlack = mean_brightness / times;
  }

  return true;
}

bool Calibrator::isLeftCource() { return isLeft; }
int Calibrator::getWhiteBrightness() { return brightnessOfWhite; };
int Calibrator::getBlackBrightness() { return brightnessOfBlack; };
