/**
 * @file Logger.cpp
 * @brief　ユーザーが与えたデータをcsv形式で記録するクラス
 * @author T.Miyaji
 */
#include "Logger.h"

LogFile::TemporaryObject::TemporaryObject(FILE* fp_, bool linefeed_)
  : fp(fp_), isHead(true), linefeed(linefeed_)
{
}

LogFile::TemporaryObject::~TemporaryObject()
{
  if(linefeed) std::fputc('\n', fp);
}

void LogFile::TemporaryObject::putDelimiter()
{
  // ファイルの先頭のときは、デリミタ―を挿入しない
  if(isHead) {
    isHead = false;
    return;
  }
  // コンマを挿入する
  std::fputc(',', fp);
}

Logger::Logger(const std::string& fileName, const char* mode, bool linefeed_)
  : fp(nullptr), linefeed(linefeed_)
{
  fp = std::fopen(getFileName(fileName).c_str(), mode);
  assert(fp != nullptr);
}

Logger::~Logger()
{
  std::fclose(fp);
}

const std::string& Logger::getFileName(const std::string& fileName) const
{
  return fileName;
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
