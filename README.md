# AvrMiniCopter-UDP

This is a UDP server interface for AvrMiniCopter.
It's developed for allow AvrMinicopter to handle commands from [RPICopter Android Controller](https://github.com/wilds/rpicopter-android-controller).

Protocol:
------------------------------------------
Each UDP packet contains a command string.
The format of the string is like:
```
<command> <nanotime> [parameter1] [parameter2] ...
```
Available commands:
- HELLO packet:
```
	hello <nanotime> <MYIP>
	resp: OK <nanotime>
```
- RC-INPUT packet:
```
	rcinput <nanotime> <throttle> <yaw> <pitch> <roll>
	not away for response
```
- HEARTBEAT packet:
```
	heartbeat <nanotime> 
	OK <nanotime>
```
- TEST MOTOR packet:
```
	tm <nanotime> <motor0> <motor1> <motor2> <motor3>
	OK <nanotime>
```
- QUERY STATUS packet:
```
	querystatus <nanotime> 
	resp: status <nanotime> <yaw> <pitch> <roll> <altitudetarget> <altitude> <recordstatus>
```
- TAKE PICTUIRE packet:
```
	takepicture <nanotime> 
	OK <nanotime>
```
- RECORD VIDEO packet:
```
	vidsnap <nanotime> <stop|record|pause>
	OK <nanotime>
```
- ENABLE ALTITUDE HOLDER packet:
```
	altitudeholderenabled <nanotime> <0|1>
	OK <nanotime>
```
- SET ALTITUDE packet:
```
	altitudetarget <nanotime> <+X|-X|X>
	OK <nanotime>
```
- FLYMODE packet:
```
	flymode <nanotime> <stable|acro>
	OK <nanotime>
```
