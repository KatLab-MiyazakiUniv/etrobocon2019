/**
 * @file Logger.cpp
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#include "Logger.h"

Logger::Logger(const char* mode)
{
  fp = std::fopen(getFileName().c_str(), mode);
  assert(fp != nullptr);
}

Logger::~Logger()
{
  std::fclose(fp);
}

std::string Logger::getFileName()
{
  // TODO とりあえずログファイル名は、「log」としておく
  // ユニークな名前にするためには、例えば現在時刻を取得する必要があるが、取得しようとするとmutexエラーが起きる
  return "log.csv";
}

void Logger::write(const char* format, ...)
{
  // 可変長引数の展開
  va_list args;
  va_start(args, format);

  // ファイル出力
  std::vfprintf(fp, format, args);

  va_end(args);
}

void Logger::putDelimiter()
{
  // ファイルの先頭のときは、デリミタ―を挿入しない
  if(std::ftell(fp) == SEEK_SET) return;

  // ファイルの末尾にコンマを挿入する
  fseek(fp, -1L, SEEK_END);
  fputc(',', fp);
}
