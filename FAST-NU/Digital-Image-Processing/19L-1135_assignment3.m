function[x] = rle(filename)
I=imread(filename);
level=graythresh(I);
bw=im2bw(I,level);
a=bw';
a=a(:);
a=a';
a=double(a);
x(1)=a(1);
m=2;
x(m)=1;
for i=1:length(a)-1
    if a(i)==a(i+1)
        x(m)=x(m)+1;
    else
        m=m+1; x(m)=1;        
    end
end

y=[];
for i=1:2:length(x)
    y=[y x(i)];
end
z=[];
for i=2:2:length(x)
    z=[z x(i)];
end
v=[];
for i=1:length(z)
    m=y(i);
    q=z(i);
    for j=1:m
        v=[v q];
    end
end


originalSize = length(a);
compressedSize = length(x);
%display('Original size: ', length(a));
compressedRatio = length(a)/length(x);
display(originalSize);
display(compressedSize);
display(compressedRatio);