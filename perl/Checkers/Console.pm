package Checkers::Console;

use strict;
use warnings;
use Exporter;

our @ISA = qw(Exporter);
our @EXPORT   = qw(player eventHandler);

sub player {
    my $self = {
        selectMove => sub { my ($board,@moves) = @_; return getMovesFromConsole($board,@moves); }
    };
    
    bless $self;
    return $self;
}

sub eventHandler {
    my $self = {
        playerTurn => sub { 
            my ($whichTurn, $currentPlayer, $board, $color) = @_;
            print "Turn $whichTurn: Player $currentPlayer ($color)\n";
        },
        gameFinished => sub {
            my ($whichTurn, $winningPlayer) = @_;
            print "Player $winningPlayer wins on turn $whichTurn\n";
        }
    };
    
    bless $self;
    return $self;
}

sub getMovesFromConsole {
    my ($board, @moves) = @_;
    
    print $board->toString() . "\n";
    
    for (my $i = 0; $i < scalar @moves; $i++) {
        print "$i : " . $moves[$i]->toString() . "\n";
    }
    
    while (1) { 
        print "Enter choice: ";
        my $choice = int(<STDIN>);
        if ($choice < 0 || $choice >= scalar @moves) { 
            print "Invalid choice $choice\n";
            next;
        }
        return $moves[$choice];
    }
}

1;
