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
  T preValue_;

 public:
  Filter();
  double lowPassFilter(T value, double rate = 0.9);
};

#endif
