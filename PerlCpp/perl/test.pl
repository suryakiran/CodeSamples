sub func_noargs {
  print "This line is coming from perl script\n";
}

sub func_2args {
  my ($a1, $a2) = @_;
  print "A1: " . $a1 . "\n";
  print "A2: " . $a2 . "\n";
}

sub func_2args_return {
  my ($a1, $a2) = @_;
  return sprintf ("%s: %d", $a1, $a2);
}

sub func_return_array {
  my ($string) = @_;

  return split(/\./, $string);
}
