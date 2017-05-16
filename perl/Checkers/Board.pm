package Checkers::Board;

use strict; 
use warnings;
use Checkers::Color;
use Checkers::SinglePiece;
require Exporter;

our @ISA = qw(Exporter);
our @EXPORT = qw();

use constant SIZE => 8;

sub new {
  my $class = shift;
  
  my $self = {};
  bless $self, $class;
  
  my @squares = ();
  for (my $row = 0; $row < SIZE; $row++) {
    push @squares, [];
    for (my $col = 0; $col < SIZE; $col++) {
        push @{$squares[$row]}, undef;
    }
  }
  
  $self->{squares} = \@squares;
  return $self;
}

sub getPiecesForColor {
    my ($self, $color) = @_;
    
    my @pieces = ();
    for (my $row = 0; $row < SIZE; $row++) {
        for (my $col = 0; $col < SIZE; $col++) {
            my $piece = $self->{squares}[$row][$col];
            push @pieces, $piece if (defined $piece and $piece->{color} == $color);
        }
    }
    return @pieces;
}

sub isFinalRowForPiece {
    my ($self, $piece, $dest) = @_;
    
    my $color = $piece->{color};
    my $row = $dest->{row};
    
    return ( ($color == RED and $row == 0) or
             ($color == BLACK and $row == ($self->size()-1)) );
}


sub size {
    my $self = shift;
    
    return scalar @{$self->{squares}};
}

sub placePieceAt {
    my ($self, $piece, $coordinate) = @_;
    
    # Short circuit the operation if the piece is already a placedPiece
    if (not ($piece->isa("Checkers::SinglePiece") or $piece->isa("Checkers::KingPiece"))) {
        $self->{squares}[$coordinate->{row}][$coordinate->{col}] = $piece;
        $piece->{coordinate} = $coordinate;
        return $piece;
    }
    
    my $placedPiece = {
        piece => $piece,
        coordinate => $coordinate,
        getSimpleMoves => sub { my ($board) = @_; return $piece->getSimpleMoves($coordinate, $board); },
        getJumpMoves => sub { my ($board) = @_; return $piece->getJumpMoves($coordinate, $board); },
        color => $piece->{color},
        canBeKinged => $piece->{canBeKinged}
    };
    bless $placedPiece;
    $self->{squares}[$coordinate->{row}][$coordinate->{col}] = $placedPiece;
    return $placedPiece;
}

sub getPieceAt {
    my ($self, $coord) = @_;
    confess Dumper($coord) unless $coord->isa("Checkers::Coordinate");
    return $self->{squares}[$coord->{row}][$coord->{col}];
}

sub removePieceAt {
    my ($self, $coord) = @_;
    
    my $piece = $self->getPieceAt($coord);
    $self->{squares}[$coord->{row}][$coord->{col}] = undef;
    return $piece;
}


sub isEven { my $num = shift; return $num % 2 == 0; }

sub isUsableSquare {
    my ($row,$col) = @_;
    return ((isEven($row) and isEven($col)) or (not isEven($row) and not isEven($col)));
}

sub isValidPosition {
    my ($self, $coord) = @_;
    
    my ($row,$col) = $coord->asArray();
    return ($row >= 0 and $col >= 0 and
           $row < $self->size() and $col < $self->size() and
           isUsableSquare($row, $col));
}

sub toString {
    my $self = shift;
    my $s = "  ";
    my @nums = (0..$self->size()-1);
    
    $s .= join "", @nums;
    $s .= "\n";
    
	foreach my $row (@nums) {
	    $s .= "$row ";
	    foreach my $col (@nums) {
	        if (not isUsableSquare($row,$col)) {
	            $s .= "|";
	        }
	        else {
	            my $piece = $self->getPieceAt(Checkers::Coordinate->new($row, $col));
	            if (not defined $piece) {
	                $s .= "_";
	            }
	            else {
	                my $color = $piece->{color};
	                my $isKing = ($piece->{canBeKinged} == 0);
	                if ($color == Checkers::Color::BLACK) {
	                    if ($isKing) { $s .= "B"; }
	                    else { $s .= "b"; }
	                }
	                elsif ($color == Checkers::Color::RED) {
	                    if ($isKing) { $s .= "R"; }
	                    else { $s .= "r"; }
	                }
	                else { $s .= "?"; }
	            }
	        }
	    }
	    $s .= "\n";
	}
	
	return $s;
}

1;
