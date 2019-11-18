/**
 * @file Parking.h
 * @brief ガレージ駐車に使用するクラス
 * @author Oiwane
 */
#ifndef PARKING_H
#define PARKING_H

#include "Controller.h"
#include "Navigator.h"

class Parking {
 private:
  Controller controller;
  const int targetBrightness;

  /**
   * 3秒間停車する
   */
  void stopFor3sec();

 public:
  /**
   * コンストラクタ
   */
  Parking(Controller& controller_, int targetBrightness_);
  /**
   * Lコースのガレージ駐車を行う
   */
  void parkAtAL();
  /**
   * Rコースのガレージ駐車を行う
   */
  void parkAtAR();
};

#endif