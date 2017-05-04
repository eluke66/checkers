package Checkers::Board;

use strict; 
use warnings;
use Checkers::Color;
use Checkers::SinglePiece;
require Exporter;

our @ISA = qw(Exporter);
our @EXPORT_OK   = qw(dump);

use Data::Dumper;

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

sub size {
    my $self = shift;
    
    return scalar @{$self->{squares}};
}

sub placePieceAt {
    my ($self, $piece, $coordinate) = @_;
    
    my $placedPiece = {
        piece => $piece,
        coordinate => $coordinate,
        getSimpleMoves => sub { my ($board) = @_; return $piece->getSimpleMoves($coordinate, $board); },
        getJumpMoves => sub { my ($board) = @_; return $piece->getJumpMoves($coordinate, $board); },
        color => $piece->{color}
    };
    bless $placedPiece;
    $self->{squares}[$coordinate->{row}][$coordinate->{col}] = $placedPiece;
    return $placedPiece;
}

sub getPieceAt {
    my ($self, $coord) = @_;
    
    return $self->{squares}[$coord->{row}][$coord->{col}];
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

sub dump {
    my $self = shift;
    
    print Dumper($self) . "\n";
    
    my $firstRow = $self->{squares}[0];
    print "FIRST ROW IS " . Dumper($firstRow) . "\n";
    my @fr = @{$firstRow};
   
    print $self->{squares}[0][1];
}

1;
