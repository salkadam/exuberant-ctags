=pod
sample codes from:
  http://docs.parrot.org/parrot/latest/html/index.html
=cut

.sub 'name'
.end

.sub 'main' :main
.end

.sub 'id' :init :load
.end

.sub 'foo' :subid('barsouter')
.end
