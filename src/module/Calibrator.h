/**
 *  @file   Calibrator.h
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <cstring>
#include "Controller.h"
#include "Display.h"

enum class Brightness { WHITE, BLACK };

class Calibrator {
 public:
  explicit Calibrator(Controller &controller_);

  /** キャリブレーションを行う。
   * @brief
   * falseが返ってきた場合、エラーメッセージがLCDに出ます。スタートを取りやめ、原因をさぐってください。
   * @return キャリブレーションが成功したかどうかの真理値(Trueなら正常終了)
   */
  bool calibration();

  /** Leftコースであるかどうかを判断する。
   * @return Leftコースであるかどうかの真偽値（TrueならLeftコース）
   */
  bool isLeftCource() const;

  /** 白色の値を取得する。
   * @return 明るさ
   */
  int getWhiteBrightness() const;

  /** 黒色の値を取得する。
   * @return 明るさ
   */
  int getBlackBrightness() const;

  /** LコースかRコースかを設定する。
   * @return 正常終了したかどうかの真偽値（Trueなら正常終了）
   */
  bool setLRCource();

  /** 明るさを設定する。
   * @param brightness 白か黒かの明るさ
   * @return 正常終了したかどうかの真偽値（Trueなら正常終了）
   */
  bool setBrightness(Brightness brightness);

 private:
  Controller &controller;
  bool isLeft;  // Leftコースであるかどうかの真偽値（TrueならLeftコース）
  unsigned int brightnessOfWhite;  // 白色の明るさ
  unsigned int brightnessOfBlack;  // 黒色の明るさ

  int averageBrightness();
};

#endif
