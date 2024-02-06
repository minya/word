#pragma once
#include <vector>
#include <string>
#include <iostream>

class Dictionary {
public:
  explicit Dictionary(std::wistream& in);
  const std::vector<std::wstring>& words() const;
private:
  std::vector<std::wstring> _words;
};