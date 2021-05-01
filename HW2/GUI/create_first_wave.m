Z = Z0 * (mu_1/ep_1)^(1/2);

xp = xcenter*delta_x;

Ey = zeros(1,512);
Hz = zeros(1,512);

for i = 1:512
  Ey(i) = E0*exp(log(0.001)*((i-xp/delta_x)/w)^2);
  Hz(i) = E0/Z*exp(log(0.001)*((i-xp/delta_x + 1/4)/w)^2);
end

