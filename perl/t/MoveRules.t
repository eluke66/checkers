use Test::More;
use Checkers::Board;
use Checkers::Coordinate;
use Checkers::MoveRules;
use Checkers::Color;

use lib 't/';
use Checkers::TestHelpers;

use strict;
use warnings;

subtest "If capturing moves are available they must be picked for simple jumps" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0, 2);
    redPieceAt($board, 1, 1);
    
    my @moves = getMovesForColor($board, BLACK);
    
    is(scalar @moves, 1, "Should have a single move");
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
};

subtest "If capturing moves are available they must be picked for multi jumps" => sub { 
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0, 2);
    redPieceAt($board, 1, 3);
    redPieceAt($board, 3, 5);
    
    my @moves = getMovesForColor($board, BLACK);
    
    is(scalar @moves, 1, "Should have a single move");
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertPieceIsBlack($board,4,6);
};

done_testing();

