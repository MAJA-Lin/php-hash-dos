#!/usr/bin/perl
# Minimize a JSON file.

use strict;
use warnings;

my $size = shift @ARGV;

my $count = 0;
my $entry = '';
while (<STDIN>) {
	$count++ if s/null/0/g;
	$entry .= $_;
	last if defined $size && $size == $count;
}
$entry .= "}" if $entry !~ /\}/;
$entry =~ s/,\s+\}/\}/g;
$entry =~ s/\s+//g;
print $entry;
