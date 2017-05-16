package Checkers::SinglePiece;

use strict;
use warnings;
use Checkers::MoveRules;
use Checkers::Coordinate;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw( FORWARD BACKWARDS );

use constant FORWARD => 1;
use constant BACKWARDS => -1;

sub new {
  my ($class, $color, $direction) = @_;
  
  my $self = {};
  bless $self, $class;
  
  $self->{color} = $color;
  $self->{direction} = $direction;
  $self->{coordProducer} = sub { my $coord = shift; return getCoords($self->{direction}, $coord); };
  $self->{canBeKinged} = 1;
  return $self;
}


sub getSimpleMoves {
    my ($self, $coordinate, $board) = @_;
    return Checkers::MoveRules::computeSimpleMoves($board, $self, $coordinate, $self->{coordProducer});
}

sub getJumpMoves {
    my ($self, $coordinate, $board) = @_;
    return Checkers::MoveRules::computeJumpMoves($board, $self, $coordinate, $self->{coordProducer});
}

sub getCoords { 
    my ($dir, $coord) = @_;
    
    my $row = $coord->{row};
    my @coords = ( 
        Checkers::Coordinate->new($coord->{row} + $dir, $coord->{col} + 1), 
        Checkers::Coordinate->new($coord->{row} + $dir, $coord->{col} - 1) );
    return @coords;
}

1;
