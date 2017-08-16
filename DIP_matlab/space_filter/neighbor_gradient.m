%% º∆À„¡⁄”ÚÃ›∂»
function gradient = neighbor_gradient(neighbor_block)

[height, width] = size(neighbor_block);
gradient = zeros(height, width);
center = neighbor_block((height+1)/2, (width+1)/2);

for h = 1:height
    for w = 1:width
        denominator = neighbor_block(h, w) - center;
        if denominator == 0
            gradient(h, w) = 0.0;
        else
            gradient(h, w) = abs(1.0 / denominator);
    end
end

gradient((height+1)/2, (width+1)/2) = 0.0;
 
end