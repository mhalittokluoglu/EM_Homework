clear;
close all;
ep_1 = 1;
ep_2 = 4;
ep_3 = 1;

mu_1 = 1;
mu_2 = 1;
mu_3 = 1;

sigma_1 = 0;
sigma_2 = 0;
sigma_3 = 0;


xcenter = 100;
E0 = 1;
Z0 = 120*pi;
delta_x = 1*10^-3;

c = 3*10^8;
delta_t = 0.5*delta_x/c;
% w = 0.001/(2*E0*delta_x);
f = 10;
w = 2*pi*f;
n = 1:512;

e0 = 8.854187817 * 10^(-12);
ep = zeros(1,512);
ep(1:250) = ep_1*e0;
ep(251:309) = ep_2*e0;
ep(310:512) = ep_3*e0;

mu0 = 4*pi*10^(-7);
mu = zeros(1,512);
mu(1:250) = mu_1*mu0;
mu(251:309) = mu_2*mu0;
mu(310:512) = mu_3*mu0;

sigma = zeros(1,512);
sigma(1:250) = sigma_1;
sigma(251:309) = sigma_2;
sigma(310:512) = sigma_3;

xp = xcenter*delta_x;

Ey = zeros(1,512);
Hz = zeros(1,512);

for i = 1:512
  Ey(i) = E0*exp(log(0.001)*((i-xp/delta_x)/w)^2);
  Hz(i) = E0/Z0*exp(log(0.001)*((i-xp/delta_x + 1/4)/w)^2);
end

while 1
  for i = 2:511
    Hz(i) = Hz(i) - (Ey(i+1)-Ey(i))*delta_t/(delta_x*mu(i));
    Ey(i) = ep(i)*Ey(i)/(ep(i)+delta_t*sigma(i)) - (Hz(i)-Hz(i-1))*delta_t/(delta_x*(ep(i)+delta_t*sigma(i)));
    end
  plot(n,Ey);
  line([250 250],[-10 10]);
  line([309 309],[-10 10]);
  ylim([-2 2]);
  xlim([0 512]);
  pause(0.003);
end