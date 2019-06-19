/**
 * @file Logger.h
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <string>

class Logger {
 private:
  unsigned int number;  // ファイル番号

 public:
  Logger();
  std::string getFileName();
};

#endif
