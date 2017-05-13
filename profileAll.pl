#!/usr/bin/perl -w

use strict;

my $runsPerLanguage = 500;

my %languages = (
"C" => "c/Release/Checkers-C $runsPerLanguage", 
"C++" => "cpp/Checkers-CPP/Game $runsPerLanguage",
"Java" => "java/target/appassembler/bin/checkers $runsPerLanguage", # Was 100000 
"Groovy" => "groovy/target/appassembler/bin/checkers $runsPerLanguage", # Was 40000
"Python3" => "python3 python/python/src/game.py $runsPerLanguage",
"Ruby" => "RUBYLIB=ruby ruby ruby/Driver.rb $runsPerLanguage",
"Perl" => "PERLLIB=perl perl perl/driver.pl $runsPerLanguage");


my %timings;
foreach my $lang (sort keys %languages) {
	print "Executing $lang for $runsPerLanguage runs\n";
	my $cmd = $languages{$lang};
	my $output = `$cmd`;
	$output =~ /(\d*\.\d*) ms/;
	my $timing = $1;
	
	$timings{$lang} = $timing;
}

my $minTime = 100000;
foreach my $lang (keys %timings) { my $val = $timings{$lang} ; $minTime = ($val <= $minTime ? $val : $minTime); }

foreach my $lang (sort { $timings{$a} <=> $timings{$b} } keys %timings) {
	my $multiplier = $timings{$lang} / $minTime;
	printf ("%-10s : %2.2f ms/game - (%.1fx)\n", $lang, $timings{$lang}, $multiplier);
}
