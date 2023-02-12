% note openarinc found @ https://github.com/stewbond/openarinc
clear all;
close all;
clc;

%% Create Simulink.ConfigSet
TF = 10;
DT = 0.1;
config_demo = Simulink.ConfigSet;
set_param( config_demo, 'StopTime', 'TF' );
set_param( config_demo, 'SolverType', 'Fixed-step' );
set_param( config_demo, 'SolverName', 'ode4' );
set_param( config_demo, 'FixedStep', 'DT' );
set_param( config_demo, 'ModelReferenceNumInstancesAllowed', 'Single' );

set_param( config_demo, 'SimUserIncludeDirs', ['.', newline, '..'] );

%% Create Bus
element_names = { 'u', 'v', 'w', 'p', 'q', 'r', 'phi', 'theta', 'psi', 'VN', 'VE', 'VD' };
element_units = { 'm/s', 'm/s', 'm/s', 'deg/s', 'deg/s', 'deg/s', 'deg', 'deg', 'deg', 'm/s', 'm/s', 'm/s' };
bus_aero_signal_grp_t = Simulink.Bus;

for ii = 1 : 12
    e( ii ) = Simulink.BusElement;
    e( ii ).Name = element_names{ ii };
    e( ii ).DataType = 'double';
    e( ii ).Dimensions = 1;
    e( ii ).Unit = element_units{ ii };
    e( ii ).Complexity = 'real';
end

bus_aero_signal_grp_t.Elements = e;
clear e;