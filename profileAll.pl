#!/usr/bin/perl -w

use strict;

my $runsPerLanguage = 500;

my %languages = (
"C" => "c/Release/Checkers-C $runsPerLanguage", 
"C++" => "cpp/Checkers-CPP/Game $runsPerLanguage",
"Java" => "java/target/appassembler/bin/checkers $runsPerLanguage", # Was 100000 
"Groovy" => "groovy/target/appassembler/bin/checkers $runsPerLanguage", # Was 40000
"Python3" => "python3 python/python/src/game.py $runsPerLanguage",
"Ruby" => "RUBYLIB=ruby ruby ruby/Driver.rb $runsPerLanguage");


my %timings;
foreach my $lang (keys %languages) {
	print "Executing $lang for $runsPerLanguage runs\n";
	my $cmd = $languages{$lang};
	my $output = `$cmd`;
	$output =~ /(\d*\.\d*) ms/;
	my $timing = $1;
	
	$timings{$lang} = $timing;
}

foreach my $lang (sort { $timings{$b} <=> $timings{$a} } keys %timings) {
	my $len = 15 - length $lang;
	print "$lang" . ' ' x $len . ": $timings{$lang} ms/game\n";
}
