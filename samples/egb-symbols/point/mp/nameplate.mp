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
pickup pencircle scaled 22.393700bp;
linecap := butt;
linejoin := mitered;
draw (77.027298,563.448975)--(505.574005,563.448975)--(505.574005,340.082001)
	--(77.027298,340.082001)--cycle;
pickup pencircle scaled 11.239400bp;
draw (208.195007,496.167999)--(422.667999,496.167999);
draw (117.796997,450.808990)--(358.480011,450.808990);
draw (264.453003,401.781006)--(470.472992,401.781006);
endfig;
end
