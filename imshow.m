clear;
M = readmatrix('wavefront.dat');%读数据

%画边界
for i=1:1:200
    for j=1:1:200
       if (i>(10*(j-100)^2+50))
           M(i,j)=0.5+M(i,j);
       end
    end
end

I=mat2gray(M);%将数值矩阵X转换为灰度图像
figure;imshow(I); %显示转换后的灰度图像
axis ([0 200 0 200])
axis on;
grid on
imwrite(mat2gray(I), '1.bmp');
