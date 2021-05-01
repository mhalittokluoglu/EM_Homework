globals;

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