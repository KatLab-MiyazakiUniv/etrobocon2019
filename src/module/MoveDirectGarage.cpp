/**
 *  @file   MoveDirectGarage
 *  @brief  ビンゴを行わずにガレージに向かうクラス
 *  @author match97
 */

//このクラスが使用されないことを願う

#include "MoveDirectGarage.h"

MoveDirectGarage::MoveDirectGarage(Controller &controller_) : controller(controller_) {}

void MoveDirectGarage::MoveDirectGarageL()
{
    Navigator navigator(controller);

    //ブロックを押す
    navigator.moveToSpecifiedColor(Color::yellow, 10);   
    navigator.move(-60, 10, 0.6);
    navigator.spin(45.0,false);
    navigator.moveToSpecifiedColor(Color::black, 15);
    //4のとこ
    navigator.moveToSpecifiedColor(Color::white, 15);    
    navigator.moveToSpecifiedColor(Color::black, 15);
    navigator.move(30, 10, 0.6);
    navigator.spin(45.0,true);
    //ブロックを押す
    navigator.moveToSpecifiedColor(Color::red, 10);
    navigator.move(-60, 10, 0.6);
    navigator.spin(45.0,true);
    navigator.moveToSpecifiedColor(Color::black, 15);
    navigator.move(65, 10, 0.6);
    navigator.spin(45.0,false);
    //真ん中
    navigator.moveToSpecifiedColor(Color::white, 15);
    navigator.moveToSpecifiedColor(Color::black, 15);
    navigator.moveToSpecifiedColor(Color::white, 15);
    navigator.move(30, 10, 0.6);
    navigator.spin(90.0,true);
    navigator.moveToSpecifiedColor(Color::green, 10);
    navigator.move(-60, 8, 0.6);
    navigator.spin(45.0,false);
    //５のとこ
    navigator.moveToSpecifiedColor(Color::black, 15);
    navigator.moveToSpecifiedColor(Color::white, 15);
    navigator.move(20, 10, 0.6);
    navigator.spin(45.0,false);
    //以下はparkingクラスを使用

}

void MoveDirectGarage::MoveDirectGarageR()
{
    Navigator navigator(controller);

    navigator.moveToSpecifiedColor(Color::yellow, 10);
    //5のとこ
    navigator.move(100, 10, 0.6);
    navigator.moveToSpecifiedColor(Color::black, 10);
    navigator.moveToSpecifiedColor(Color::yellow, 10);
    navigator.move(-60, 10, 0.6);
    navigator.spin(45.0,true);
    navigator.moveToSpecifiedColor(Color::black, 10);
    navigator.move(60, 10, 0.6);
    navigator.spin(45.0,false);
    //真ん中
    navigator.moveToSpecifiedColor(Color::white, 10);
    navigator.moveToSpecifiedColor(Color::black, 10);
    navigator.moveToSpecifiedColor(Color::white, 10);
    navigator.move(30, 10, 0.6);
    navigator.spin(90.0,true);
    navigator.moveToSpecifiedColor(Color::blue, 10);
    navigator.move(-60, 10, 0.6);
    navigator.spin(45.0,false);
    //4のとこ
    navigator.moveToSpecifiedColor(Color::white, 10);
    navigator.moveToSpecifiedColor(Color::black, 10);
    navigator.moveToSpecifiedColor(Color::white, 10);
    navigator.move(30, 10, 0.6);
    navigator.spin(45.0,false);
    //以下はparkingクラスを使用

}
