/**
 * @file Logger.h
 * @brief　ユーザーが与えたデータをcsv形式で記録するクラス
 * @detail 記録するためには、「write」または「<<演算子」機能を使用する。
 * @author T.Miyaji
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <string>
#include <type_traits>

namespace LogFile {
  class TemporaryObject {
   private:
    FILE* fp;
    bool isHead;

   public:
    TemporaryObject(FILE* fp_);
    /**
     * @brief 行末に改行を挿入する
     */
    ~TemporaryObject();
    /**
     * @brief データの先頭にデリミタ―を挿入する
     * @note 行頭の場合は、デリミタ―は挿入されない
     */
    void putDelimiter();

    /**
     * @brief 整数型のデータを出力ファイルに書き込む
     * @detail Usage: foo << 1 << 2 << 3; (自動的にデリミターと改行が挿入される)
     * @param intValue [整数型(int, unsigned int, std::int8_t, etc...)]
     */
    template <typename T,
              typename std::enable_if<std::is_integral<T>::value, std::nullptr_t>::type = nullptr>
    TemporaryObject& operator<<(T intValue)
    {
      putDelimiter();
      fprintf(fp, "%d", intValue);
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
    TemporaryObject& operator<<(T floatingPointValue)
    {
      putDelimiter();
      fprintf(fp, "%f", floatingPointValue);
      return *this;
    }

    /**
     * @brief 文字列を出力ファイルに書き込む
     * @detail Usage: foo << "aa" << "bb" (自動的にデリミタ―と改行が挿入される)
     * @param stringLiteral [文字列型（const char*)]
     */
    template <typename T,
              typename std::enable_if<std::is_same<T, const char*>::value>::type* = nullptr>
    TemporaryObject& operator<<(T stringLiteral)
    {
      putDelimiter();
      fprintf(fp, "%s", stringLiteral);
      return *this;
    }
  };
}  // namespace LogFile

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
   * @brief 指定したデータを出力ファイルに書き込む
   * @detail Usage: foo << 1 << 2.4 << "aa"; (自動的にデリミターと改行が挿入される)
   * @param data [記録するデータ]
   */
  template <typename T>
  LogFile::TemporaryObject operator<<(T data)
  {
    LogFile::TemporaryObject object(fp);
    object << data;
    return object;
  }
};

#endif
