package Checkers::Game;

use strict; 
use warnings;
use Checkers::Color;
use Checkers::SinglePiece;
require Exporter;

our @ISA = qw(Exporter);
our @EXPORT_OK   = qw(play);

use constant NUM_PIECES_PER_PLAYER => 12;

sub putPiecesOnTheBoard {
    my $board = shift;
    
    my $piecesPerRow = $board->size()/2;
    my $rows = int(NUM_PIECES_PER_PLAYER / $piecesPerRow);
        
    if ($piecesPerRow * $rows != NUM_PIECES_PER_PLAYER) {
        die "Cannot fit " . NUM_PIECES_PER_PLAYER . " onto a board of size " . $board->size();
    }

    foreach my $row (0..$rows) {
        my $colStart = $row % 2;
        for (my $col = $colStart; $col < $board->size(); $col += 2) {
            my $piece = SinglePiece->new(BLACK, FORWARD);
            $board->placePieceAt($piece, Coordinate->new($row,$col));
        }
    }
    foreach my $row (0..$rows) {
        my $thisRow = $board->size() - $row - 1;
        my $colStart = $thisRow % 2;
        for (my $col = $colStart; $col < $board->size(); $col += 2) {
            my $piece = SinglePiece->new(RED, BACKWARDS);
            $board->placePieceAt($piece, Coordinate->new($thisRow,$col));
        }
    }
}

sub play {
	my ($board, $player1, $player2, $rules, $eventHandler) = @_;

	my ($whichPlayer,$whichTurn) = (0,0);
	my @players = ( [$player1, BLACK] , [$player2, RED]);

	putPiecesOnTheBoard($board);

	while (1) {
		my ($currentPlayer,$color) = $players[$whichPlayer];
		$eventHandler->{playerTurn}->($whichTurn, $currentPlayer, $board, $color) if $eventHandler;
		
		my @moves = $rules->getMoveForColor($color, $board);
		last if scalar @moves == 0;
		
		my $move = $currentPlayer->selectMove(\@moves, $board);
		$move->execute();
		
		$whichPlayer = ($whichPlayer+1)%2;
		$whichTurn += 1;
	}
	
	my ($winningPlayer,$winningColor) = $players[($whichPlayer+1)%2];
	$eventHandler->{gameFinished}->($whichTurn, $winningPlayer) if $eventHandler;

    return $winningPlayer
}


1;
