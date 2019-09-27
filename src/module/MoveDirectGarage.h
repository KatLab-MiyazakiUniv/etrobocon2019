/**
 *  @file   MoveDirectGarage
 *  @brief  ビンゴを行わずにガレージに向かうクラス
 *  @author match97
 */
#ifndef MOVEDIRECTGARAGE_H
#define MOVEDIRECTGARAGE_H

#include "Controller.h"
#include "Navigator.h"

class MoveDirectGarage {
  private:
    Controller controller;
    const int targetBrightness;

  public:
    /**
     * コンストラクタ
     */
    MoveDirectGarage(Controller &controller_, int targetBrightness_);
    /**
     * Lコースのガレージに直接向かう
     */
    void moveDirectGarageL();
    /**
     *  Rコースのガレージに直接向かう
     **/
    void moveDirectGarageR();
};

#endif