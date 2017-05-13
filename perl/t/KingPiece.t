use Test::More;
use Checkers::Board;
use Checkers::KingPiece;
use Checkers::Coordinate;
use Checkers::Color;
use Data::Dumper;
use strict;
use warnings;

use lib 't/';
use Checkers::TestHelpers qw(assertNoRedPieces assertNoPieceAt assertPieceIsBlack);

use strict;
use warnings;


sub blackPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::KingPiece->new(Checkers::Color::BLACK), Checkers::Coordinate->new($row,$col))   
}
sub redPieceAt {
    my ($board, $row, $col) = @_;
    return $board->placePieceAt(Checkers::KingPiece->new(Checkers::Color::RED), Checkers::Coordinate->new($row,$col))   
}

subtest "Kings can move forward and backwards" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 2, 2);
    
    my @moves = $blackPiece->{getSimpleMoves}($board);
    ok(scalar @moves == 4, "should have 4 moves");
    foreach my $move (@moves) {
        ok( 
            $move->{moveTo}->equals(Checkers::Coordinate->new(1,1)) or 
            $move->{moveTo}->equals(Checkers::Coordinate->new(1,3)) or
            $move->{moveTo}->equals(Checkers::Coordinate->new(3,1)) or 
            $move->{moveTo}->equals(Checkers::Coordinate->new(3,3)), "moves should end at the right spots for" );
    }
};

subtest "Kings cannot jump when blocked" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 0,0);
    redPieceAt($board, 1,1);
    redPieceAt($board, 2,2);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    ok(scalar @moves == 0, "no moves allowed");
};

subtest "Kings can jump forward once" => sub {
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

subtest "Kings can jump backwards once" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 2, 2);
    redPieceAt($board, 1,1);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    
    ok(scalar @moves == 1);
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,2,2);
    assertPieceIsBlack($board,0,0);
};

subtest "Kings can jump forwards then backwards" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 2, 0);
    redPieceAt($board, 1,1);
    redPieceAt($board, 1,3);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    
    ok(scalar @moves == 1);
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,2,0);
    assertPieceIsBlack($board,2,4);

};

subtest "Kings can jump backwards then forwards" => sub {
    my $board = Checkers::Board->new;
    my $blackPiece = blackPieceAt($board, 2, 4);
    redPieceAt($board, 1,1);
    redPieceAt($board, 1,3);
    
    my @moves = $blackPiece->{getJumpMoves}($board);
    
    ok(scalar @moves == 1);
    $moves[0]->{execute}();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,2,4);
    assertPieceIsBlack($board,2,0);
};

done_testing();
