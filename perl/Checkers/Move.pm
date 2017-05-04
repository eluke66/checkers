package Checkers::Move;

use strict; 
use warnings;
use Data::Dumper;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw(simpleMove);

sub simpleMove {
    my ($board, $piece, $moveFrom, $moveTo) = @_;
    
    my $move = {
        piece => $piece,
        moveFrom => $moveFrom,
        moveTo => $moveTo,
        board => $board,
        # TODO
        execute => sub {},
        unExecute => sub {}
    };
    bless $move;
    
    return $move;
}

sub jumpMove {
    my ($board, $piece, $moveFrom, $moveTo) = @_;
    
    my $move = {
        piece => $piece,
        moveFrom => $moveFrom,
        existingPieceLocation => $moveTo,
        moveTo => Checkers::Coordinate::extending($moveFrom, $moveTo),
        board => $board,
        removedPiece => undef,
        # TODO
        execute => sub {},
        unExecute => sub {}
    };
    bless $move;
    
    return $move;
}


1;
