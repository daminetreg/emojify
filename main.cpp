#include <iostream>
#include <algorithm>
#include <locale>
#include <codecvt> 

namespace pre { namespace unicode {

  inline std::string to_utf8(const std::u16string& utf16) {
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(utf16);
  }

  inline std::u16string to_utf16(const std::string& utf8) {
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(utf8);
  }

  inline std::string to_utf8(const std::u32string& utf32) {
    return std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t>{}.to_bytes(utf32);
  }

  inline std::u32string to_utf32(const std::string& utf8) {
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}.from_bytes(utf8);
  }


}}

inline std::string emojify(const std::string& cleartext) {

  char32_t base = U'😀';  //0xd83dde00;

  auto result = pre::unicode::to_utf32(cleartext);

  std::transform(result.begin(), result.end(), result.begin(),
    [base](auto c) {
      auto enc = base + (U'z' - std::tolower(c)) ;
      std::cout << int32_t(c) << " into " << int32_t(enc) << std::endl;
      return enc;
    });

  return pre::unicode::to_utf8(result);
}

inline std::string asciify(const std::string& emojized) {

  char32_t base = U'😀';  //0xd83dde00;

  auto result = pre::unicode::to_utf32(emojized);

  std::transform(result.begin(), result.end(), result.begin(),
    [base](auto c) {
      auto dec  =   U'z' - (c - base);
      std::cout << int32_t(c) << " into " << int32_t(dec) << std::endl;
      return dec;
    });

  return pre::unicode::to_utf8(result);
}

int main(int argc, char** argv) {

  if (argc > 1) {
    std::string arg{argv[1]};

    if (pre::unicode::to_utf32(arg)[0] >= U'😀') {
      auto emojified = asciify(arg);
      std::cout << " emojified (" << emojified.size() <<  " / " << arg.size() << ") : " << emojified << std::endl;
    } else {
      auto asciified = emojify(arg);
      std::cout << " asciified (" << asciified.size() <<  " / " << arg.size() << ") : " << asciified << std::endl;
    }

    return 0;
  }

 // for (char32_t base = U'😀'; base < (U'😀' + 26); ++base) {
 //   std::cout << int32_t(base) << pre::unicode::to_utf8(std::u32string(1, base)) << "-";
 // }
 // std::cout << std::endl;

 // std::cout << "😀" <<
 //   pre::bytes::to_hexstring("a")
//<< std::endl;

 // std::string input; std::cin >> input;

 // auto emojified = emojify(input);
 // std::cout << " emojified (" << emojified.size() <<  " / " << input.size() << ") : " << emojified << std::endl;
 // 
 // auto asciified = asciify(emojified);
 // std::cout << " asciified (" << asciified.size() <<  " / " << emojified.size() << ") : " << asciified << std::endl;
  return 0;
}
