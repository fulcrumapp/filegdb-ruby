#include "fgdb.hpp"

std::wstring to_wstring(const char *input) {
  std::string converted(input);
  return std::wstring(converted.begin(), converted.end());
}

const char* to_char_array(std::wstring str) {
  return std::string(str.begin(), str.end()).c_str();
}

const char *fgdb_error_string(fgdbError hr) {
  wstring errorText;
  ErrorInfo::GetErrorDescription(hr, errorText);
  return to_char_array(errorText);
}
