% Converted from PostScript(TM) to MetaPost by pstoedit
% MetaPost backend contributed by Scott Pakin <scott+ps2ed_AT_pakin.org>
% pstoedit is Copyright (C) 1993 - 2014 Wolfgang Glunz <wglunz35_AT_pstoedit.net>

% Generate structured PostScript
prologues := 1;

% Display a given string with its *baseline* at a given location
% and with a given rotation angle
vardef showtext(expr origin)(expr angle)(expr string) =
  draw string infont defaultfont scaled defaultscale
    rotated angle shifted origin;
enddef;

beginfig(1);
linecap := butt;
linejoin := mitered;
fill (394.687988,411.277008)--(394.687988,403.121002)--(402.843994,403.121002)
	--(402.843994,400.621002)--(394.687988,400.621002)--(394.687988,392.464996)
	--(392.234009,392.464996)--(392.234009,400.621002)--(384.062988,400.621002)
	--(384.062988,403.121002)--(392.234009,403.121002)--(392.234009,411.277008)
	--cycle;
fill (394.687988,411.277008)--cycle;
pickup pencircle scaled 0.750000bp;
draw (394.687988,411.277008)--(394.687988,403.121002)--(402.843994,403.121002)
	--(402.843994,400.621002)--(394.687988,400.621002)--(394.687988,392.464996)
	--(392.234009,392.464996)--(392.234009,400.621002)--(384.062988,400.621002)
	--(384.062988,403.121002)--(392.234009,403.121002)--(392.234009,411.277008)
	--cycle;
draw (394.687988,411.277008);
pickup pencircle scaled 1.333610bp;
draw (407.531006,401.867004)..controls (407.531006,394.097992) and (401.230011,387.796997)..(393.460999,387.796997)
	..controls (385.687988,387.796997) and (379.390991,394.097992)..(379.390991,401.867004)
	..controls (379.390991,409.636993) and (385.687988,415.937988)..(393.460999,415.937988)
	..controls (401.230011,415.937988) and (407.531006,409.636993)..(407.531006,401.867004)
	--cycle;
draw (407.531006,401.867004);
endfig;
end
