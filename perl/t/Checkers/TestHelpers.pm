package Checkers::TestHelpers;

use Test::More;
use Checkers::Board;
use Checkers::SinglePiece;
use Checkers::Coordinate;
use Checkers::Color;

use strict;
use warnings;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw( blackPieceAt redPieceAt assertNoRedPieces assertNoPieceAt assertPieceIsBlack assertPieceIsRed );

sub blackPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::SinglePiece->new(BLACK, FORWARD), Checkers::Coordinate->new($row,$col))   
}
sub redPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::SinglePiece->new(RED, BACKWARDS), Checkers::Coordinate->new($row,$col))   
}

sub assertNoRedPieces {
    my ($board) = @_;
    
    is (scalar $board->getPiecesForColor(RED), 0, "Should have no red pieces");
}

sub assertNoPieceAt {
    my ($board, $row, $col) = @_;
    
    my $piece = $board->getPieceAt(Checkers::Coordinate->new($row,$col));
    
    is ($piece, undef, "No piece");
}

sub assertPieceIsBlack {
    my ($board, $row, $col) = @_;
    my $piece = $board->getPieceAt(Checkers::Coordinate->new($row,$col));
 
    ok( defined $piece, "Piece is defined" );
    is( $piece->{color}, BLACK, "Piece at $row, $col is black" );
    return $piece;
}

sub assertPieceIsRed {
    my ($board, $row, $col) = @_;
    my $piece = $board->getPieceAt(Checkers::Coordinate->new($row,$col));
 
    ok( defined $piece, "Piece is defined" );
    is( $piece->{color}, RED, "Piece at $row, $col is red" );
    return $piece;
}

1;
