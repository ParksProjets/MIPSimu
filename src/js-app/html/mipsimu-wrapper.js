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
var imageData = ctx.getImageData(0, 0, width, height);


// Memory containers.
var mem, vga;


// C function wrapper.
// var Initialize = Module.cwrap('Initialize', 'void', ['number', 'number']);
// var UpdateAndRender = Module.cwrap('UpdateAndRender', 'void', []);




// Handle of "requestAnimationFrame".
var animHandle = 0;


// Starts the emulator.
function StartEmulator() {

    // Update the application.
    function update() {
        Module._UpdateAndRender(); // performance.now() - start);
        start = performance.now();
    
        imageData.data.set(vga);
        ctx.putImageData(imageData, 0, 0);

        animHandle = requestAnimationFrame(update);
    };

    var start = performance.now();
    update();
}


// Stops the emulator.
function StopEmulator() {
    cancelAnimationFrame(animHandle);
}



// Load some binray data into the memory.
function LoadData(buffer) {
    var memView = new DataView(mem.buffer);
    var bufView = new DataView(buffer);

    for (var i = 0; i < buffer.byteLength; i += 4)
        memView.setUint32(i, bufView.getUint32(i, true));

    StartEmulator();
}


// Loads binary data from a file.
function LoadFromFile() {
    StopEmulator();
    // TODO.
}


// Loads binary data from a file.
function LoadFromUrl(url) {
    StopEmulator();

    fetch(url)
        .then(resp => resp.arrayBuffer())
        .then(LoadData)
        .catch(() => alert("Can't load default MIPS application."));
}




Module.onRuntimeInitialized = () => {

    // Screen buffer.
    var vga_size = width * height * 4;
    var vga_ptr = Module._malloc(vga_size);
    vga = new Uint8Array(Module.HEAPU8.buffer, vga_ptr, vga_size);
    vga.fill(0xFF);

    // Memory buffer.
    var mem_ptr = Module._malloc(0x28000);
    mem = new Uint8Array(Module.HEAPU8.buffer, mem_ptr, 0x28000);


    // Initialize the application.
    Module._Initialize(mem_ptr, vga_ptr);
    console.log("Emulator initialized!");

    // Load the default application.
    LoadFromUrl("flapsthemips.bin");
}
