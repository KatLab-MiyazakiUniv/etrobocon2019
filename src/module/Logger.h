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
#include <type_traits>

class Logger {
 private:
  FILE* fp;

 public:
  /**
   * @brief ファイルポインターを確保するコンストラクター
   * @param mode [ファイルの書き込みモード（デフォルトでは追記）]
   */
  Logger(const char* mode = "a");

  /**
   * @brief ファイルポインターを解放するデストラクター
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

  /**
   * @brief 挿入するデータの末尾にデリミタ―(コンマ)を挿入する
   */
  void putDelimiter();

  /**
   * @brief 整数型のデータを出力ファイルに書き込む
   * @detail Usage: foo << 1 << 2 << 3; (自動的にデリミターと改行が挿入される)
   * @param intValue [整数型(int, unsigned int, std::int8_t, etc...)]
   */
  template <typename T,
            typename std::enable_if<std::is_integral<T>::value, std::nullptr_t>::type = nullptr>
  Logger& operator<<(T intValue)
  {
    putDelimiter();
    fprintf(fp, "%d\n", intValue);
    return *this;
  }

  /**
   * @brief 浮動小数点数型のデータを出力ファイルに書き込む
   * @detail Usage: foo << 1.2 << 2.4 << 3.98; (自動的にデリミターと改行が挿入される)
   * @param floatingPointValue [浮動小数点数型(float, double)]
   */
  template <typename T,
            typename std::enable_if<std::is_floating_point<T>::value, std::nullptr_t>::type
            = nullptr>
  Logger& operator<<(T floatingPointValue)
  {
    putDelimiter();
    fprintf(fp, "%f\n", floatingPointValue);
    return *this;
  }

  /**
   * @brief 文字列を出力ファイルに書き込む
   * @detail Usage: foo << "aa" << "bb" (自動的にデリミタ―と改行が挿入される)
   * @param stringLiteral [文字列型（const char*)]
   */
  template <typename T,
            typename std::enable_if<std::is_same<T, const char*>::value>::type* = nullptr>
  Logger& operator<<(T stringLiteral)
  {
    putDelimiter();
    fprintf(fp, "%s\n", stringLiteral);
    return *this;
  }
};

#endif
