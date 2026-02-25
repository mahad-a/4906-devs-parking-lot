[Top]
components : AccessControl@AccessControlType Lot 
out : out 
in : in 
Link : in in@AccessControl
Link : out@AccessControl in@Lot
Link : out@Lot out

[AccessControl]

[Lot]
components : Sensor1@Sensor1Type Screen@ScreenType 
out : out 
in : in 
Link : in in@Sensor1
Link : out@Sensor1 in@Screen
Link : out@Screen out

[Sensor1]

[Screen]



