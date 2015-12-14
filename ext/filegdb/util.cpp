#include "filegdb.hpp"
#include <cstdlib>

const std::wstring to_wstring(const char *input) {
  std::string converted(input);
  return std::wstring(converted.begin(), converted.end());
}

const std::string to_string(std::wstring str) {
  static char result[16384];

  std::wcstombs(result, str.c_str(), sizeof(result));

  return std::string(result);
}

const std::string fgdb_error_string(fgdbError hr) {
  wstring errorText;
  ErrorInfo::GetErrorDescription(hr, errorText);
  return to_string(errorText);
}
