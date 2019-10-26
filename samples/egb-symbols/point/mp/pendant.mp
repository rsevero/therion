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
pickup pencircle scaled 11.338600bp;
linecap := butt;
linejoin := mitered;
draw (161.371002,550.137024)--(356.835999,550.137024);
pickup pencircle scaled 3.401580bp;
draw (257.589996,550.895020)--(257.589996,444.828003);
pickup pencircle scaled 2.834650bp;
draw (308.347992,547.867004)--(308.347992,471.347992);
pickup pencircle scaled 3.968500bp;
draw (193.949005,547.867004)--(193.949005,425.890991);
pickup pencircle scaled 2.125980bp;
draw (221.223007,549.379028)--(221.223007,510.742004);
endfig;
end
