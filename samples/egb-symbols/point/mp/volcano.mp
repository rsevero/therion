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
pickup pencircle scaled 21.160601bp;
linecap := butt;
linejoin := beveled;
draw (36.671902,222.897995)--(169.684006,567.409973)..controls (177.815994,510.679993) and (212.089996,485.109009)..(265.714996,485.109009)
	..controls (319.335999,485.109009) and (353.609009,510.679993)..(361.742004,567.409973)
	--(494.753998,222.897995);
endfig;
end
