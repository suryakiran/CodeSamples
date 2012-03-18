use strict;
use warnings;
use Getopt::Long;
use File::Spec::Functions;
use Template;
use XML::Simple qw(:strict);
use XML::Parser;
use Data::Dumper;

my (
  $tmplFile,
  $outFile,
  $cmakeVarsFile, 
  $cmakeVars, 
  $exeName,
  $ld_lib_paths
);

GetOptions (
  'template|t=s' => \$tmplFile,
  'output|o=s' => \$outFile,
  'exeName|e=s' => \$exeName,
  'cmake-vars|x=s' => \$cmakeVarsFile,
  'dirs|d=s@' => \$ld_lib_paths
);

$cmakeVars = XMLin(
  $cmakeVarsFile,
  ForceArray => 0,
  KeyAttr => []
);

foreach (keys %$cmakeVars) {
  my $val = $cmakeVars->{$_};

  if (ref($val) eq 'HASH') {
    if (not scalar keys %$val) {
      delete $cmakeVars->{$_};
    }
  }
}

$cmakeVars->{os} = $^O;

if ($exeName) {
  $cmakeVars->{exeName} = $exeName;
}

if ($ld_lib_paths) {
  my %ldpaths = map {$_ => 1} @$ld_lib_paths;
  $cmakeVars->{LD_LIBRARY_PATHS}=[sort (keys %ldpaths)];
}

my $template = Template->new(
  INTERPOLATE => 1,
  ABSOLUTE => 1,
  EVAL_PERL => 1
);

$template->process ($tmplFile, $cmakeVars, $outFile);

chmod 0755, $outFile if -e $outFile;
