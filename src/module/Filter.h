/**
 *  @file   Filter.h
 *  @brief  外乱対策のためのフィルターをまとめたクラス
 *  @author T.Miyaji
 */
#ifndef FILTER_H
#define FILTER_H

template <typename T = int>
class Filter {
 private:
  T preValue;

 public:
  Filter();
  void reset();
  double lowPassFilter(T value, double rate = 0.9);
  double complementaryFilter(T heavyValue, T lightValue, double rate = 0.93);
};

#endif
