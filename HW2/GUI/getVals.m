globals
mu_1 = str2double(get(handles.edit1, 'String'));
mu_2 = str2double(get(handles.edit2, 'String'));
mu_3 = str2double(get(handles.edit3, 'String'));

ep_1 = str2double(get(handles.edit4, 'String'));
ep_2 = str2double(get(handles.edit5, 'String'));
ep_3 = str2double(get(handles.edit6, 'String'));

sigma_1 = str2double(get(handles.edit7, 'String'));
sigma_2 = str2double(get(handles.edit8, 'String'));
sigma_3 = str2double(get(handles.edit9, 'String'));


ep(1:250) = ep_1*e0;
ep(251:309) = ep_2*e0;
ep(310:512) = ep_3*e0;

mu(1:250) = mu_1*mu0;
mu(251:309) = mu_2*mu0;
mu(310:512) = mu_3*mu0;

sigma(1:250) = sigma_1;
sigma(251:309) = sigma_2;
sigma(310:512) = sigma_3;

