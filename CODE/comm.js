// old stuff
var connect = require('connect'),
	fs = require('fs'),
	util = require('util'),
	io = require('socket.io').listen(9001), // WS port
	port = 9000, // HTTP port
	
	// new stuff
	// define a class
	SerialPort = require("serialport").SerialPort,
	// ls /dev/tty.*
	sPort="/dev/tty.usbmodem1411",
	//sPort = "/dev/tty.usbserial-AM01PK24",
	// create an instance (object)
	arduino = new SerialPort(sPort, {
		baudrate: 57600
	});

// create web server using connect 
connect.createServer(
	connect.static(__dirname + '/public') // two underscores
).listen(port);
util.log('the server is running on port: ' + port);

// init socket.io
io.set('log level', 1);
io.sockets.on('connection', function(socket) {
	util.log('Ooooooh, someone just poked me :)');
	// socket.on('led', function(data) {
	// 	// sending binary data
	// 	var ledOn = new Buffer(1), // Buffer is an array and Buffer(1) means 1 index array
	// 		ledOff = new Buffer(1);
	// 	ledOn[0] = 0x01; // 1
	// 	ledOff[0] = 0x00; // 0
	// 	// shorthand ledOn = new Buffer([0x01])

	// 	if(data === true) {
	// 		// turn on
	// 		arduino.write(ledOn);
	// 		util.log('LED ON');
	// 	} else {
	// 		// turn off
	// 		arduino.write(ledOff);
	// 		util.log('LED OFF');
	// 	}
	// });
	// socket.on('slider', function(data) {
	// 	aHex = data.toString(16);
	// 	bHex = '0x' + aHex;
	// 	cHex = new Buffer([bHex]);
	// 	// util.log('Z' + cHex + 'X');
	// 	arduino.write('O' + cHex + 'P');
	// });
});

// function that converts int to hexadecimal
// we communicate to Arduino using hex (binary) 

// serial port
var receivedData, sendData;

arduino.on('open', function() {
	console.log('opening port');
	// console.log((11).toString(16));
	// setInterval(toggle, 1000);
});

// receive data
arduino.on('data', function(data) { // data comes in Buffer <   >
	// try removing toString()
	// util.log(data);
	receivedData += data;
	// basically says if there're 'E' and 'B' signals
	if (receivedData.indexOf('E') >= 0 && receivedData.indexOf('B') >= 0) {
		// save the data between 'B' and 'E'
		sendData = receivedData.substring(receivedData.indexOf('B') + 1, receivedData.indexOf('E'));
		receivedData = '';
		util.log(sendData);
		// parse data to browser
		io.sockets.emit('controller', sendData);
		// socket.io
		// emit, on, broadcast.emit, io.sockets.emit
	}

	if (receivedData.indexOf('S') >= 0 && receivedData.indexOf('F') >= 0) {
		// save the data between 'S' and 'F'

			sendData = receivedData.substring(receivedData.indexOf('S') + 1, receivedData.indexOf('F'));
			receivedData = '';
			if(sendData != 'FS'){
				util.log(sendData);
				// parse data to browser
				io.sockets.emit('button', sendData);
				// socket.io
				// emit, on, broadcast.emit, io.sockets.emit
			}

	}
});