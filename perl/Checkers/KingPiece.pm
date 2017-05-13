package Checkers::KingPiece;

use strict;
use warnings;
use Checkers::MoveRules;
use Checkers::Coordinate;
use Data::Dumper;
use Carp;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw( );


sub new {
  my ($class, $color) = @_;
  
  my $self = {};
  bless $self, $class;
  
  $self->{color} = $color;
  $self->{coordProducer} = sub { my $coord = shift; return getCoords($self->{direction}, $coord); };
  $self->{canBeKinged} = 0;
  
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
    confess "Needed a coord, got $coord" unless $coord->isa("Checkers::Coordinate");
    
    my $row = $coord->{row};
    my @coords = ( 
        Checkers::Coordinate->new($coord->{row} + 1, $coord->{col} + 1), 
        Checkers::Coordinate->new($coord->{row} + 1, $coord->{col} - 1),
        Checkers::Coordinate->new($coord->{row} - 1, $coord->{col} + 1), 
        Checkers::Coordinate->new($coord->{row} - 1, $coord->{col} - 1) );
    return @coords;
}

1;
