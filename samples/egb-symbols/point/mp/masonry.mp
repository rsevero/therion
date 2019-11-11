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
fill (247.164001,458.144989)--(317.664001,458.144989)--(317.664001,426.644989)
	--(247.164001,426.644989)--cycle;
fill (286.914001,416.894989)--(358.164001,416.894989)--(358.164001,385.394989)
	--(286.914001,385.394989)--cycle;
fill (206.664001,416.894989)--(277.914001,416.894989)--(277.914001,385.394989)
	--(206.664001,385.394989)--cycle;
fill (327.414001,375.644989)--(397.914001,375.644989)--(397.914001,344.144989)
	--(327.414001,344.144989)--cycle;
fill (247.164001,375.644989)--(317.664001,375.644989)--(317.664001,344.144989)
	--(247.164001,344.144989)--cycle;
fill (327.414001,458.195007)--(397.914001,458.195007)--(397.914001,426.695007)
	--(327.414001,426.695007)--cycle;
fill (286.914001,499.234009)--(358.164001,499.234009)--(358.164001,467.734009)
	--(286.914001,467.734009)--cycle;
endfig;
end
