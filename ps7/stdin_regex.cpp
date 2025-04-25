// Copyright Manasa Praveen 2025
// compile with
// g++ stdin_regex.cpp

// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main() {
  string s, rs;
  regex e;

  // see https://en.cppreference.com/w/cpp/regex/error_type
  std::cout << "Here are some helpful error codes you may encounter\n";
  std::cout << "while constructing your regex\n";
  std::cout << "error_collate " << regex_constants::error_collate << endl;
  std::cout << "error_ctype " << regex_constants::error_ctype << endl;
  std::cout << "error_escape " << regex_constants::error_escape << endl;
  std::cout << "error_backref " << regex_constants::error_backref << endl;
  std::cout << "error_brack " << regex_constants::error_brack << endl;
  std::cout << "error_paren " << regex_constants::error_paren << endl;
  std::cout << "error_brace " << regex_constants::error_brace << endl;
  std::cout << "error_badbrace " << regex_constants::error_badbrace << endl;

  std::cout << endl;

  std::cout << "Enter regex > ";
  getline(cin, rs);

  try {
    e = regex(rs);
  } catch (regex_error& exc) {
    std::cout << "Regex constructor failed with code " << exc.code() << endl;
    exit(1);
  }

  std::cout << "Enter line > ";

  while (getline(cin, s)) {
    std::cout << endl;

    if (regex_match (s, e))
      std::cout << "string object \"" << s << "\" matched\n\n";
    if ( regex_match ( s.begin(), s.end(), e ) )
      std::cout << "range on \"" << s << "\" matched\n\n";

    smatch sm;    // same as match_results<string::const_iterator> sm;
    regex_match(s, sm, e);
    std::cout << "string object \"" << s << "\" with " << sm.size() << " matches\n\n";
    // uses constant iterators so requires -std=gnu++0x
    //    regex_match ( s.cbegin(), s.cend(), sm, e);
    //    cout << "range on \"" << s << "\" with " << sm.size() << " matches\n";
    if (sm.size() > 0) {
	    std::cout << "the matches were: ";
	    for (unsigned i=0; i < sm.size(); ++i) {
		    std::cout << "[" << sm[i] << "] " << endl;
	    }
    }

    std::cout << endl << endl;

    std::cout << "Enter line > ";
  }

  return 0;
}
