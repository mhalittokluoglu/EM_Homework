%{
        EEE456
ELECTROMAGNETIC MODELLING HOMEWORK - 1
GROUP #1

Lecturer: Prof. Dr. Erkan AFACAN

Students:
Onur AKSOY 161110004
Mine Nur ÖZER 161110057
Muhammed Halit TOKLUOĞLU 161110070
%}


clear;
close all;
%------Constants------
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

%---------------------

%Allocating an array of 512 elements for both Ey and Hz
Ey = zeros(1,512);
Hz = zeros(1,512);
xp = xcenter*delta_x;

%For excitation, Gaussian Pulse is used.
%Creating Gaussian Pulse
for i = 1:512
  Ey(i) = E0*exp(log(0.001)*((i-xp/delta_x)/w)^2);
  Hz(i) = E0/Z0*exp(log(0.001)*((i-xp/delta_x + 1/4)/w)^2);
end

%Applying formulas in lecture note of FDTD 5 (Week 7) in order to calculate Hz and Ey in interval [1,512]

temp = 0;
is_figure = figure;
while ishandle(is_figure)
  for i = 1:512
    if i == 1
      Hz(1) = Hz(i) - (Ey(2)-Ey(1))*delta_t/(delta_x*mu(1));
      Hz(2) = Hz(i) - (Ey(3)-Ey(2))*delta_t/(delta_x*mu(2));
      temp = Ey(2);
      Ey(2) = ep(2)*Ey(2)/(ep(i)+delta_t*sigma(i)) - (Hz(2)-Hz(1))*delta_t/(delta_x*(ep(2)+delta_t*sigma(2)));
      Ey(1) = temp - (Ey(2) - Ey(1))/3;
    elseif i == 2
      continue;
    elseif i == 511
      continue;
    elseif i == 512
      Hz(511) = Hz(511) - (Ey(512)-Ey(511))*delta_t/(delta_x*mu(511));
      temp = Ey(511);
      Ey(511) = ep(511)*Ey(511)/(ep(i)+delta_t*sigma(i)) - (Hz(511)-Hz(510))*delta_t/(delta_x*(ep(511)+delta_t*sigma(511)));
      Ey(512) = temp - (Ey(511) - Ey(512))/3;    
    else
      Hz(i) = Hz(i) - (Ey(i+1)-Ey(i))*delta_t/(delta_x*mu(i));
      Ey(i) = ep(i)*Ey(i)/(ep(i)+delta_t*sigma(i)) - (Hz(i)-Hz(i-1))*delta_t/(delta_x*(ep(i)+delta_t*sigma(i)));
    end
  end
  %Plotting
  plot(n,Ey);
  line([250 250],[-10 10]);
  line([309 309],[-10 10]);
  ylim([-2 2]);
  xlim([0 512]);
  pause(0.01);
end