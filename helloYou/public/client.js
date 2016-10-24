var socket = io();

// LOOKING AROUND
function look1() {
    socket.emit('look1');
}

function look2() {
    socket.emit('look2');
}

function look3() {
    socket.emit('look3');
}


// TILTING
function forward() {
    socket.emit('forward');
}

function upright() {
    socket.emit('upright');
}

function backward() {
    socket.emit('backward');
}


// WIGGLE
function wiggle() {
    socket.emit('wiggle');
}


// LOOK AROUND
function lookaround() {
    socket.emit('lookaround');
}


// STOP FUNCTIONS
function stop() {
    socket.emit('stop');
}

function reset() {
    socket.emit('reset');
}




// read the data from the message that the server sent and change the
// background of the webpage based on the data in the message
socket.on('server-msg', function(msg) {
    console.log('msg:', msg);
    switch(msg) {
        case 'light':
            document.body.style.backgroundColor = 'white';
            console.log('white')
            break;
        case 'dark':
            document.body.style.backgroundColor = 'black';
            console.log('black');
            break;
    }
});
