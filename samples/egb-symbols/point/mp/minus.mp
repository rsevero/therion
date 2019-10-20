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
fill (294.660004,411.578003)--(307.644989,411.578003)--(307.644989,407.625000)
	--(294.660004,407.625000)--cycle;
pickup pencircle scaled 1.285130bp;
draw (314.710999,409.601990)..controls (314.710999,402.113007) and (308.640991,396.042999)..(301.152008,396.042999)
	..controls (293.664001,396.042999) and (287.593994,402.113007)..(287.593994,409.601990)
	..controls (287.593994,417.089996) and (293.664001,423.160004)..(301.152008,423.160004)
	..controls (308.640991,423.160004) and (314.710999,417.089996)..(314.710999,409.601990)
	--cycle;
draw (314.710999,409.601990);
endfig;
end
