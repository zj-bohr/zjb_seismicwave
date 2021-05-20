clear;
f=25;%中心频率
gama=3;%控制频带宽度的参数
pi=3.141592653589793;
lt=1000;%采样时间长度,单位ms
dt=0.0001;%采样时间间隔,单位s
t=zeros(1,lt);
s=zeros(1,lt);
for k=1:1000
    t(k)=k*dt*1000;%*1000是将单位s转换为ms
    s(k)=exp(-1 * (2 * pi * f / gama)^ 2 * (k * dt)^ 2) * cos(2 * pi * f* k * dt);
end
plot(t,s)
title("雷克子波（零相位）");
xlabel('采样时间/ms')
ylabel('振幅')
legend('中心频率25')
