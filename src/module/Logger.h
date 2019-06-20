/**
 * @file Logger.h
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <string>

class Logger {
 private:
  FILE* fp;

 public:
  Logger(const char* mode = "a");
  ~Logger();
  std::string getFileName();
};

#endif
