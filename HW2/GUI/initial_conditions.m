globals;
ep_1 = 1;
ep_2 = 4;
ep_3 = 1;

mu_1 = 1;
mu_2 = 1;
mu_3 = 1;

sigma_1 = 0;
sigma_2 = 0;
sigma_3 = 0;


set(handles.edit1, 'String', num2str(mu_1));
set(handles.edit2, 'String', num2str(mu_2));
set(handles.edit3, 'String', num2str(mu_3));

set(handles.edit4, 'String', num2str(ep_1));
set(handles.edit5, 'String', num2str(ep_2));
set(handles.edit6, 'String', num2str(ep_3));

set(handles.edit7, 'String', num2str(sigma_1));
set(handles.edit8, 'String', num2str(sigma_2));
set(handles.edit9, 'String', num2str(sigma_3));

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

Z = Z0 * (mu_1/ep_1)^(1/2);

xp = xcenter*delta_x;

Ey = zeros(1,512);
Hz = zeros(1,512);

for i = 1:512
  Ey(i) = E0*exp(log(0.001)*((i-xp/delta_x)/w)^2);
  Hz(i) = E0/Z*exp(log(0.001)*((i-xp/delta_x + 1/4)/w)^2);
end
