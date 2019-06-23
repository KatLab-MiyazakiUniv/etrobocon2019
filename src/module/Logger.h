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
    bool linefeed;

   public:
    TemporaryObject(FILE* fp_, bool linefeed_);
    /**
     * @brief 行末に改行を挿入する (linefeedがtrueのとき)
     */
    ~TemporaryObject();
    /**
     * @brief データの先頭にデリミタ―を挿入する
     * @note 行頭の場合は、デリミタ―は挿入されない
     */
    void putDelimiter();

    /**
     * @brief 整数型のデータを出力ファイルに書き込む
     * @detail Usage: foo << 1 << 2 << 3;
     * (自動的にデリミターと、linefeedがtrueのとき改行が挿入される)
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
     * @detail Usage: foo << 1.2 << 2.4 << 3.98;
     * (自動的にデリミターと、linefeedがtrueのとき改行が挿入される)
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
     * @detail Usage: foo << "aa" << "bb"
     * (自動的にデリミターと、linefeedがtrueのとき改行が挿入される)
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
  bool linefeed;

 public:
  /**
   * @brief ファイルポインターを確保するコンストラクター
   * @param mode [ファイルの書き込みモード（デフォルトでは書き込みモード）]
   * @param linefeed_ [<<演算子を用いたとき、自動的に改行を入れるかどうか（デフォルトでは挿入する）]
   */
  Logger(const std::string& fileName = "log.csv", const char* mode = "w", bool linefeed_ = true);

  /**
   * @brief ファイルポインターを解放するデストラクター
   */
  ~Logger();

  /**
   * @brief 出力ファイル名を返す
   */
  const std::string& getFileName(const std::string& fileName) const;

  /**
   * @brief 指定したデータを出力ファイルに書き込む
   * @detail Usage: foo.write("%d,%f,%s\n", x, y, z);
   * @param format [書式指定子]
   */
  void write(const char* format, ...);

  /**
   * @brief 指定したデータを出力ファイルに書き込む
   * @detail Usage: foo << 1 << 2.4 << "aa";
   * (自動的にデリミターと、linefeedがtrueのとき改行が挿入される)
   * @param data [記録するデータ]
   */
  template <typename T>
  LogFile::TemporaryObject operator<<(T data)
  {
    LogFile::TemporaryObject object(fp, linefeed);
    object << data;
    return object;
  }
};

#endif
