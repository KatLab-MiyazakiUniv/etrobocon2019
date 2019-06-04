/**
 *  @file   Filter.cpp
 *  @brief  外乱対策のためのフィルターをまとめたクラス
 *  @author T.Miyaji
 */
#include "Filter.h"

template <typename T>
Filter<T>::Filter() : preValue_(0)
{
}

/**
 *  [Filter::lowPassFilter]
 *  @brief  ローパスフィルター(現在値と前回値を参考にして値を決定する)
 *  @param  value [現在の値]
 *  @param  rate  [前回値を参考にする割合]
 *  @return       [フィルター後の値]
 */
template <typename T>
double Filter<T>::lowPassFilter(T value, double rate)
{
  // 前回値の初期化
  if(preValue_ == 0) {
    preValue_ = value;
    return static_cast<double>(value);
  }

  return preValue_ * rate + value * (1 - rate);
}

// 明示的なインスタンス化
template class Filter<int>;
template class Filter<float>;
template class Filter<double>;
