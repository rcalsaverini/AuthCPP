set term jpeg
set output "foo.jpg"
set dgrid3d 100,100
set pm3d map
set palette color rgbformulae 3,5,5

splot "foo" u 1:2:3
