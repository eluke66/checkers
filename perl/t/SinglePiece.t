use Test::More;
use Checkers::Board;
use Checkers::SinglePiece;
use Checkers::Coordinate;
use Checkers::Color;
use Data::Dumper;

use lib 't/';
use Checkers::TestHelpers;

use strict;
use warnings;

subtest "Single pieces cannot jump when blocked" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,0);
    redPieceAt($board, 1,1);
    redPieceAt($board, 2,2);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    ok(scalar @moves == 0, "no moves allowed");
};

subtest "Single pieces cannot jump their own man" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,0);
    blackPieceAt($board, 1,1);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    ok(scalar @moves == 0, "no moves allowed");
};

subtest "Single pieces have two forward moves" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,2);

    my @moves = $blackPiece->{getSimpleMoves}($board);
    ok(scalar @moves == 2, "should have 2 moves");
    foreach my $move (@moves) {
        ok( $move->{moveTo}->equals(Checkers::Coordinate->new(1,1)) or $move->{moveTo}->equals(Checkers::Coordinate->new(1,3)), "moves should end at the right spots" );
    }
    
    my $redPiece = redPieceAt($board, 4, 2);
    @moves = $redPiece->{getSimpleMoves}($board);
    ok(scalar @moves == 2, "should have 2 moves");

    foreach my $move (@moves) {
        ok( $move->{moveTo}->equals(Checkers::Coordinate->new(3,1)) or $move->{moveTo}->equals(Checkers::Coordinate->new(3,3)), "moves should end at the right spots" );
    }
};

subtest "Single pieces cannot move off the board or when blocked" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0, 0);
    redPieceAt($board, 1,1);
    
    my @moves = $blackPiece->{getSimpleMoves}($board);

    ok(scalar @moves == 0, "no moves allowed");
   
};

subtest "Single pieces can jump once and that piece is removed" => sub { 
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0, 0);
    redPieceAt($board, 1,1);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    
    ok(scalar @moves == 1);
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,0,0);
    assertPieceIsBlack($board,2,2);
};

subtest "Single pieces can jump more than once and those pieces are removed" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0, 0);
    redPieceAt($board, 1,1);
    redPieceAt($board, 3,3);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    
    ok(scalar @moves == 1);
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,0,0);
    assertPieceIsBlack($board,4,4);
};

subtest "Single pieces can have two forward jumps" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,2);
    redPieceAt($board, 1,1);
    redPieceAt($board, 1,3);

    my @moves = $blackPiece->{getJumpMoves}($board);
    ok(scalar @moves == 2, "should have 2 moves");
    foreach my $move (@moves) {
        ok( $move->{moveTo}->equals(Checkers::Coordinate->new(2,0)) or $move->{moveTo}->equals(Checkers::Coordinate->new(2,4)), "moves should end at the right spots" );
    }
};

subtest "Single pieces can have multiple forward multi-jumps" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,2);
    redPieceAt($board, 1,1);
    redPieceAt($board, 1,3);
    redPieceAt($board, 3,5);

    my @moves = $blackPiece->{getJumpMoves}($board);
    ok(scalar @moves == 2, "should have 2 moves");
    foreach my $move (@moves) {
        ok( $move->{moveTo}->equals(Checkers::Coordinate->new(2,0)) or $move->{moveTo}->equals(Checkers::Coordinate->new(4,6)), "moves should end at the right spots" );
    }
};

subtest "When single piece moves into the back row it is kinged" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, $board->size()-2, 0);
    
    my @moves = $blackPiece->{getSimpleMoves}($board);
        
    ok(scalar @moves == 1, "should have 1 move");
    $moves[0]->{execute}();
    
    my $newPiece = assertPieceIsBlack($board,$board->size()-1,1);
    ok( $newPiece->{canBeKinged} == 0 );
};


subtest "When single piece jumps into the back row it is kinged" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, $board->size()-3, 1);
    redPieceAt($board, $board->size()-2,2);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
        
    ok(scalar @moves == 1, "should have 1 move");
    $moves[0]->{execute}();
    
    my $newPiece = assertPieceIsBlack($board,$board->size()-1,3);
    ok( $newPiece->{canBeKinged} == 0 );
};

done_testing();

