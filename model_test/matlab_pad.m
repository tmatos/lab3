% meu filtro fir pronto, ordem 197
h = [ 83 -25 -25 -26 -27 -28 -26 -22 -16 -8 2 13 22 30 34 33 28 19 6 -9 -24 -38 -47 -52 -50 -41 -26 -6 16 38 57 70 75 70 55 32 3 -29 -60 -85 -101 -105 -96 -73 -39 3 48 90 123 143 145 129 95 45 -14 -76 -133 -177 -201 -201 -174 -123 -51 34 121 199 258 289 284 241 163 56 -69 -197 -312 -397 -439 -427 -357 -232 -59 143 355 549 699 778 765 644 408 62 -383 -902 -1465 -2035 -2572 -3037 -3398 -3625 29065 -3625 -3398 -3037 -2572 -2035 -1465 -902 -383 62 408 644 765 778 699 549 355 143 -59 -232 -357 -427 -439 -397 -312 -197 -69 56 163 241 284 289 258 199 121 34 -51 -123 -174 -201 -201 -177 -133 -76 -14 45 95 129 145 143 123 90 48 3 -39 -73 -96 -105 -101 -85 -60 -29 3 32 55 70 75 70 57 38 16 -6 -26 -41 -50 -52 -47 -38 -24 -9 6 19 28 33 34 30 22 13 2 -8 -16 -22 -26 -28 -27 -26 -25 -25 83 ]

Fsam = 8000 

% filtro fir metodo kaiser
[n, w, beta, ftype] = kaiserord ([400, 500], [0, 1], [0.1, 0.1], 8000);
b = fir1 (n, w, kaiser (n+1, beta), ftype, "noscale");
freqz (b, 1, [], 8000);

% Create a 5 seconds signal with 3 components:
% a 1 Hz and a 200 Hz sinusoidal component and some gaussian noise.
t=0:1/Fsam:1;
input = sin(2*pi*300*t) + sin(2*pi*700*t) + randn(size(t));

Fsam = 8000 
t=0:1/Fsam:1;
input = sin(2*pi*150*t) + sin(2*pi*550*t);

plot(abs(fft(input)))

inputq = round(input * 2^13 );

fd = fopen("2sine.dat","w")
fprintf(fd, "%d ", inputq)
fclose(fd)

out = filter2(h,inputq);

plot(abs(fft(out)))
%ou
plot( 20*log10( abs( fft(h)(1:4000) ) ) )

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Fsam = 8000;
t = 0:1/Fsam:1;
input = sin(2*pi*100*t) + sin(2*pi*1000*t) + sin(2*pi*3000*t);

plot( abs( fft(input)(1:4000) ) )

inputq = round(input * 2^13 );

fd = fopen("3sine.dat","w");
fprintf(fd, "%d ", inputq);
fclose(fd);

out = filter2(h,inputq);

plot(abs(fft(out)))
%ou
plot( 20*log10( abs( fft(h)(1:4000) ) ) )

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

plot( abs( fft(in)(1:4000) ) );
figure;
plot( abs( fft(out)(1:4000) ) );

plot( 20*log10( abs( fft(in)(1:4000) ) ) );
figure;
plot( 20*log10( abs( fft(out)(1:4000) ) ) );

soundsc(out, 8000, 16);

