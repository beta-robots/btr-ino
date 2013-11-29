// CLEAR ALL **********************************************************************
xdel(winsid());
clear;

// PARAMS **********************************************************************
remin = 300; //min eTape resistance [ohm]
remax = 1500; //max eTape resistance [ohm]
vcc = 5; //power voltage
rd = [0:10:2000]; //resistor at divider

//voltage divider range function
vdmax = vcc*remax./(remax+rd);
vdmin = vcc*remin./(remin+rd);
vdrange = vdmax - vdmin;

//plot
fig1 = figure();
fig1.background = 8;
plot(rd,vdrange,"blue");
plot(rd,vdmax,"red");
plot(rd,vdmin,"green");
plot(rd,3.3,"black");
ah = gca();
ah.auto_scale = "off";
ah.tight_limits = "on";
ah.data_bounds = [0,0;2000,5];
ah.x_label.text = "$R_d\ [\Omega]$";
ah.x_label.font_size = 4;
ah.y_label.text = "$[V]$";
ah.y_label.font_size = 4;
lh =legend(["$\Delta V_d$";"$V_{d,max}$";"$V_{d,min}$"],1);
lh.font_size = 3;
title("Voltage divider to measure eTape liquid level");
ah.title.font_size = 4;

