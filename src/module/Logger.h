/**
 * @file Logger.h
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <cstdarg>
#include <string>

class Logger {
 private:
  FILE* fp;

 public:
  /**
   * @brief ファイルポインタを確保するコンストラクタ
   * @param mode [ファイルの書き込みモード（デフォルトでは追記）]
   */
  Logger(const char* mode = "a");
  /**
   * @brief ファイルポインタを解放するデストラクタ
   */
  ~Logger();
  std::string getFileName();
  bool write(const char* format, ...);
};

#endif
