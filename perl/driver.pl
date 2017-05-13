#!/usr/bin/perl

use Checkers::Game;
use Checkers::Board;
use Checkers::MoveRules;
use strict;
use warnings;

sub profile {
    my $numRuns = shift;
    
    use Time::HiRes;

    my $totalTime = 0;
    my $randomPlayer = { selectMove => sub { my ($b,@m) = @_; return $m[ rand @m ]; } }; bless $randomPlayer;
    
    for (my $i = 0; $i < $numRuns; $i += 1 ) {
        my $board = Checkers::Board->new;
        my $start = Time::HiRes::time;
        Checkers::Game::play( $board, $randomPlayer, $randomPlayer, \&Checkers::MoveRules::getMovesForColor, undef);
        my $end = Time::HiRes::time;
        $totalTime += ($end-$start);
    }
    
    my $msPerGame = ($totalTime*1000) / $numRuns;
    printf "Total time is %.2f sec to play %d games, or %.2f ms/game\n", $totalTime, $numRuns, $msPerGame;
}

sub playInteractive {
    use Checkers::Console;
    
    my $board = Checkers::Board->new;
    Checkers::Game::play( $board, Checkers::Console::player, Checkers::Console::player, \&Checkers::MoveRules::getMovesForColor, Checkers::Console::eventHandler);
}

if (scalar @ARGV > 0) {
    profile($ARGV[0]);
}
else {
    playInteractive();
}
