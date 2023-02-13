NICE_BLUE   = [0.0000 0.4470 0.7410];
NICE_ORANGE = [0.8500 0.3250 0.0980];
NICE_YELLOW = [0.9290 0.6940 0.1250];
NICE_GREEN  = [0.4660 0.6740 0.1880];
NICE_RED    = [0.6350 0.0780 0.1840];

ms_2_s = ( 1 / 1000 );
K = ms_2_s;

time_ms_10  = K * [0 :  10 : 480];
time_ms_60  = K * [0 :  60 : 480];
time_ms_240 = K * [0 : 240 : 480];
% Idea for 10 ms
A1 = 2;
T1 = 10;

% Idea for 60 ms
A2 = 3;
T2 = 60;

% Idea for 240 ms
A3 = 4;
T3 = 240;

s1 = A1 * cos( T1 * time_ms_10 );
s2 = A2 * cos( T2 * time_ms_60 );
s3 = A3 * cos( T3 * time_ms_240 );

set( 0, 'DefaultFigureWindowStyle', 'docked' );
timeLabel = 'Time (ms)';

frequencies = {'100', '16.67', '4.17'};
IDX = 1;
fig( IDX ) = figure( 'Name', ['Signals ', frequencies{ IDX }, ' Hz'] );
fig( IDX ).Color = [1 1 1];
hold on;
xlabel( timeLabel );
ylabel( 'Signals (a.u.)' );
title( ['Signal Design - Fs = ', frequencies{ IDX }, 'Hz'] );
grid on;
axis on;
plot( time_ms_10, s1, 'Color', NICE_ORANGE, 'Marker', 'Square',...
    'MarkerFaceColor', NICE_ORANGE, 'DisplayName',...
    ['Fs = ', num2str( 1 / T1 ), ' Hz'] );

IDX = 2;
fig( IDX ) = figure( 'Name', ['Signals ', frequencies{ IDX }, ' Hz'] );
fig( IDX ).Color = [1 1 1];
hold on;
xlabel( timeLabel );
ylabel( 'Signals (a.u.)' );
title( ['Signal Design - Fs = ', frequencies{ IDX }, 'Hz'] );
grid on;
axis on;
plot( time_ms_60, s2, 'Color', NICE_BLUE, 'Marker', 'Square',...
    'MarkerFaceColor', NICE_BLUE, 'DisplayName',...
    ['Fs = ', num2str( 1 / T2 ), ' Hz'] );

IDX = 3;
fig( IDX ) = figure( 'Name', ['Signals ', frequencies{ IDX }, ' Hz'] );
fig( IDX ).Color = [1 1 1];
hold on;
xlabel( timeLabel );
ylabel( 'Signals (a.u.)' );
title( ['Signal Design - Fs = ', frequencies{ IDX }, 'Hz'] );
grid on;
axis on;
plot( time_ms_240, s3, 'Color', NICE_GREEN, 'Marker', 'Square',...
    'MarkerFaceColor', NICE_GREEN, 'DisplayName',...
    ['Fs = ', num2str( 1 / T3 ), ' Hz'] );
