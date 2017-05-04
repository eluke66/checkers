package Checkers::Coordinate;

require Exporter;

our @ISA    = qw( Exporter );
our @EXPORT = qw();

sub new {
  my ($class, $row, $col) = @_; 
  
  my $self = {};
  bless $self, $class;
  
  $self->{row} = $row;
  $self->{col} = $col;
  return $self;
}

sub asArray {
    my $self = shift;
    my @rowcol = ($self->{row}, $self->{col});
    
    return @rowcol;
}

sub equals {
    my ($self,$other) = @_;
    
    return $self->{row} == $other->{row} and $self->{col} == $other->{col};
}

sub extending {
    my ($c1, $c2) = @_;
    
    my $newRow = ($c2->{row}-$c1->{row}) + $c2->{row};
    my $newCol = ($c2->{col}-$c1->{col}) + $c2->{col};
        
    return Checkers::Coordinate->new($newRow, $newCol);
}

1;
