var express = require('express'); // web server application
var http = require('http');				// http basics
var app = express();							// instantiate express server
var server = http.Server(app);		// connects http library to server
var io = require('socket.io')(server);	// connect websocket library to server
var serialport = require('serialport');	// serial library
var serverPort = 8000;

// use express to create the simple webapp
app.use(express.static('public'));		// find pages in public directory

// check to make sure that the user calls the serial port for the arduino when
// running the server
if(!process.argv[2]) {
    console.error('Usage: node '+process.argv[1]+' SERIAL_PORT');
    process.exit(1);
}

// start the serial port connection and read on newlines
var serial = new serialport.SerialPort(process.argv[2], {
    parser: serialport.parsers.readline('\r\n')
});

// this is the websocket event handler and say if someone connects
// as long as someone is connected, listen for messages
io.on('connect', function(socket) {
    console.log('a user connected');



// LOOKING AROUND
    socket.on('look1', function() {
        console.log('look1');
        serial.write('1');
    });

    socket.on('look2', function() {
        console.log('look2');
        serial.write('2');
    });

    socket.on('look3', function() {
        console.log('look3');
        serial.write('3');
    });


// TILTING
    socket.on('forward', function() {
        console.log('forward');
        serial.write('M');
    });

    socket.on('upright', function() {
        console.log('upright');
        serial.write('N');
    });

    socket.on('backward', function() {
        console.log('backward');
        serial.write('B');
    });


//WIGGLE
    socket.on('wiggle', function() {
        console.log('wiggle');
        serial.write('W');
    });

// LOOKAROUND
    socket.on('lookaround', function() {
        console.log('lookaround');
        serial.write('L');
    });

// SWOOP (To be built out, currently just one not properly working function)
    socket.on('swoopA', function() {
        console.log('swoopA');
        serial.write('A');
    });


//STOP AND RESET
    socket.on('stop', function() {
        console.log('stop');
        serial.write(' ');
    });

    socket.on('reset', function() {
        console.log('reset');
        serial.write('R');
    });



    // if you get the 'disconnect' message, say the user disconnected
    socket.on('disconnect', function() {
        console.log('user disconnected');
    });



});

// this is the serial port event handler.
// read the serial data coming from arduino - you must use 'data' as the first argument
// and send it off to the client using a socket message
serial.on('data', function(data) {
    console.log('data:', data);
    io.emit('server-msg', data);
});

// start the server and say what port it is on
server.listen(serverPort, function() {
    console.log('listening on *:%s', serverPort);
});
