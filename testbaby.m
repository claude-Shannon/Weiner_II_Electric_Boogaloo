%  x=ecgsyn(500,20,0,60,0,0.5,500);
%  y=length(x);
% for i=61:300
%     x=ecgsyn(500,20,0,i,0,0.5,500);
%     y=[y;length(x)];
%     
%     
%     
% end;
% 
% addpath('C:\Users\shsab\OneDrive\Documents\SPRING_2018\Embedded\Final_Project')
% mother.heartrate=60;
% mother.stddev=0;
% mother.fs=1000;
% mother.data=ecgsyn(mother.fs,9,0,mother.heartrate,mother.stddev,0.5,mother.fs); %big mom
% mother.data=mother.data./(max(mother.data))./2;
% baby.heartrate=140;
% baby.stddev=0;
% baby.fs=1000;
% baby.data=ecgsyn(baby.fs,20,0,baby.heartrate,baby.stddev,0.5,baby.fs); %bb
% baby.data=baby.data./(max(baby.data))./4;
% figure; plot(mother.data); hold on; plot(baby.data,'r')
% 
% change sampling rate to 48k
% momRate=(16/60/length(mother.data))^-1;
% [P,Q]=rat(48000,momRate);
% abs(P/Q*momRate-48000);
% x=resample(mother.data,48000,momRate);
% 
% 
% babyRate=(38/140/length(baby.data))^-1;
% y=resample(baby.data,48000,babyRate);
% 
% 
% figure; plot(x); hold on; plot(y,'r'); title('Mama and baby at fs=48,000)');
% 
% 
% momANDbaby = baby.data(1:length(mother.data))+mother.data;
% figure; plot(momANDbaby,'g');
% 
% 
% 
% 
% mult=100;
% x=repmat(mother.data,mult,1);
% y=repmat(baby.data,mult,1);
% both=x+y(1:length(x));
% sound
% 


addpath('C:\Users\shsab\Desktop\EMBEDDED');


%15 dec
%1 non-decimal
%1 sign bit



%60 bpm
%%THIS IS THE ORIGINAL DATA!!!!!!!!!!!!!!!!!!
[mother.data,Fs]=audioread('C:\Users\shsab\Desktop\EMBEDDED\heartbeat.mp3');

%change mom sampling rate to 48k
momRate=Fs;
[P,Q]=rat(48000,momRate);
abs(P/Q*momRate-48000);
x=resample(mother.data,48000,momRate);
mother.data=x;
mother.fs=48000; 



start=494800;
finish=785100;
chunk=mother.data(start:finish,1);
mother.data=chunk;


%baby generation time
%goal: 150bpm = 60bpm*5/2=mom*5/2

%aka initial fs=48000k*5/2

babyRate=48000*5/2;
[P,Q]=rat(48000,babyRate);
x=resample(chunk,48000,babyRate); 
figure; plot(x)
babychunk=x(57180:76590);
mamachunk=mother.data(12830:64340);
figure; plot([babychunk;babychunk;babychunk;babychunk]); hold on; plot([mamachunk;mamachunk;mamachunk],'r')

mamachunk=mamachunk./max(abs(mamachunk));
babychunk=babychunk./max(abs(babychunk));

y=repmat(mamachunk,17,1);
y=y(50:end);
figure; 
subplot(2,1,1);
plot(y,'color', [.25 .25 .65]); xlabel('sample n'); ylabel('normalized magnitude')
title('Mother''s Heartbeat (60 bps, 48kHz sampling frequency)','FontSize', 24)
set(gcf,'color','w');
xlim([0 850000])

subplot(2,1,2)
x=repmat(babychunk,45,1);
x=x(50:end);
z=x(1:850000)+y(1:850000);
z=z./abs(max(z));
plot(z,'color', [.10 .55 .75]); xlabel('sample n'); ylabel('normalized magnitude')
title('Baby Plus Mother''s Heartbeat (150|60 bps, 48kHz sampling frequency)','FontSize', 24)
set(gcf,'color','w');
xlim([0 850000])




sound([babychunk;babychunk;babychunk;babychunk;babychunk;babychunk;babychunk;babychunk;],48000)
sound(repmat(mamachunk,10),48000)

figure; plot(repmat(mamachunk,10,1))
figure; plot(mamachunk)



mother.data=mamachunk;
baby.data=babychunk;



%fix these magnitudes
mother.data=mamachunk./max(abs(mamachunk))./2; %%MOM DATA IN NCO
baby.data=babychunk./max(abs(babychunk))./2; %%BABY DATA IN NCO

sound(repmat(mother.data,10,1),48000);%51511


dlmwrite('C:\Users\shsab\Desktop\EMBEDDED\motherBeats.txt',mother.data','delimiter',',','precision','%16.15f')
dlmwrite('C:\Users\shsab\Desktop\EMBEDDED\babyBeats.txt',baby.data','delimiter',',','precision','%16.15f')

X=csvread('C:\Users\shsab\Desktop\EMBEDDED\nco_sine.m')