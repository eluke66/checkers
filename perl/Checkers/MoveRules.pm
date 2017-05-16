package Checkers::MoveRules;

use strict;
use warnings;
use Checkers::Move;
use Checkers::Board;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw(computeSimpleMoves computeJumpMoves getMovesForColor);

sub grepAndMap {
    my ($grepRef, $mapRef, @items) = @_;
    
    my @outputItems = ();
    
    # This should be grep/map, but for some reason it's not working
    foreach my $item (@items) { 
        next unless $grepRef->($item);
        push @outputItems, $mapRef->($item);
    }
    return @outputItems;
}

sub getMovesForColor {
    my ($board, $color) = @_;
    
    my @pieces = $board->getPiecesForColor($color);
    
    my @jumps = map { $_->{getJumpMoves}($board) } @pieces;
    
    # Do jumps if available   
    return @jumps if scalar @jumps > 0;
        
    # Otherwise do simple moves.
    my @moves = map { $_->{getSimpleMoves}($board) } @pieces;
    return @moves;
}

sub computeSimpleMoves {
    my ($board, $piece, $coordinate, $coordProducer) = @_;
    
    my @coords = $coordProducer->($coordinate);
    my $isValid = sub { my $c = shift; return ($board->isValidPosition($c) and not defined $board->getPieceAt($c)); };
    my $toMove = sub { my $c = shift; return Checkers::Move::simpleMove($board, $piece, $coordinate, $c); };
    
    return grepAndMap($isValid, $toMove, @coords);
}

sub pieceIsJumpable {
    my ($board, $piece, $coordinate) = @_;
    
    my $boardPiece = $board->getPieceAt($coordinate);
    
    return (defined $boardPiece and $boardPiece->{color} != $piece->{color});
}

sub nextSpaceIsLandable {
    my ($board, $piece, $startCoordinate, $nextCoordinate) = @_;
    
    my $landingSpot = Checkers::Coordinate::extending($startCoordinate, $nextCoordinate);
    return ($board->isValidPosition($landingSpot) and not defined $board->getPieceAt($landingSpot));
}

sub searchJumps {
    my ($board, $piece, $coordProducer, @incomingMoves) = @_;
    
    my @finalMoves;
    
    foreach my $move (@incomingMoves) {
    
        # Let's assume we execute the move.
        $move->{execute}();

        # Get the next jump moves.
        my $nextCoordinate = $move->{moveTo};
        
        my $isValid = sub { my $c = shift; return ($board->isValidPosition($c) and pieceIsJumpable($board,$piece,$c) and nextSpaceIsLandable($board, $piece, $nextCoordinate, $c)); };
        my $toMove = sub { my $c = shift; return Checkers::Move::multiJumpMove($board, $piece, $nextCoordinate, $c, $move); };
       
        my @nextCoordinates = $coordProducer->($nextCoordinate);
        my @nextMovesForThisMove = grepAndMap($isValid, $toMove, @nextCoordinates);
        
        # And undo the move
        $move->{unExecute}();

        # If there are any next moves, then we replace this move with those moves AND THEIR CONTINUED MOVES
        if (scalar @nextMovesForThisMove > 0) {
            push @finalMoves, searchJumps($board, $piece, $coordProducer, @nextMovesForThisMove);
        }
        else {
            # Otherwise we don't have to jump more, and just add this move.
            push @finalMoves, $move
        }
    }
    return @finalMoves;
}

sub computeJumpMoves {
    my ($board, $piece, $coordinate, $coordProducer) = @_;
    
    my @coords = $coordProducer->($coordinate);
    my $isValid = sub { my $c = shift; return ($board->isValidPosition($c) and pieceIsJumpable($board,$piece,$c) and nextSpaceIsLandable($board, $piece, $coordinate, $c)); };
    my $toMove = sub { my $c = shift; return Checkers::Move::jumpMove($board, $piece, $coordinate, $c); };
   
   
    my @initialMoves = grepAndMap($isValid, $toMove, @coords);
    return searchJumps($board, $piece, $coordProducer, @initialMoves);
}

1;
