colors = [204 0 153; 255 0 0; 255 204 0; 51 204 204; 0 0 204; 0 0 0]/255;
colorsRepeated = repmat(colors, length(index)/6);
colorsRepeated = colorsRepeated(:,1:3);
sizes = [40; 2; 2; 2; 2; 2];
sizesRepeated = repmat(sizes, length(index)/6);
sizesRepeated = sizesRepeated(:,1);

scatter(x, y, sizesRepeated, colorsRepeated, 'filled')

xlabel('x');
ylabel('y');

hold on;
h = zeros(6, 1);
for i = 1:6
    h(i) = scatter(NaN, NaN, 20, colors(i,:), 'filled');
end
legend(h, 'Sun','Jupiter','Saturn', 'Uranus', 'Neptune', 'Pluto');
hold off;