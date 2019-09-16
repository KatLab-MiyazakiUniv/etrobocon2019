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

    public:
      /**
       * コンストラクタ
       */
      MoveDirectGarage(Controller &controller_);
      /**
       * Lコースのガレージに直接向かう
       */
      void MoveDirectGarageL();
      /**
       *  Rコースのガレージに直接向かう
       **/
      void MoveDirectGarageR();
};

#endif