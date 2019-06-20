/**
 * @file Logger.cpp
 * @brief　ユーザーが与えたデータをcsv形式でLogフォルダ上に記録するクラス
 * @author T.Miyaji
 */
#include "Logger.h"

Logger::Logger(const char* mode)
{
  fp = std::fopen(getFileName().c_str(), mode);
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
