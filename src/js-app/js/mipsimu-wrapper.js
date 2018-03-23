/*

JS wrapper for MIPSimu.

https://github.com/jonvaldes/canvascripten/blob/master/index.html

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

var width = 320;
var height = 240;


// Screen canvas.
var canvas = document.getElementById("screen");
canvas.width = width;
canvas.height = height;

var ctx = canvas.getContext('2d');
var data = ctx.getImageData(0, 0, width, height);


// C function wrapper.
var Initialize = Module.cwrap('Initialize', 'void', ['number', 'number']);
var UpdateAndRender = Module.cwrap('UpdateAndRender', 'void', []);


// Screen buffer.
var buffer_size = 0;
var buffer_ptr = Module._malloc(buffer_size);
var buffer = new Uint8Array(Module.HEAPU8.buffer, buffer_ptr, buffer_size);


// Initialize the application.
Initialize(width, height, buffer.byteOffset);


// Update the application.
var update = function() {
    UpdateAndRender(buffer.byteOffset, w, h, Date.now() - start);

    imageData.data.set(buf);
    ctx.putImageData(imageData,0,0);

    window.requestAnimationFrame(update);
};

update();
