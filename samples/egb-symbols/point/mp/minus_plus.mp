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
fill (482.812988,451.992004)--(482.812988,443.835999)--(490.968994,443.835999)
	--(490.968994,441.335999)--(482.812988,441.335999)--(482.812988,433.179993)
	--(480.359009,433.179993)--(480.359009,441.335999)--(472.187988,441.335999)
	--(472.187988,443.835999)--(480.359009,443.835999)--(480.359009,451.992004)
	--cycle;
fill (482.812988,451.992004)--cycle;
pickup pencircle scaled 0.750000bp;
draw (482.812988,451.992004)--(482.812988,443.835999)--(490.968994,443.835999)
	--(490.968994,441.335999)--(482.812988,441.335999)--(482.812988,433.179993)
	--(480.359009,433.179993)--(480.359009,441.335999)--(472.187988,441.335999)
	--(472.187988,443.835999)--(480.359009,443.835999)--(480.359009,451.992004)
	--cycle;
draw (482.812988,451.992004);
pickup pencircle scaled 0.000000bp;
fill (475.089996,425.414001)--(488.074005,425.414001)--(488.074005,421.460999)
	--(475.089996,421.460999)--cycle;
pickup pencircle scaled 1.332280bp;
draw (481.585999,412.011993)..controls (473.812988,412.011993) and (467.515991,418.312988)..(467.515991,426.082001)
	--(467.515991,442.582001)..controls (467.515991,450.351990) and (473.812988,456.652008)..(481.585999,456.652008)
	..controls (489.355011,456.652008) and (495.656006,450.351990)..(495.656006,442.582001)
	--(495.656006,426.082001)..controls (495.656006,418.312988) and (489.355011,412.011993)..(481.585999,412.011993)
	--cycle;
draw (481.585999,412.011993);
endfig;
end
