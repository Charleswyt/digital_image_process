%% ĞŞÕıalpha¾ùÖµÂË²¨
function m = revisemean(x, del)

x = sort(x(:));
number = length(x);
mid = (number - 1) / 2;

if(del >= mid)
    del = mid;
end

m = mean(x(1+del : number-del));