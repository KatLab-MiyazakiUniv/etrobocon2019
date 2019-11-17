/**
 *  @file   Navigator.h
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Controller.h"
#include "Distance.h"
#include "Filter.h"
#include "Pid.h"
#include "Rotation.h"
#include "TurnControl.h"
#include "LineTracer.h"
#include <cmath>
#include <array>

class Navigator {
 public:
  /**
   * コンストラクタ
   *
   * @brief Navigatorクラスのコンストラクタ
   * @param &controller_ [Controllerインスタンスの参照]
   * @param targetBrightness [黒と白の閾値]
   */
  explicit Navigator(Controller& controller_, int targetBrightness_);

  /**
   * 前進と後進をする
   *
   * @brief specifiedDistanceの値でbackwardかforwardを呼び出す。
   * @param specifiedDistance [移動したい距離(mm)。正なら前進、負なら後進。]
   * @param pwm [モータの強さ]
   * @return なし
   */
  void move(double specifiedDistance, int pwm = 30);

  /**
   * 指定した色まで前進と後進をする
   *
   * @param specifiedColor [指定する色]
   * @param pwm [モータの強さ。正なら前進、負なら後進する]
   * @return なし
   */
  void moveToSpecifiedColor(Color specifiedColor, int pwm = 30);

  /**
   * @brief 走行体を回頭させる(yawing)
   * @param angle [回頭角度(正の値)]
   * @param clockwise [時計回りに回転するかどうか(デフォルトで時計回り)]
   * @param pwm [モーターパワー]
   * @param weight [重み]
   */
  void spin(double angle, bool clockwise = true, int pwm = 7, double weight = 0.90);
  /**
   * 指定した距離までライントレースする
   * @param specifiedDistance [指定した距離(mm)。正なら前進、負なら後進。]
   * @param pwm [モーターパワー(正の値)]
   * @param lineTracePGain [ライントレースに使用するPゲイン]
   * @param isLeft [左エッジならtrue]
   */
  void lineTrace(double specifiedDistance, int pwm = 10, double lineTracePGain = 0.6,
                 bool isLeft = true);
  /**
   * 指定した色までライントレースする
   * @brief 黒と白以外の指定した色までP制御でライントレースをする
   * @param specifiedColor [指定する色]
   * @param pwm [モーターパワー]
   * @param lineTracePGain [ライントレースに使用するPゲイン]
   * @param isLeft [左エッジならtrue]
   */
  void lineTraceToSpecifiedColor(Color specifiedColor, int pwm = 10, double lineTracePGain = 0.6,
                                 bool isLeft = true);
  /**
   * 黒と白以外のいづれかの色までライントレースする
   * @param pwm [モーターパワー]
   * @param lineTracePGain [ライントレースに使用するPゲイン]
   * @param isLeft [左エッジならture]
   */
  void lineTraceExcludingMonochrome(int pwm = 10, double lineTracePGain = 0.6, bool isLeft = true);
  /**
   * 循環バッファー内にある指定色の個数を計算する
   * @param circulation [循環バッファー]
   * @param index [循環バッファーのインデックス]
   * @param specifiedColor [指定色]
   */
  template <int N>
  int countColorInBuffer(std::array<Color, N>& circulation, unsigned int& index,
                         Color specifiedColor)
  {
    int count = 0;  // 指定色が循環バッファに存在する個数

    // 循環バッファーに色情報を格納する
    if(circulation.size() <= index) index = 0;
    circulation[index] = controller.getColor();
    ++index;

    // 循環バッファー内にある指定色の個数を計算する
    for(const auto& color : circulation) {
      if(color == specifiedColor) ++count;
    }

    return count;
  }

 private:
  Distance distance;
  Controller& controller;
  const int targetBrightness;
  /**
   * 指定した距離動いたか判定する
   * @brief 現在値とgoalDistanceを比較し、resultに"true"か"false"を格納する
   * @param goalDistance [現在地から移動したい距離動いた後の値(mm)]
   * @param isForward [前進なら"true"、後進なら"false"]
   * @return result [移動したい距離動いたら"true"、動いていないなら"false"]
   */
  bool hasArrived(double goalDistance, bool isForward);
  /**
   * @brief pwmをセットする
   * @param pwm [モータの強さ]
   * @param alpha [左右のPWM値の差]
   * @return なし
   */
  void setPwmValue(int pwm, double alpha = 0.0);
  /**
   * スムーズに走り出すためにセットするpwmを決める
   * @param 最初の何回かを小さめのpwmにする
   * @param counter [カウンター]
   * @param pwm [モーターパワー]
   * @param step [pwmを上げる回数]
   * @retrun 実際にセットするpwm値
   */
  int accelerate(int& counter, int pwm, int step);
};

#endif
