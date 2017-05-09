package Checkers::TestHelpers;

use Test::More;
use Checkers::Board;
use Checkers::SinglePiece;
use Checkers::Coordinate;
use Checkers::Color;
use Data::Dumper;
use strict;
use warnings;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw( blackPieceAt redPieceAt assertNoRedPieces assertNoPieceAt assertPieceIsBlack );

sub blackPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::SinglePiece->new(Checkers::Color::BLACK, FORWARD), Checkers::Coordinate->new($row,$col))   
}
sub redPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::SinglePiece->new(Checkers::Color::RED, BACKWARDS), Checkers::Coordinate->new($row,$col))   
}

sub assertNoRedPieces {
    my ($board) = @_;
    
    ok (scalar $board->getPiecesForColor(Checkers::Color::RED) == 0);
}

sub assertNoPieceAt {
    my ($board, $row, $col) = @_;
    
    my $piece = $board->getPieceAt(Checkers::Coordinate->new($row,$col));
    
    ok (not defined $piece);
}

sub assertPieceIsBlack {
    my ($board, $row, $col) = @_;
    my $piece = $board->getPieceAt(Checkers::Coordinate->new($row,$col));
 
    ok( defined $piece, "Piece is defined" );
    ok( $piece->{color} == Checkers::Color::BLACK, "Piece at $row, $col is black" );
    return $piece;
}

1;
