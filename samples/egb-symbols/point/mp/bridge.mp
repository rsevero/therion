% Converted from PostScript(TM) to MetaPost by pstoedit
% MetaPost backend contributed by Scott Pakin <scott+ps2ed_AT_pakin.org>
% pstoedit is Copyright (C) 1993 - 2019 Wolfgang Glunz <wglunz35_AT_pstoedit.net>

% Generate structured PostScript
prologues := 1;

% Display a given string with its *baseline* at a given location
% and with a given rotation angle
vardef showtext(expr origin)(expr angle)(expr string) =
  draw string infont defaultfont scaled defaultscale
    rotated angle shifted origin;
enddef;

beginfig(1);
pickup pencircle scaled 16.908701bp;
linecap := butt;
linejoin := mitered;
draw (580.965027,551.184021)--(522.101990,444.898010)--(126.344002,444.898010)
	--(67.480499,551.184021);
draw (580.965027,239.464996)--(522.101990,345.750000)--(126.344002,345.750000)
	--(67.480499,239.464996);
endfig;
end
