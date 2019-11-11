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
linecap := butt;
linejoin := mitered;
fill (203.082001,222.688004)..controls (199.026993,223.921997) and (194.871002,226.574005)..(192.328003,229.546997)
	--(193.651993,599.629028)..controls (201.710999,607.637024) and (213.699005,608.065979)..(222.128998,600.648010)
	..controls (228.453003,595.081970) and (228.901993,593.562988)..(229.332001,576.359009)
	--(229.707001,561.359009)--(356.457001,561.359009)--(356.832001,576.359009)
	..controls (357.261993,593.565979) and (357.710999,595.081970)..(364.046997,600.656006)
	..controls (372.730011,608.301025) and (386.246002,607.289001)..(393.832001,598.426025)
	--(393.832001,229.542999)..controls (383.945007,217.992004) and (365.015991,220.565994)..(358.605011,234.332001)
	..controls (356.976990,237.832001) and (356.847992,239.054993)..(356.839996,251.046997)
	--(356.832001,263.984009)--(229.332001,263.984009)--(229.324005,251.046997)
	..controls (229.320007,239.054993) and (229.190994,237.832001)..(227.559006,234.332001)
	..controls (223.401993,225.406006) and (211.979996,219.968994)..(203.082001,222.688004)
	--cycle;
fill (356.457001,349.109009)--(229.707001,349.109009)--(229.309006,306.734009)
	--(356.855011,306.734009)--cycle withcolor white;
fill (356.457001,433.109009)--(229.707001,433.109009)--(229.309006,392.234009)
	--(356.855011,392.234009)--cycle withcolor white;
fill (356.457001,518.609009)--(229.707001,518.609009)--(229.309006,476.234009)
	--(356.855011,476.234009)--cycle withcolor white;
endfig;
end
