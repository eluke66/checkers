use Test::More;
use Checkers::Board;
use Checkers::SinglePiece;
use Checkers::Coordinate;
use Checkers::Color;
use Data::Dumper;
use strict;
use warnings;

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
    # TODO
}

sub assertNoPieceAt {
    my ($board, $row, $col) = @_;
    # TODO
}

sub assertPieceIsBlack {
    my ($board, $row, $col) = @_;
    my $piece = $board->getPieceAt($row,$col);
    
    ok( defined $piece );
    ok( $piece->color == Checkers::Color::BLACK );
}

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
    $moves[0]->execute();
    
    assertNoRedPieces($board);
    assertNoPieceAt($board,0,0);
    assertPieceIsBlack($board,2,2);
};
      
done_testing();

