package Checkers::MoveRules;

use strict;
use warnings;
use Checkers::Move;
use Data::Dumper;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw(computeSimpleMoves);

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

sub computeSimpleMoves {
    my ($board, $piece, $coordinate, $coordProducer) = @_;
    
    my @coords = $coordProducer->($coordinate);
    my $isValid = sub { my $c = shift; return ($board->isValidPosition($c) and not defined $board->getPieceAt($c)); };
    my $toMove = sub { my $c = shift; return Checkers::Move::simpleMove($board, $piece, $coordinate, $c); };
    
    return grepAndMap($isValid, $toMove, @coords);
    #my @moves = ();
    # This should be grep/map, but for some reason it's not working
    #foreach my $coord (@coords) { 
    #    next unless $isValid->($coord);
    #    push @moves, $toMove->($coord);
    #}
    #return @moves;
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
    # TODO
    
    return @incomingMoves;
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
