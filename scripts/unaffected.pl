#!/usr/bin/perl

use strict;
use warnings;

use JSON;

my $hash = JSON::decode_json(do { local $/; <STDIN> });
foreach my $key (keys %$hash) {
	print "$key => \n";
}
