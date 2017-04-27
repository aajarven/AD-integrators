colors = [204 0 153; 255 0 0; 255 204 0; 51 204 204; 0 0 204; 0 0 0]/255;
colorsRepeated = ones(length(index), 3);
%colorsRepeated = colors(repmat(1:size(colors,1), length(index)/6,1),:);
%colorsRepeated = repmat(colors, length(index)/6);
%colorsRepeated = colorsRepeated(:,1:3);
sizes = [40; 2; 2; 2; 2; 2];
sizesRepeated = ones(length(index), 1);
%sizesRepeated = sizes(repmat(1:size(sizes,1), length(index)/6,1),:);
%sizesRepeated = repmat(sizes, length(index)/6);
%sizesRepeated = sizesRepeated(:,1);

for i=1:length(index)
    sizesRepeated(i) = sizes(mod(i-1, 6)+1);
    
    for j=1:3
        colorsRepeated(i,j) = colors(mod(i-1,6)+1,j);
    end
    
end

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