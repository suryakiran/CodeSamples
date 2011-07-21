%typemap{const int&}{parsed}{
  %cpp_type{%int%};
};

%typemap{const double&}{parsed}{
  %cpp_type{%double%};
};

%typemap{const std::string&}{parsed} {
  %cpp_type{%std::string%};
};

%typemap{bool}{simple};

%typemap{std::vector<std::string>}{parsed} {
  %cpp_type{%std::vector<std::string>%};
};
