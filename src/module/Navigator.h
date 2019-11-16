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
<<<<<<< HEAD
#include "Pid.h"
#include "SpeedControl.h"
#include "Rotation.h"
#include <cmath>
=======
#include "Filter.h"
#include "Pid.h"
#include "Rotation.h"
#include "TurnControl.h"
#include "LineTracer.h"
#include <cmath>
#include <array>
>>>>>>> upstream/master

class Navigator {
 public:
  /**
   * コンストラクタ
   *
   * @brief Navigatorクラスのコンストラクタ
   * @param &controller_ [Controllerインスタンスの参照]
   * @param targetBrightness [黒と白の閾値]
<<<<<<< HEAD
   * @param Kp_ [SpeedControl用のPゲイン]
   * @param Ki_ [SpeedControl用のIゲイン]
   * @param Kd_ [SpeedControl用のDゲイン]
   */
  explicit Navigator(Controller& controller_, int targetBrightness_, double Kp_ = 0.60,
                     double Ki_ = 0.0, double Kd_ = 0.0);

  /**
   * @brief SpeedControl用のPidゲインのセッター
   * @param Kp_ [SpeedControl用のPゲイン]
   * @param Ki_ [SpeedControl用のIゲイン]
   * @param Kd_ [SpeedControl用のDゲイン]
   * @return なし
   */
  void setPidGain(double Kp, double Ki, double Kd);
=======
   */
  explicit Navigator(Controller& controller_, int targetBrightness_);
>>>>>>> upstream/master

  /**
   * 前進と後進をする
   *
   * @brief specifiedDistanceの値でbackwardかforwardを呼び出す。
   * @param specifiedDistance [移動したい距離(mm)。正なら前進、負なら後進。]
   * @param pwm [モータの強さ]
   * @param pGain [PID制御におけるPゲイン (デフォルトは0.0なので指定しなければP制御は実行されない)]
   * @return なし
   */
  void move(double specifiedDistance, int pwm = 30, const double pGain = 0.0);

  /**
   * 指定した速度で前進と後進をする
   *
   * @brief specifiedDistanceとSpeedControl.calculateSpeedから戻ってきたPWMをmoveに渡す
   * @param specifiedDistance [移動したい距離(mm)]
   * @param specifiedSpeed [移動したい速度]
   * @return なし
   */
  void moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed);

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
<<<<<<< HEAD
   */
  void spin(double angle, bool clockwise = true, int pwm = 10);
  /**
   * 指定した色までライントレースする
   * @brief 黒と白以外の色までOn Off制御でライントレースをする
   * @param specifiedColor [指定する色]
   * @param pwm [モーターパワー]
   * @param pGain
   */
  void traceBlackLineToSpecifiedColor(Color specifiedColor, int pwm = 10, double pGain = 0.6,
                                      bool isLeft = true);
=======
   * @param weight [重み]
   */
  void spin(double angle, bool clockwise = true, int pwm = 10, double weight = 0.94);
  /**
   * 指定した距離までライントレースする
   * @param specifiedDistance [指定した距離(mm)。正なら前進、負なら後進。]
   * @param pwm [モーターパワー(正の値)]
   * @param encoderPGain [エンコーダーの値をP制御する際に使用するPゲイン]
   * @param lineTracePGain [ライントレースに使用するPゲイン]
   * @param isLeft [左エッジならtrue]
   */
  void lineTrace(double specifiedDistance, int pwm = 10, double encoderPGain = 0.6,
                 double lineTracePGain = 0.6, bool isLeft = true);
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
>>>>>>> upstream/master

 private:
  Distance distance;
  Controller& controller;
<<<<<<< HEAD
  PidGain pidForSpeed;
=======
>>>>>>> upstream/master
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
<<<<<<< HEAD
  /**
   * 現在とっている色が黒かを判断する
   * @param brightness [現在のカラーセンサーの取得値]
   * @return 黒ならtrue、白ならfalseを返す
   */
  Color recognizeBlack(int brightness);
=======
>>>>>>> upstream/master
};

#endif
