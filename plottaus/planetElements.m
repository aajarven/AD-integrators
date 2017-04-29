function [ inclination, M, omega, Omega, eccentricity, uniqueT, lambda, pomega ] = planetElements( planetNumber, mu , x, y, z, vx, vy, vz, t, index)

    planetR = [x(planetNumber:6:end,:), y(planetNumber:6:end,:), z(planetNumber:6:end,:)];
    planetV = [vx(planetNumber:6:end,:), vy(planetNumber:6:end,:), vz(planetNumber:6:end,:)];

    sunR = [x(1:6:end,:), y(1:6:end,:), z(1:6:end,:)];
    sunV = [vx(1:6:end,:), vy(1:6:end,:), vz(1:6:end,:)];

    rs = planetR - sunR; % AU
    vs = planetV - sunV; % AU/yr

    uniqueT = t(1:6:end,:);

    eccentricity = zeros(length(uniqueT), 1);
    inclination = zeros(length(uniqueT), 1);
    Omega = zeros(length(uniqueT), 1);
    omega = zeros(length(uniqueT), 1);
    M = zeros(length(uniqueT), 1);
    lambda = zeros(length(uniqueT), 1);
    pomega = zeros(length(uniqueT), 1);

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
        nu = acos( dot(eVec, r) / (norm(eVec) * norm(r))); % true anomaly
        if dot(r, v)<0
            nu = 2*pi-nu;
        end
        %E = 2*atand(sqrt((1-norm(eVec))/(1+norm(eVec)))*tan(nu/2));
        E = atan2( sqrt(1-dot(eVec, eVec)) * sin(nu), norm(eVec)+cos(nu));
        E = mod(E, 2*pi);
        M = E - norm(eVec)*sin(E); %E - norm(eVec)*sin(E); % 
        M(i) = M*180/pi;
        
        % lambda and pomega
        lambda(i) = Omega(i) + omega(i) + M(i);
        pomega(i) = Omega(i) + omega(i);
    end

    clearvars rs vs mu r v h eVec n nu E;
end
