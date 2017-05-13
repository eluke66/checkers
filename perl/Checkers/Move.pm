package Checkers::Move;

use strict; 
use warnings;
use Data::Dumper;
use Checkers::KingPiece;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw(simpleMove);

sub moveAndKingPiece {
    my ($board, $piece, $dest) = @_;
    
    if ($board->isFinalRowForPiece($piece, $dest) and $piece->{canBeKinged}) {
        $board->placePieceAt(Checkers::KingPiece->new($piece->{color}), $dest);
    }
    else {
        $board->placePieceAt($piece, $dest);
    }
}

sub execSimpleMove {
    my $self = shift;
    
    $self->{board}->removePieceAt( $self->{moveFrom} );
    moveAndKingPiece($self->{board}, $self->{piece}, $self->{moveTo});
}

sub unexecSimpleMove {
    my $self = shift;
    
    $self->{board}->removePieceAt( $self->{moveTo} );
    $self->{board}->placePieceAt($self->{piece}, $self->{moveFrom});
}

sub simpleMove {
    my ($board, $piece, $moveFrom, $moveTo) = @_;
    
    my $move = {
        piece => $piece,
        moveFrom => $moveFrom,
        moveTo => $moveTo,
        board => $board
    };
    bless $move;
    $move->{execute} = sub { $move->execSimpleMove(); };
    $move->{unExecute} = sub { $move->unexecSimpleMove(); };
    
    return $move;
}

sub execJumpMove {
    my $self = shift;
    
    if (not defined $self->{removedPiece}) {
        $self->{removedPiece} = $self->{board}->getPieceAt($self->{existingPieceLocation});
        $self->{board}->removePieceAt($self->{moveFrom});
        moveAndKingPiece($self->{board}, $self->{piece}, $self->{moveTo});
        $self->{board}->removePieceAt($self->{existingPieceLocation});
        
    }
    else {
        die "Trying to re-execute jump move: " . Dumper($self);
    }
}

sub unexecJumpMove {
    my $self = shift;
    
    if (defined $self->{removedPiece}) {
        $self->{board}->removePieceAt($self->{moveTo});
        $self->{board}->placePieceAt($self->{piece}, $self->{moveFrom});
        $self->{board}->placePieceAt($self->{removedPiece}, $self->{existingPieceLocation});
        $self->{removedPiece} = undef;
    }
    else {
        die "Trying to unexecute jump move that has not been executed: " . Dumper($self);
    }
}

sub jumpMove {
    my ($board, $piece, $moveFrom, $moveTo) = @_;
    
    my $move = {
        piece => $piece,
        moveFrom => $moveFrom,
        existingPieceLocation => $moveTo,
        moveTo => Checkers::Coordinate::extending($moveFrom, $moveTo),
        board => $board,
        removedPiece => undef
    };
    bless $move;
    
    $move->{execute} = sub { $move->execJumpMove(); };
    $move->{unExecute} = sub { $move->unexecJumpMove(); };
    return $move;
}


sub execMultiJumpMove {
    my $self = shift;
    
    $self->{previousMove}->{execute}();
    $self->execJumpMove();
}

sub unexecMultiJumpMove {
    my $self = shift;
    
    $self->unexecJumpMove();
    $self->{previousMove}->{unExecute}();
}

sub multiJumpMove {
    my ($board, $piece, $moveFrom, $moveTo, $previousMove) = @_;
    
    my $move = {
        piece => $piece,
        moveFrom => $moveFrom,
        existingPieceLocation => $moveTo,
        moveTo => Checkers::Coordinate::extending($moveFrom, $moveTo),
        board => $board,
        removedPiece => undef,
        previousMove => $previousMove
    };
    bless $move;
    
    $move->{execute} = sub { $move->execMultiJumpMove(); };
    $move->{unExecute} = sub { $move->unexecMultiJumpMove(); };
    return $move;
}


1;
