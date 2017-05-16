use Test::More;
use Checkers::Board;
use Checkers::Coordinate;
use Checkers::Game;
use Checkers::Color;
use Checkers::Move;
use Checkers::SinglePiece;
use Data::Dumper;
use strict;
use warnings;

use lib 't/';
use Checkers::TestHelpers;

subtest "Each player starts with 12 pieces" => sub {
    my $board = Checkers::Board->new;
    Checkers::Game::putPiecesOnTheBoard($board);
    
    is( scalar $board->getPiecesForColor(BLACK), 12, "Black must have 12 pieces");
    is( scalar $board->getPiecesForColor(RED), 12, "Red must have 12 pieces");
};

subtest "Closest left square to each player starts with a piece" => sub {
    my $board = Checkers::Board->new;
    Checkers::Game::putPiecesOnTheBoard($board);
    my $end = $board->size()-1;
    
    assertPieceIsBlack( $board, 0, 0 );
    assertPieceIsRed( $board, $end, $end );
};

subtest "Board is 8x8" => sub {
    my $board = Checkers::Board->new;
    
    is( $board->size(), 8, "Board must be of size 8" );
};

subtest "Black moves first" => sub {
    my $board = Checkers::Board->new;
    my ($player1, $player2) = undef;  # Dummy values
    my $getMovesForColor = sub { my ($board,$color) = @_; ok( $color == BLACK ); my @moves; return @moves;};
    
    Checkers::Game::play($board, $player1, $player2, $getMovesForColor, undef);
};

subtest "Red moves after black" => sub {
    my $board = Checkers::Board->new;
    my $player1 = { selectMove => sub { my ($b,@m) = @_; return $m[0]; } }; bless $player1;
    my $player2 = undef;    
    my $from = Checkers::Coordinate->new(2,0);
    my $to = Checkers::Coordinate->new(3,1);
    my $blackMoves = [ Checkers::Move::simpleMove( $board, Checkers::SinglePiece->new(BLACK, FORWARD), $from, $to ) ];
    my $redMoves = [];
    my %movesPerColor = ( &BLACK => $blackMoves, &RED => $redMoves );
    my $getMovesForColor = sub { 
        my ($board,$color) = @_; 

        ok( exists $movesPerColor{$color}, "Move for $color exists" );
        my @moves = @{$movesPerColor{$color}};

        delete $movesPerColor{$color};
        return @moves;
    };
    
    Checkers::Game::play($board, $player1, $player2, $getMovesForColor, undef);

    is( scalar keys %movesPerColor, 0, "All moves should be consumed" );
};

subtest "When a player cannot move the other player wins" => sub {
    my $board = Checkers::Board->new;
    my ($player1, $player2) = (1,2);  # Dummy values
    my $getMovesForColor = sub { my @moves; return @moves;};
    
    my $winner = Checkers::Game::play($board, $player1, $player2, $getMovesForColor, undef);

    is ( $player2, $winner, "Player 2 should win" );
};

done_testing();

