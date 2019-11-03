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
pickup pencircle scaled 22.011000bp;
linecap := butt;
linejoin := mitered;
draw (476.980011,639.585999)..controls (471.453003,639.585999) and (422.562988,621.965027)..(428.812988,575.375000)
	..controls (434.457001,533.296997) and (506.785004,503.894989)..(505.894989,457.292999)
	..controls (502.128998,260.425995) and (383.000000,164.895004)..(289.718994,164.895004)
	..controls (196.440994,164.895004) and (77.312500,260.425995)..(73.546898,457.292999)
	..controls (72.656303,503.894989) and (144.983994,533.296997)..(150.628998,575.375000)
	..controls (156.875000,621.965027) and (107.987999,639.585999)..(102.460999,639.585999);
endfig;
end
