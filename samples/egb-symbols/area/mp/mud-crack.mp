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
pickup pencircle scaled 0.749999bp;
linecap := butt;
linejoin := mitered;
draw (172.531006,466.222992)--(225.104996,425.453003)--(271.855011,440.605011)
	--(323.921997,390.414001)--(346.839996,423.699005)--(414.757996,363.097992)
	--(390.753998,275.722992)--(414.515991,281.648010)--(438.726990,322.277008);
draw (244.710999,252.141006)--(232.354996,272.496002)--(308.351990,293.101990)
	--(257.156006,310.019989)--(266.289001,357.613007)--(291.085999,380.539001)
	--(303.242004,428.855011)--(282.320007,477.753998)--(393.207001,502.281006)
	--(380.324005,518.754028);
draw (172.531006,466.222992)--(244.710999,518.554993);
draw (173.410004,322.277008)--(205.151993,357.402008)--(244.710999,322.277008)
	--(266.289001,357.613007);
draw (380.324005,252.992004)--(364.523010,292.832001)--(380.324005,322.277008)
	--(346.839996,423.699005)--(417.410004,491.484009)--(393.207001,502.281006);
draw (437.769989,466.222992)--(417.410004,491.484009)--(380.324005,392.070007);
endfig;
end
