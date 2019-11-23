from colormath.color_objects import sRGBColor, LabColor
from colormath.color_conversions import convert_color
from colormath.color_diff import delta_e_cie2000

color1_rgb = sRGBColor(0.0, 0.0, 0.5)
color2_rgb = sRGBColor(0.0, 0.0, 1.0)
color1_lab = convert_color(color1_rgb, LabColor)
color2_lab = convert_color(color2_rgb, LabColor)
delta_e = delta_e_cie2000(color1_lab, color2_lab);

print(delta_e)