/**
 * @file Logger.h
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <cstdarg>
#include <cassert>
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

  /**
   * @brief 出力ファイル名を返す
   */
  std::string getFileName();

  /**
   * @brief 指定したデータを出力ファイルに書き込む
   * @detail Usage: foo.write("%d,%f,%s\n", x, y, z);
   * @param format [書式指定子]
   */

  void write(const char* format, ...);
};

#endif
