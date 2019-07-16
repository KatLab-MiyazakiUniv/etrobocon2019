/**
 *  @file   Bluetooth.h
 *  @brief  Bluetooth通信をする
 *  @author Tatsumi0000
 */
#ifndef BLUETOOH_H
#define BLUETOOH_H
#include <syssvc/serial.h>
class Bluetooth {
 public:
  /** コンストラクタ（今の所引数なし2019/07/16）
   *  @param controller [コントローラのインスタンス]
   */
  void Bluetooth();

  /**
   * PC側からメッセージを受取るメソッド
   * @param isLeftCourse_ [Leftコースである場合True]
   */
  void receiveMessage();

  /**
   * ロボットからPCへメッセージを送るメソッド
   * @param isLeftCourse_ [Leftコースである場合True]
   */
  void sendMessage();

  /**
   * sizeという名の変数を返すゲッター
   */
  int getSize() const;

 private:
  int size;
  static char message[9] = { 0 };
};

#endif
