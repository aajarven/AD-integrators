planetNumber = 6;

plutoR = [x(planetNumber:6:end,:), y(planetNumber:6:end,:), z(planetNumber:6:end,:)];
plutoV = [vx(planetNumber:6:end,:), vy(planetNumber:6:end,:), vz(planetNumber:6:end,:)];

sunR = [x(1:6:end,:), y(1:6:end,:), z(1:6:end,:)];
sunV = [vx(1:6:end,:), vy(1:6:end,:), vz(1:6:end,:)];

rs = plutoR - sunR; % AU
vs = plutoV - sunV; % AU/yr
%mu = 3.966832e+01 + 2.040596e-03; %AU^3/yr^2
mu = 3.966832e+01 + 2.246283e-07; %AU^3/yr^2

uniqueT = t(1:6:end,:);

eccentricity = zeros(length(uniqueT), 1);
inclination = zeros(length(uniqueT), 1);
Omega = zeros(length(uniqueT), 1);
omega = zeros(length(uniqueT), 1);
M = zeros(length(uniqueT), 1);

for i = 1:length(uniqueT)
    r = rs(i,:);
    v = vs(i,:);
    h = cross(r, v);
    
    % eccentricity
    %eVec = ((dot(v,v) - mu/norm(r))*r - (dot(r,v)*v))/mu;
    eVec = cross(v, h)/mu-r/norm(r);
    eccentricity(i) = norm(eVec);
    
    % inclination
    inclination(i) = acosd(h(3)/norm(h)); % degrees
    
    % Omega
    n = cross([0, 0, 1], h);
    if n(2)<0
        Omega(i) = 360 - acosd(n(1)/norm(n));
    else
        Omega(i) = acosd(n(1)/norm(n));
    end
    
    % omega
    if eVec(3) < 0
        omega(i) = 360 - acosd(dot(n, eVec)/(norm(n)*norm(eVec)));
    else
        omega(i) = acosd(dot(n, eVec)/(norm(n)*norm(eVec)));
    end
    
    % M
    nu = acos(dot(eVec, r)/(norm(eVec)*norm(r))); % true anomaly
    %E = 2*atand(sqrt((1-norm(eVec))/(1+norm(eVec)))*tan(nu/2));
    E = atan2d(sqrt(1-dot(eVec, eVec))*sin(nu), norm(eVec)+cos(nu));
    M(i) = E-norm(eVec)*sin(E);
end

clearvars rs vs mu r v h eVec n nu E;
