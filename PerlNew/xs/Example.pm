package Example;

use strict;
use warnings;

require Exporter;
require DynaLoader;

use base qw(Exporter DynaLoader);

our %EXPORT_TAGS = (
  'all' => [qw ()]
);

our @EXPORT_OK = (@{$EXPORT_TAGS {'all'}});
our @EXPORT = qw (
);

our $VERSION = '0.01';

bootstrap Example $VERSION;
